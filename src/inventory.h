#ifndef INVENTORY_H
#define INVENTORY_H
#include "config/config.h"
#include "entity.h"

void
player_inv_give(struct player *, struct item_config *, uint32_t);

void
player_inv_remove(struct player *, const char *, uint32_t);

int
player_inv_remove_id(struct player *, int, uint32_t);

void
player_inv_remove_slot(struct player *, int);

bool
player_inv_held(struct player *, const char *, uint32_t);

bool
player_inv_held_id(struct player *, int, uint32_t);

bool
player_inv_worn(struct player *, const char *);

int
player_inv_clear(struct player *);

int
player_inv_death(struct player *);
#endif
