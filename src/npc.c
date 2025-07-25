#include <assert.h>
#include "config/config.h"
#include "entity.h"
#include "script.h"
#include "server.h"

static void npc_random_walk(struct npc *);
static int npc_combat_roll(struct npc *, struct player *);
static void npc_hunt_target(struct npc *);
static bool npc_init_combat(struct npc *, struct player *);
static bool npc_tile_indoors(struct npc *, int, int);

static bool
npc_tile_indoors(struct npc *npc, int x, int y)
{
	int plane = 0;
	int p_y = y;

	while (p_y > PLANE_LEVEL_INC) {
		p_y -= PLANE_LEVEL_INC;
		plane++;
	}
	return (npc->mob.server->adjacency[plane][x][p_y] & ADJ_INDOORS) != 0;
}

void
npc_die(struct npc *npc, struct player *p)
{
	struct zone *zone_old;
	struct zone *zone_new;

	if (p != NULL) {
		if (p->chased_by_npc == npc->mob.id) {
			p->chased_by_npc = UINT16_MAX;
		}

		if (p->script_active || p->ui_multi_open) {
			/* might be waiting on an existing killnpc script */
			return;
		}

		if (script_onkillnpc(npc->mob.server->lua, p, npc)) {
			if (npc->mob.cur_stats[SKILL_HITS] > 0) {
				/* the killnpc trigger can restore hits */
				return;
			}
		}

		for (int i = 0; i < npc->config->drop_count; ++i) {
			struct item_config *item_config;
			uint16_t id;

			id = npc->config->drops[i].id;
			item_config = server_item_config_by_id(id);
			assert(item_config != NULL);

			if (item_config->weight == 0) {
				server_add_temp_item(p, npc->mob.x, npc->mob.y,
				    id, npc->config->drops[i].amount, 200);
			} else {
				/*
				 * possibly an authentic bug - the config file
				 * lists skeletons as dropping two bones but
				 * appear to drop one bone in all replays.
				 *
				 * tip.it's archives don't mention a double
				 * bone drop, so this probably never happened.
				 *
				 * they would have mentioned a good way to
				 * train prayer since big bones didn't exist.
				 */
				server_add_temp_item(p, npc->mob.x, npc->mob.y,
				    id, 1, 200);
			}
		}

		if (p->script_active || p->ui_multi_open) {
			/* might be waiting on an existing killnpc script */
			return;
		}
	}

	npc->respawn_time = npc->config->respawn / 5;

	if (p != NULL && p->mob.in_combat &&
	    p->mob.target_npc == npc->mob.id) {
		player_award_combat_xp(p, &npc->mob);
	}

	mob_die(&npc->mob);

	if (p != NULL && p->mob.target_npc == npc->mob.id) {
		mob_combat_reset(&p->mob);
	}

	zone_old = server_find_zone(npc->mob.x, npc->mob.y);

	npc->mob.x = npc->spawn_x;
	npc->mob.y = npc->spawn_y;

	zone_new = server_find_zone(npc->mob.x, npc->mob.y);

	if (zone_old != zone_new) {
		if (zone_old != NULL) {
			zone_remove_npc(zone_old, npc->mob.id);
		}
		if (zone_new != NULL) {
			zone_add_npc(zone_new, npc->mob.id);
		}
	}
}

void
npc_damage(struct npc *npc, struct player *p , int roll)
{
	if (roll >= npc->mob.cur_stats[SKILL_HITS]) {
		npc->mob.cur_stats[SKILL_HITS] = 0;
		npc_die(npc, p);
		return;
	}

	if (npc->mob.cur_stats[SKILL_HITS] == 0) {
		return;
	}

	if (p != NULL &&
	    npc->mob.cur_stats[SKILL_HITS] > npc->config->bravery &&
	    npc->mob.target_player == -1) {
		npc->mob.target_player = p->mob.id;
		npc->mob.following_player = p->mob.id;
	}

	npc->mob.cur_stats[SKILL_HITS] -= roll;
	npc->mob.damage = roll;
	npc->mob.damage_timer = p->mob.server->tick_counter;
}

