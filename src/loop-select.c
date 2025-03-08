#include "../config.h"
#ifdef _WIN32
#include "platform/win32_compat.h"
#else
#include <sys/select.h>
#include <sys/socket.h>
#include <netdb.h>
#endif
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "entity.h"
#include "loop.h"
#include "server.h"
#include "netio.h"
#include "utility.h"

static int loop_delay = TICK_RATE;

int
loop_add_player(struct player *p)
{
	(void)p;
	return 0;
}

void
loop_set_delay(int delay)
{
	loop_delay = delay;
}

int
loop_start(struct server *s)
{
	struct timeval tv = {0};
	int sockets[8];
	fd_set read_set;
	fd_set orig_set;
	int numsockets = 0;
	int maxfd = 0;
	uint64_t next_tick = 0;

	numsockets = net_establish_listener(s, sockets);
	if (numsockets == 0) {
		fprintf(stderr, "failed to open sockets: %s\n", strerror(errno));
		goto err;
	}

	FD_ZERO(&orig_set);

	printf("got %d sockets\n", numsockets);
	for (int i = 0; i < numsockets; ++i) {
		FD_SET(sockets[i], &orig_set);
		if (sockets[i] >= maxfd) {
			maxfd = sockets[i] + 1;
		}
	}

	tv.tv_sec = 0;
	tv.tv_usec = 20000;

	read_set = orig_set;
	while (select(maxfd, &read_set, NULL, NULL, &tv) != -1) {
		for (int i = 0; i <= maxfd; ++i) {
			if (FD_ISSET(i, &read_set)) {
				net_player_accept(s, i);
			}
		}
		if (get_time_ms() >= next_tick) {
			server_tick();
			next_tick = get_time_ms() + loop_delay;
		}
		read_set = orig_set;
	}
	for (int i = 0; i < numsockets; ++i) {
		close(sockets[i]);
	}
	printf("done\n");
	return 0;
err:
	for (int i = 0; i < numsockets; ++i) {
		close(sockets[i]);
	}
	return -1;
}
