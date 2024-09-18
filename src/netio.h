#ifndef NETIO_H
#define NETIO_H

#include "entity.h"

int net_establish_listener(struct server *, int *);
int net_player_accept(struct server *, int);
int net_player_send(struct player *);
int net_player_recv(struct player *);
void net_login_response(struct player *, int);

#endif