void
npc_change(struct npc *npc, struct npc_config *config)
{
	assert(npc != NULL);
	assert(config != NULL);

	npc->config = config;
	npc->refresh = true;

	/* behaviour assumed from witch's house shapeshifter */

	npc->mob.cur_stats[SKILL_ATTACK] = npc->config->attack;
	npc->mob.cur_stats[SKILL_DEFENSE] = npc->config->defense;
	npc->mob.cur_stats[SKILL_STRENGTH] = npc->config->strength;
	npc->mob.cur_stats[SKILL_HITS] = npc->config->hits;

	for (int i = 0; i < MAX_SKILL_ID; ++i) {
		npc->mob.cur_stats[i] = npc->mob.base_stats[i];
	}
}

void
npc_teleport(struct npc *npc, int x, int y)
{
	struct zone *zone_old;
	struct zone *zone_new;

	zone_old = server_find_zone(npc->mob.x, npc->mob.y);

	npc->refresh = true;
	npc->mob.moved = false;
	npc->mob.x = x;
	npc->mob.y = y;

	zone_new = server_find_zone(npc->mob.x, npc->mob.y);
	if (zone_new != zone_old) {
		if (zone_old != NULL) {
			zone_remove_npc(zone_old, npc->mob.id);
		}
		if (zone_new != NULL) {
			zone_add_npc(zone_new, npc->mob.id);
		}
	}
}

void
npc_retreat(struct npc *npc)
{
	int attempts = 0;
	double rx, ry;
	int min_x, min_y;
	int x, y;

	if (npc->mob.in_combat && npc->mob.target_player != -1) {
		struct player *p;

		p = npc->mob.server->players[npc->mob.target_player];
		if (p != NULL) {
			player_send_message(p,
			    "Your opponent is retreating");
			mob_combat_reset(&npc->mob);
			mob_combat_reset(&p->mob);
		}
	}

	do {
		rx = server_random();
		ry = server_random();

		min_x = npc->mob.x - 8;
		if (min_x < 0) {
			min_x = 0;
		}
		x = min_x + (int)(16 * rx);

		min_y = npc->mob.y - 8;
		if (min_y < 0) {
			min_y = 0;
		}
		y = min_y + (int)(16 * ry);

		if (mob_check_reachable(&npc->mob, x, y, false)) {
			break;
		}
		x = npc->mob.x;
		y = npc->mob.y;
	} while ((attempts++) < 10);

	npc->mob.action_walk = true;
	npc->mob.walk_queue_x[0] = x;
	npc->mob.walk_queue_y[0] = y;
	npc->mob.walk_queue_len = 1;
	npc->mob.walk_queue_pos = 0;
}

static void
npc_random_walk(struct npc *npc)
{
	double rx, ry;
	int x, y;
	int min_x, min_y;
	bool valid;
	int attempts;

	if (npc->busy) {
		return;
	}

	if (npc->config->wander_range == 0) {
		return;
	}

	attempts = 0;
	do {
		rx = server_random();
		ry = server_random();

		min_x = npc->spawn_x - npc->config->wander_range;
		if (min_x < 0) {
			min_x = 0;
		}
		x = min_x + (int)((npc->config->wander_range * 2) * rx);

		min_y = npc->spawn_y - npc->config->wander_range;
		if (min_y < 0) {
			min_y = 0;
		}
		y = min_y + (int)((npc->config->wander_range * 2) * ry);

		valid = true;

		switch (npc->config->move_restrict) {
		case MOVE_RESTRICT_OUTDOORS:
			valid = !npc_tile_indoors(npc, x, y);
			break;
		case MOVE_RESTRICT_INDOORS:
			valid = npc_tile_indoors(npc, x, y);
			break;
		}
	} while (!valid && (attempts++) < 10);

	npc->mob.action_walk = false;
	npc->mob.walk_queue_x[0] = x;
	npc->mob.walk_queue_y[0] = y;
	npc->mob.walk_queue_len = 1;
	npc->mob.walk_queue_pos = 0;
}

