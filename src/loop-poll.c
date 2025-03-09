#include "../config.h"
#ifdef HAVE_SYS_TIMERFD_H
#include <sys/timerfd.h>
#endif
#ifdef _WIN32
#include "platform/win32_compat.h"
#else
#include <sys/socket.h>
#include <poll.h>
#include <netdb.h>
#endif
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "entity.h"
#include "loop.h"
#include "server.h"
#include "netio.h"
#include "utility.h"

struct server *serv;

static int loop_delay = TICK_RATE;

#ifdef HAVE_SYS_TIMERFD_H
static int timerfd = -1;
#endif

int
loop_add_player(struct player *p)
{
	(void)p;
	return 0;
}

void
loop_set_delay(int delay)
{
#ifdef HAVE_TIMERFD_CREATE
	struct itimerspec its = {0};
#endif
	loop_delay = delay;

#ifdef HAVE_TIMERFD_CREATE
	its.it_interval.tv_nsec = delay * 1000000;
	its.it_value = its.it_interval;

	(void)timerfd_settime(timerfd, 0, &its, NULL);
#endif
}

int
loop_start(struct server *s)
{
	int sockets[8];
	struct pollfd pfds[8];
	int numsockets = 0;
	int numfd = 0;
	uint64_t next_tick = 0;

	serv = s;

	numsockets = net_establish_listener(s, sockets);
	if (numsockets == 0) {
		fprintf(stderr, "failed to open sockets: %s\n", strerror(errno));
		goto err;
	}

#ifdef HAVE_TIMERFD_CREATE
	timerfd = timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK);
	if (timerfd != -1) {
		struct itimerspec its = {0};
		its.it_interval.tv_nsec = TICK_RATE * 1000000;
		its.it_value = its.it_interval;

		(void)timerfd_settime(timerfd, 0, &its, NULL);
		pfds[numfd].fd = timerfd;
		pfds[numfd++].events = POLLRDNORM | POLLRDBAND;
	}
#endif

	printf("got %d sockets\n", numsockets);
	for (int i = numfd; i < (numsockets + numfd); ++i) {
		pfds[i].fd = sockets[i - numfd];
		pfds[i].events = POLLRDNORM | POLLRDBAND;
	}

	while (poll(pfds, numfd + numsockets, 20) != -1) {
		for (int i = numfd; i < (numfd + numsockets); ++i) {
			if ((pfds[i].revents & POLLRDNORM) ||
			    (pfds[i].revents & POLLRDBAND)) {
				net_player_accept(s, pfds[i].fd);
			}
		}
		if (get_time_ms() >= next_tick) {
			server_tick();
			next_tick = get_time_ms() + loop_delay;
		}
	}
	for (int i = 0; i < numfd + numsockets; ++i) {
		close(pfds[i].fd);
	}
	printf("done\n");
	return 0;
err:
	for (int i = 0; i < numfd + numsockets; ++i) {
		close(pfds[i].fd);
	}
	return -1;
}
