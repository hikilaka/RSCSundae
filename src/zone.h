#ifndef ZONE_H
#define ZONE_H
#include <stdint.h>
#include <stddef.h>

#ifndef ZONE_WIDTH
#define ZONE_WIDTH	(8)
#endif

#ifndef ZONE_AREA
#define ZONE_AREA	(64)
#endif

#ifndef ZONE_MAX_BOUNDS
#define ZONE_MAX_BOUNDS	(16)
#endif

#ifndef ZONE_MAX_X
#define ZONE_MAX_X	(450)
#endif

#ifndef ZONE_TOTAL_X
#define ZONE_TOTAL_X	(1 + (ZONE_MAX_X / ZONE_WIDTH))
#endif

#ifndef ZONE_MAX_Y
#define ZONE_MAX_Y	(750)
#endif

#ifndef ZONE_TOTAL_Y
#define ZONE_TOTAL_Y	(1 + (ZONE_MAX_Y / ZONE_WIDTH))
#endif

#ifndef ZONE_MAX_PLANE
#define ZONE_MAX_PLANE	(4)
#endif

struct server;
struct player;
struct npc;

/* 3d object in 2-dimensional space */
struct loc {
	uint16_t id;
	uint16_t orig_id;
	uint16_t x;
	uint16_t y;
	uint8_t dir;
};

enum bound_dir {
	BOUND_DIR_VERT		= 0,
	BOUND_DIR_HORIZ		= 1,
	BOUND_DIR_DIAG_NW_SE	= 2,
	BOUND_DIR_DIAG_NE_SW	= 3,
};

/* 2d object (wall) in 3-dimensional space */
struct bound {
	uint16_t id;
	uint16_t x;
	uint16_t y;
	uint8_t dir;
};

struct ground_item {
	uint16_t id;
	uint16_t x;
	uint16_t y;
	uint16_t duration;	/* ticks until deletion */
	uint32_t stack;
	uint8_t respawn;
	uint8_t on_surface;
	uint64_t creation_time;	/* ticks of creation */
	uint64_t respawn_time;	/* ticks of next respawn */
	uint64_t unique_id;
	int64_t owner;
};

/* small chunk of the game world */
struct zone {
	uint16_t x, y;
	uint8_t plane;
	struct loc locs[ZONE_AREA];
	uint16_t loc_count;
	struct bound bounds[ZONE_MAX_BOUNDS];
	uint16_t bound_count;
	struct ground_item *items;
	uint16_t item_count;
	uint16_t item_max;
	uint16_t *npcs;
	uint16_t npc_max;
	uint16_t *players;
	uint16_t player_max;
};

struct zone *server_find_zone(int, int);
struct zone *server_get_zone(int, int, int);
struct loc *server_find_loc(int, int);
void server_add_loc(struct server *, struct loc *);
void server_del_loc(int, int);
struct bound *server_find_bound(int, int, int);
void server_add_bound(struct server *, struct bound *);
struct ground_item *server_get_ground_item(struct player *, uint64_t, int, int);
struct ground_item *server_find_ground_item(struct player *, int, int, int);
void server_add_item_respawn(struct ground_item *);

void zone_add_player(struct zone *, uint16_t);
void zone_remove_player(struct zone *, uint16_t);

void zone_add_npc(struct zone *, uint16_t);
void zone_remove_npc(struct zone *, uint16_t);

size_t zone_find_npcs(struct zone *, struct server *,
    struct npc **, size_t, bool);

size_t zone_find_players(struct zone *, struct server *,
    struct player **, size_t);

bool server_player_on_tile(struct server *, int, int);
bool server_npc_on_tile(struct server *, int, int, bool);

#endif