static void
npc_hunt_target(struct npc *npc)
{
	struct player *p;
	struct player *players[128];
	bool restrict_hunt = false;
	size_t n;

	if (npc->mob.cur_stats[SKILL_HITS] <= npc->config->bravery) {
		return;
	}

	if (npc->mob.server->restrict_npc_aggression) {
		restrict_hunt = true;
		if (mob_wilderness_level(&npc->mob) > 0) {
			restrict_hunt = false;
		}
	}

	n = mob_get_nearby_players(&npc->mob, players, 128);
	for (size_t i = 0; i < n; ++i) {
		p = players[i];

		if (p->mob.in_combat || p->retreat_timer > 0) {
			continue;
		}

		if (restrict_hunt &&
		    p->combat_level > (npc->config->combat_level * 2)) {
			continue;
		}

		if (!mob_within_range(&npc->mob, p->mob.x, p->mob.y,
		    npc->config->hunt_range + 2)) {
			continue;
		}

		/*
		 * ignore players that are already being chased unless
		 * we're closer than the NPC chasing them
		 */
		if (p->chased_by_npc != UINT16_MAX) {
			struct npc *npc2;

			npc2 = p->mob.server->npcs[p->chased_by_npc];
			if (npc2 != NULL &&
			    npc2->mob.target_player == p->mob.id &&
			    mob_distance(&p->mob, npc2->mob.x, npc2->mob.y) <=
			    mob_distance(&p->mob, npc->mob.x, npc->mob.y)) {
				continue;
			}

			npc2->mob.following_player = -1;
			if (npc2->mob.target_player == p->mob.id) {
				npc2->mob.target_player = -1;
			}
		}

		p->chased_by_npc = npc->mob.id;
		npc->mob.target_player = p->mob.id;
		npc->mob.following_player = p->mob.id;
		return;
	}
}

void
npc_process_movement(struct npc *npc)
{
	struct zone *zone_old;
	struct zone *zone_new;

	if (npc->busy) {
		return;
	}

	zone_old = server_find_zone(npc->mob.x, npc->mob.y);

	if (npc->mob.in_combat) {
		struct player *p;

		p = npc->mob.server->players[npc->mob.target_player];
		if (npc->mob.x != p->mob.x || npc->mob.y != p->mob.y) {
			npc->mob.action_walk = true;
			npc->mob.walk_queue_x[0] = p->mob.x;
			npc->mob.walk_queue_y[0] = p->mob.y;
			npc->mob.walk_queue_len = 1;
			npc->mob.walk_queue_pos = 0;
		}
	} else {
		if (npc->mob.following_player != -1) {
			struct player *p;

			p = npc->mob.server->players[npc->mob.following_player];
			if (p == NULL) {
				npc->mob.following_player = -1;
				return;
			}

			/*
			 * NPCs appear to be stunned slightly after retreat, see
			 * RSC 2001/replays master archive/Walk around/Misthalin- Lumbridge/walkaround- lumbridge road to varrock- road up to wheatfield digsite- dark mage aggressive - lvl 1-1-1
			 */
			if (p->retreat_timer > 0) {
				return;
			}

			/*
			 * aggressive NPCs used to be able to get stuck outside
			 * of their range, see various replays of jungle
			 * spiders on hazelmere's island
			 */
			if (mob_distance(&p->mob,
			    npc->spawn_x, npc->spawn_y) > 16) {
				p->chased_by_npc = UINT16_MAX;
				npc->mob.following_player = -1;
				npc->mob.target_player = -1;
				return;
			}
			npc->mob.action_walk = true;
			goto walk;
		} else if (npc->config->aggression > 2) {
			npc_hunt_target(npc);
		}

		if (npc->random_walk_timer == 0) {
			if (npc->mob.following_player == -1) {
				npc->random_walk_timer =
				    10.0 * server_random();
				npc_random_walk(npc);
			}
		} else {
			npc->random_walk_timer--;
		}
	}

	int pos = npc->mob.walk_queue_pos;
	if ((npc->mob.walk_queue_len - pos) <= 0) {
		return;
	}

	if (!npc->mob.action_walk) {
		int x = npc->mob.walk_queue_x[pos];
		int y = npc->mob.walk_queue_y[pos];

		switch (npc->config->move_restrict) {
		case MOVE_RESTRICT_OUTDOORS:
			if (npc_tile_indoors(npc, x, y)) {
				npc->mob.walk_queue_len = 0;
				npc->mob.walk_queue_pos = 0;
			}
			break;
		case MOVE_RESTRICT_INDOORS:
			if (!npc_tile_indoors(npc, x, y)) {
				npc->mob.walk_queue_len = 0;
				npc->mob.walk_queue_pos = 0;
			}
			break;
		}
	}

walk:
	mob_process_walk_queue(&npc->mob);

	zone_new = server_find_zone(npc->mob.x, npc->mob.y);

	if (zone_old != zone_new) {
		if (zone_old != NULL) {
			zone_remove_npc(zone_old, npc->mob.id);
		}
		if (zone_new != NULL) {
			zone_add_npc(zone_new, npc->mob.id);
		}
	}
}

