#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include "stat.h"
#include "server.h"

#ifndef MAX_SKILL_LEVEL
#define MAX_SKILL_LEVEL	(99)
#endif

/* compatibility with java clients */
#ifndef MAX_EXPERIENCE
#define MAX_EXPERIENCE	(INT32_MAX)
#endif

/*
 * the spelling here is not the same as the client,
 * since original RSC had some inconsistencies there
 */
const char *skill_names[] = {
	"attack", "defence", "strength", "hitpoints", "ranged", "prayer",
	"magic", "cooking", "woodcutting", "fletching", "fishing",
	"firemaking", "crafting", "smithing", "mining", "herblaw"
};

static uint32_t xp_table[MAX_SKILL_LEVEL];

void
stat_calculate_table(void)
{
	uint32_t xp = 0;

	for (int i = 0; i < MAX_SKILL_LEVEL; ++i) {
		int next = i + 1;
		xp += (int)(next + (300.0 * pow(2.0, next / 7.0)));
		xp_table[i] = xp & 0xffffffc;
	}
}

int
xp_to_level(uint32_t xp)
{
	int level = 1;

	for (int i = 0; i < MAX_SKILL_LEVEL; ++i) {
		if (xp < xp_table[i]) {
			break;
		}
		level = i + 2;
	}
	if (level > MAX_SKILL_LEVEL) {
		level = MAX_SKILL_LEVEL;
	}
	return level;
}

bool
stat_is_combat(int stat)
{
	return stat == SKILL_ATTACK ||
	    stat == SKILL_DEFENSE ||
	    stat == SKILL_STRENGTH ||
	    stat == SKILL_HITS ||
	    stat == SKILL_MAGIC ||
	    stat == SKILL_RANGED ||
	    stat == SKILL_PRAYER;
}

/* corresponds to runescript ifstatrandom */
bool
stat_random(struct mob *mob, int stat,
    double base_probability, double top_probability)
{
	double level;
	int low, high, chance, random;

	assert(mob != NULL);
	assert(stat < MAX_SKILL_ID);

	level = mob->cur_stats[stat];

	/*
	 * interpolate
	 * do not modify for increased level caps, since scripts expect
	 * a 0-100 range
	 */
	low = (int)(base_probability * (99.0 - level) / 98.0);
	high = (int)(top_probability * (level - 1.0) / 98.0);
	chance = (low + high) + 1;

	random = server_random() * 256.0;
	return random <= chance;
}

/* corresponds to runescript advancestat */
void
stat_advance(struct player *player, int stat,
    int base_xp, int proportion_xp)
{
	int cur, inc, level;

	assert(stat < MAX_SKILL_ID);

	cur = player->experience[stat];
	inc = base_xp + (proportion_xp * player->mob.base_stats[stat]);

	inc *= player->mob.server->xp_multiplier;
	inc *= player->xp_multiplier;

	if ((MAX_EXPERIENCE - cur) > inc) {
		player->experience[stat] = cur + inc;
	} else {
		player->experience[stat] = MAX_EXPERIENCE;
	}

	level = xp_to_level(player->experience[stat]);
	if (level > player->mob.base_stats[stat]) {
		char msg[64];
		int gained;

		gained = level - player->mob.base_stats[stat];
		(void)snprintf(msg, sizeof(msg),
		    "@gre@You just advanced %d %s level!",
		    gained, skill_names[stat]);
		player_send_message(player, msg);
		player->mob.cur_stats[stat] += gained;
		player->mob.base_stats[stat] = level;
		player_send_stat(player, stat);

		if (stat_is_combat(stat)) {
			player_recalculate_combat_level(player);
		}
	} else {
		player_send_stat_xp(player, stat);
	}
}

/* corresponds to runescript addstat */
void
stat_add(struct mob *mob, int stat, int constant, int percent)
{
	int p, new, max;

	assert(stat < MAX_SKILL_ID);

	/*
	 * function is documented as using the current (affected)
	 * stats in the percentage calculation but observation of
	 * the actual game shows otherwise.
	 */
	p = (int)((mob->base_stats[stat] * (double)percent) / 100.0);
	new = mob->cur_stats[stat] + constant + p;
	max = mob->base_stats[stat] + constant + p;
	mob->cur_stats[stat] = (uint16_t)(new > max ? max : new);
}

/* corresponds to runescript substat */
void
stat_remove(struct mob *mob, int stat, int constant, int percent)
{
	int p, new;

	assert(stat < MAX_SKILL_ID);

	/*
	 * precent reduction is based on current level, see
	 * https://classic.runescape.wiki/w/User:Stormykins/Dragonfire
	 */
	p = (int)((mob->cur_stats[stat] * (double)percent) / 100.0);
	new = mob->cur_stats[stat] - constant - p;
	mob->cur_stats[stat] = (uint16_t)(new < 0 ? 0 : new);
}

/* corresponds to runescript healstat */
void
stat_heal(struct mob *mob, int stat, int constant, int percent)
{
	int max = mob->base_stats[stat];

	/*
	 * in the case it's already boosted we preserve that boost,
	 * otherwise don't allow exceeding the base level
	 */
	if (mob->cur_stats[stat] > mob->base_stats[stat]) {
		max = mob->cur_stats[stat];
	} else {
		max = mob->base_stats[stat];
	}

	stat_add(mob, stat, constant, percent);

	if (mob->cur_stats[stat] > max) {
		mob->cur_stats[stat] = max;
	}
}

/* corresponds to runescript ifstatup */
bool
stat_up(struct mob *mob, int stat)
{
	assert(stat < MAX_SKILL_ID);
	return mob->cur_stats[stat] > mob->base_stats[stat];
}

/* corresponds to runescript ifstatdown */
bool
stat_down(struct mob *mob, int stat)
{
	assert(stat < MAX_SKILL_ID);
	return mob->cur_stats[stat] < mob->base_stats[stat];
}
