#ifndef _WIN32
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#endif
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include "protocol/opcodes.h"
#include "server.h"
#include "netio.h"

#ifdef _WIN32
#include "platform/win32_compat.h"
static int winsock_startup = 0;
#endif

static int net_set_flags(int);

int
net_establish_listener(struct server *s, int *sockets)
{
	int numsocks = 0;
	struct addrinfo hints = {0};
	struct addrinfo *ai = NULL, *ai0 = NULL;
	char portstr[32];

#ifdef _WIN32
	if (!winsock_startup) {
		WSADATA wsa_data = {0};
		int ret = WSAStartup(MAKEWORD(2, 2), &wsa_data);

		if (ret < 0) {
			fprintf(stderr, "WSAStartup() error: %d\n",
			    WSAGetLastError());
			return -1;
		}
		winsock_startup = 1;
	}
#endif

	(void)snprintf(portstr, sizeof(portstr), "%d", s->port);

	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if (getaddrinfo(s->bind_addr, portstr, &hints, &ai0) == -1) {
		fprintf(stderr, "failed to getaddrinfo: %s\n", strerror(errno));
		goto err;
	}

	for (ai = ai0; ai != NULL; ai = ai->ai_next) {
		int s = socket(ai->ai_family, SOCK_STREAM, 0);
		if (s == -1) {
			fprintf(stderr,
			    "failed to open socket: %s\n", strerror(errno));
			continue;
		}

		if (net_set_flags(s) == -1) {
			close(s);
			continue;
		}

		if (bind(s, ai->ai_addr, ai->ai_addrlen) == -1) {
			fprintf(stderr,
			    "failed to bind socket: %s\n", strerror(errno));
			close(s);
			continue;
		}

		if (listen(s, SOMAXCONN) == -1) {
			fprintf(stderr,
			    "failed to listen on socket: %s\n", strerror(errno));
			close(s);
			continue;
		}

		sockets[numsocks++] = s;
	}

	freeaddrinfo(ai0);
	ai0 = NULL;

	return numsocks;
err:
	if (ai0 != NULL) {
		freeaddrinfo(ai0);
	}
	return -1;
}

int
net_player_recv(struct player *p)
{
	size_t max = PLAYER_BUFSIZE - p->inbuf_len;
	ssize_t n = recv(p->sock, p->inbuf + p->inbuf_len, max, 0);

	if (n > 0) {
#if 0
		/* this is useful for capturing data for e.g. fuzzing */
		FILE *f = fopen("./packet", "ab");
		if (f != NULL) {
			fwrite(p->inbuf + p->inbuf_len, 1, n, f);
			fflush(f);
			fclose(f);
		}
#endif
		p->inbuf_len += n;
	}
	return 0;
}

int
net_player_send(struct player *p)
{
	size_t to_write = p->outbuf_len - p->outbuf_written;

	if (to_write > 0) {
		ssize_t len = send(p->sock,
			p->outbuf + p->outbuf_written, to_write, 0);
		if (len > 0) {
			p->outbuf_written += len;
		}
	}

	if (p->outbuf_written >= p->outbuf_len) {
		p->outbuf_len = 0;
		p->outbuf_written = 0;
	}
	return 0;
}

void
net_login_response(struct player *p, int response)
{
	if (p->protocol_rev < 196) {
		uint8_t b[2];

		b[0] = 0;
		b[1] = response;

		(void)send(p->sock, &b, sizeof(b), 0);
	} else {
		uint8_t b = response;

		(void)send(p->sock, &b, sizeof(b), 0);
	}
}

static int
net_set_flags(int s)
{
	int flags;

#ifdef F_GETFL
	flags = fcntl(s, F_GETFL, 0);
	if (flags == -1) {
		fprintf(stderr,
		    "failed to get flags: %s\n", strerror(errno));
		return -1;
	}

	if (fcntl(s, F_SETFL, flags | O_NONBLOCK) == -1) {
		fprintf(stderr,
		    "failed to set O_NONBLOCK: %s\n", strerror(errno));
		return -1;
	}
#else
	flags = 1;
	if (ioctl(s, FIONBIO, &flags) != 0) {
		fprintf(stderr, "failed to set non-blocking\n");
		return -1;
	}
#endif

#ifdef TCP_NODELAY
	flags = 1;
	if (setsockopt(s, IPPROTO_TCP, TCP_NODELAY,
			&flags, sizeof(flags)) == -1) {
		fprintf(stderr,
		    "failed to set TCP_NODELAY: %s\n", strerror(errno));
		return -1;
	}
#endif

	return 0;
}

int
net_player_accept(struct server *serv, int from)
{
	char address[64];
	struct sockaddr_storage client_addr;
	socklen_t client_len = sizeof(client_addr);
	struct player *p;

	int client_sock = accept(from,
	    (struct sockaddr *)&client_addr, &client_len);
	if (client_sock == -1) {
		return -1;
	}

	if (net_set_flags(client_sock) == -1) {
		close(client_sock);
		return -1;
	}

	getnameinfo((struct sockaddr *)&client_addr,
	    sizeof(client_addr),
	    address, sizeof(address), NULL, 0,
	    NI_NUMERICHOST);
	printf("got connection from %s\n", address);

	p = player_create(serv, client_sock, address);
	if (p == NULL) {
		close(client_sock);
		return -1;
	}

	return 0;
}