static int
npc_combat_roll(struct npc *npc, struct player *defender)
{
	int def = player_get_defense_boosted(defender);

	return mob_combat_roll(npc->mob.cur_stats[SKILL_ATTACK], 0,
	    def, defender->bonus_armour,
	    npc->mob.cur_stats[SKILL_STRENGTH], 0);
}

static bool
npc_init_combat(struct npc *npc, struct player *target)
{
	if (target->mob.in_combat) {
		target->chased_by_npc = UINT16_MAX;
		npc->mob.walk_queue_pos = 0;
		npc->mob.walk_queue_len = 0;
		mob_combat_reset(&npc->mob);
		return false;
	}

	npc->mob.action_walk = true;

	if (!mob_within_range(&npc->mob, target->mob.x, target->mob.y, 2)) {
		npc->mob.following_player = target->mob.id;
		return false;
	}

	if (!mob_check_reachable(&npc->mob,
	    target->mob.x, target->mob.y, false)) {
		return false;
	}

	script_onattackbynpc(npc->mob.server->lua, target, npc);

	player_send_message(target, "You are under attack!");

	npc->mob.walk_queue_len = 0;
	npc->mob.walk_queue_pos = 0;

	/* successful catch, combat lock the target */
	target->mob.walk_queue_len = 0;
	target->mob.walk_queue_pos = 0;
	target->mob.following_player = -1;
	target->mob.following_npc = -1;

	npc->mob.following_player = -1;
	npc->mob.following_npc = -1;

	player_close_ui(target);
	player_clear_actions(target);

	npc->mob.in_combat = true;
	npc->mob.combat_next_hit = 0;
	npc->mob.combat_rounds = 0;

	target->mob.target_player = -1;
	target->mob.target_npc = npc->mob.id;
	target->mob.in_combat = true;
	target->mob.combat_rounds = 0;
	target->mob.combat_next_hit = 3;
	target->mob.dir = MOB_DIR_COMBAT_RIGHT;
	return true;
}

void
npc_process_combat(struct npc *npc)
{
	struct player *target;
	int roll;

	if (npc->mob.target_player == -1) {
		return;
	}

	target = npc->mob.server->players[npc->mob.target_player];

	if (target == NULL) {
		mob_combat_reset(&npc->mob);
		return;
	}

	if (!npc->mob.in_combat) {
		/*
		 * NPCs appear to be stunned slightly after retreat, see
		 * RSC 2001/replays master archive/Walk around/Misthalin- Lumbridge/walkaround- lumbridge road to varrock- road up to wheatfield digsite- dark mage aggressive - lvl 1-1-1
		 */
		if (target->retreat_timer == 0) {
			npc_init_combat(npc, target);
		}
		return;
	}

	assert(target->mob.in_combat);

	target->chased_by_npc = UINT16_MAX;
	npc->mob.following_player = -1;

	if (npc->mob.x != target->mob.x ||
	    npc->mob.y != target->mob.y) {
		return;
	}

	if (!npc->mob.moved) {
		npc->mob.dir = MOB_DIR_COMBAT_LEFT;
	}

	/*
	 * check out replay:
	 * rsc-preservation.xyz/Combat/Chickens [Feather Gathering] pt1
	 * for some recordings of retreating from low hits
	 */
	if (npc->mob.combat_rounds > 3 &&
	    npc->config->bravery > 0 &&
	    npc->mob.cur_stats[SKILL_HITS] <= npc->config->bravery) {
		npc_retreat(npc);
		return;
	}

	if (npc->mob.combat_next_hit > 0) {
		npc->mob.combat_next_hit--;
		return;
	}

	if (!target->prayers[PRAY_PARALYZE_MONSTER]) {
		roll = npc_combat_roll(npc, target);
		player_damage(target, NULL, roll);
	}
	npc->mob.combat_rounds++;
	npc->mob.combat_next_hit = 3;
}
