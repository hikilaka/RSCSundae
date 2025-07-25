#ifndef ENTITY_H
#define ENTITY_H
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include "zone.h"
#include "ext/isaac.h"

#define PLAYER_BUFSIZE		(5000)

#define PLANE_WIDTH		(2304)
#define PLANE_HEIGHT		(1776)
#define PLANE_LEVEL_INC		(944)

#define MAX_KNOWN_PLAYERS	(255)
#define MAX_KNOWN_NPCS		(255)
#define MAX_CHAT_LEN		(80)
#define MAX_SKILL_ID		(16)
#define MAX_CLIENT_SETTINGS	(3)
#define MAX_INV_SIZE		(30)
#define MAX_OFFER_SIZE		(12)
#define MAX_MULTI_SIZE		(5)
#define MAX_KNOWN_ZONES		(64)
#define MAX_BANK_SIZE		(48)

/* number three comes from 2004scape research */
#define MAX_CACHED_ATTACKERS	(3)

/* signed to accomodate java client */
#define MAX_STACK_SIZE		(INT32_MAX)

/* final client supports 100 ignore and 200 friend entries */
#define MAX_FRIENDS		(200)
#define MAX_IGNORE		(100)

/* restriction of 204 protocol */
#define MAX_USERNAME_LEN	(20)

#define MAX_ENTITY_SPRITES	(12)

#define WALK_QUEUE_LEN		(16)

#define PLAYER_VAR_INC_SIZE	(16)

struct server;
struct ranctx;
struct bound;
struct loc;
struct ground_item;

enum login_stage {
	LOGIN_STAGE_ZERO	= 0,
	LOGIN_STAGE_SESSION	= 1,
	LOGIN_STAGE_GOT_LOGIN	= 2,
};

struct bank_item {
	uint16_t id;
	uint32_t amount;
};

enum action {
	ACTION_NONE		= 0,
	ACTION_NPC_ATTACK	= 1,
	ACTION_NPC_USEWITH	= 2,
	ACTION_NPC_TALK		= 3,
	ACTION_NPC_CAST		= 4,
	ACTION_INV_DROP		= 5,
	ACTION_INV_OP1		= 6,
	ACTION_INV_USEWITH	= 7,
	ACTION_INV_CAST		= 8,
	ACTION_ITEM_TAKE	= 9,
	ACTION_ITEM_USEWITH	= 10,
	ACTION_ITEM_CAST	= 11,
	ACTION_PLAYER_ATTACK	= 12,
	ACTION_PLAYER_CAST	= 13,
	ACTION_BOUND_OP1	= 14,
	ACTION_BOUND_OP2	= 15,
	ACTION_BOUND_USEWITH	= 16,
	ACTION_LOC_USEWITH	= 17,
	ACTION_LOC_OP1		= 18,
	ACTION_LOC_OP2		= 19,
	ACTION_SELF_CAST	= 20,
};

enum trade_state {
	TRADE_STATE_NONE	= 0,
	TRADE_STATE_ACCEPTED	= 1,
	TRADE_STATE_CONFIRMED	= 2,
};

enum skill {
	SKILL_ATTACK		= 0,
	SKILL_DEFENSE		= 1,
	SKILL_STRENGTH		= 2,
	SKILL_HITS		= 3,
	SKILL_RANGED		= 4,
	SKILL_PRAYER		= 5,
	SKILL_MAGIC		= 6,
	SKILL_COOKING		= 7,
	SKILL_WOODCUTTING	= 8,
	SKILL_FLETCHING		= 9,
	SKILL_FISHING		= 10,
	SKILL_FIREMAKING	= 11,
	SKILL_CRAFTING		= 12,
	SKILL_SMITHING		= 13,
	SKILL_MINING		= 14,
	SKILL_HERBLAW		= 15
};

enum prayer {
	PRAY_THICK_SKIN			= 0,
	PRAY_BURST_OF_STRENGTH		= 1,
	PRAY_CLARITY_OF_THOUGHT		= 2,
	PRAY_ROCK_SKIN			= 3,
	PRAY_SUPERHUMAN_STRENGTH	= 4,
	PRAY_IMPROVED_REFLEXES		= 5,
	PRAY_RAPID_RESTORE		= 6,
	PRAY_RAPID_HEAL			= 7,
	PRAY_PROTECT_ITEM		= 8,
	PRAY_STEEL_SKIN			= 9,
	PRAY_ULTIMATE_STRENGTH		= 10,
	PRAY_INCREDIBLE_REFLEXES	= 11,
	PRAY_PARALYZE_MONSTER		= 12,
	PRAY_PROTECT_FROM_MISSILES	= 13,
};

#define MAX_PRAYERS	(PRAY_PROTECT_FROM_MISSILES + 1)

enum combat_style {
	COMBAT_STYLE_CONTROLLED	= 0,
	COMBAT_STYLE_AGGRESSIVE	= 1,
	COMBAT_STYLE_ACCURATE	= 2,
	COMBAT_STYLE_DEFENSIVE	= 3,
};

enum chat_type {
	CHAT_TYPE_NONE		= 0,
	CHAT_TYPE_PUBLIC	= 1,
	CHAT_TYPE_QUEST		= 2,
};

/* TODO: expand with a they/them option */
enum mobgender {
	MOB_GENDER_MALE		= 1,
	MOB_GENDER_FEMALE	= 2,
};

enum mobdir {
	MOB_DIR_NORTH		= 0,
	MOB_DIR_NORTHWEST	= 1,
	MOB_DIR_WEST		= 2,
	MOB_DIR_SOUTHWEST	= 3,
	MOB_DIR_SOUTH		= 4,
	MOB_DIR_SOUTHEAST	= 5,
	MOB_DIR_EAST		= 6,
	MOB_DIR_NORTHEAST	= 7,
	/*
	 * attacker is shown on right, defender on left
	 * except NPCs are always on the left
	 */
	MOB_DIR_COMBAT_LEFT	= 8,
	MOB_DIR_COMBAT_RIGHT	= 9
};

struct mob {
	struct server *server;
	uint16_t x, y;
	uint16_t id;
	uint16_t walk_queue_x[WALK_QUEUE_LEN];
	uint16_t walk_queue_y[WALK_QUEUE_LEN];
	uint16_t walk_queue_pos;
	uint16_t walk_queue_len;
	uint8_t is_npc;
	uint8_t action_walk;
	uint8_t dir;
	uint8_t prev_dir;
	uint8_t moved;
	uint8_t in_combat;
	uint8_t damage;
	uint8_t noclip;
	uint32_t combat_rounds;
	uint64_t damage_timer;
	uint8_t combat_next_hit;
	uint8_t cur_stats[MAX_SKILL_ID];
	uint8_t base_stats[MAX_SKILL_ID];
	uint8_t chat_len;
	uint8_t chat_compressed_len;
	char chat_enc[MAX_CHAT_LEN];
	char chat_compressed[MAX_CHAT_LEN];
	int16_t target_player;
	int16_t target_npc;
	int16_t following_player;
	int16_t following_npc;
	uint16_t movement_timer;
};

enum animslot {
	ANIM_SLOT_HEAD		= 0,
	ANIM_SLOT_BODY		= 1,
	ANIM_SLOT_LEGS		= 2,
	ANIM_SLOT_OFFHAND	= 3,
	ANIM_SLOT_HAND		= 4,
	ANIM_SLOT_HAT		= 5,
	ANIM_SLOT_SHIRT		= 6,
	ANIM_SLOT_TROUSERS	= 7,
	ANIM_SLOT_NECK		= 8,
	ANIM_SLOT_SHOES		= 9,
	ANIM_SLOT_GLOVES	= 10,
	ANIM_SLOT_BACK		= 11,
};

struct invitem {
	uint16_t id;
	uint32_t stack;
	uint8_t worn;
};

struct playervar {
	char *name;
	uint32_t value;
};

struct effect {
	uint8_t id;
	uint16_t x;
	uint16_t y;
};

struct npc {
	struct mob mob;
	struct npc_config *config;
	uint16_t talk_target;
	uint16_t respawn_time;
	uint16_t random_walk_timer;
	uint16_t spawn_x;
	uint16_t spawn_y;
	uint8_t busy;
	uint8_t regen_timer;
	uint8_t refresh;
};

enum rpg_class {
	CLASS_ADVENTURER	= 0,
	CLASS_WARRIOR		= 1,
	CLASS_WIZARD		= 2,
	CLASS_RANGER		= 3,
	CLASS_MINER		= 4
};

struct player {
	struct mob mob;
	int sock;
	int16_t known_players[MAX_KNOWN_PLAYERS];
	uint8_t known_players_seen[MAX_KNOWN_PLAYERS];
	uint16_t known_player_count;
	int16_t known_npcs[MAX_KNOWN_NPCS];
	uint16_t known_npc_count;
	uint8_t tmpbuf[PLAYER_BUFSIZE]; /* used for packet construction */
	uint8_t inbuf[PLAYER_BUFSIZE];
	char password[32]; /* cleared after registration */
	char address[64];
	uint16_t inbuf_len;
	uint16_t inbuf_processed;
	uint8_t outbuf[PLAYER_BUFSIZE];
	uint16_t outbuf_len;
	uint16_t outbuf_written;
	int64_t session_id;
	int64_t name;
	int16_t trading_player;
	uint8_t rank;
	uint8_t protocol_rev;
	uint8_t login_stage;
	uint8_t stats_changed;
	uint8_t bonus_changed;
	uint8_t appearance_changed;
	uint8_t plane_changed;
	uint8_t prayers_changed;
	uint8_t inv_changed;
	uint8_t sprites_base[MAX_ENTITY_SPRITES];
	uint8_t sprites[MAX_ENTITY_SPRITES];
	uint8_t client_settings[MAX_CLIENT_SETTINGS];
	uint8_t combat_level;
	uint8_t gender;
	uint8_t hair_colour;
	uint8_t top_colour;
	uint8_t leg_colour;
	uint8_t skin_colour;
	uint8_t rpg_class;
	uint8_t xp_multiplier;
	uint8_t skulled;
	uint16_t skull_timer;
	uint64_t drain_counter;
	uint64_t next_drain;
	uint8_t chat_type;
	uint8_t ui_multi_open;
	uint8_t ui_bank_open;
	uint8_t ui_design_open;
	uint8_t ui_trade_open;
	uint8_t block_public;
	uint8_t block_private;
	uint8_t block_trade;
	uint8_t block_duel;
	uint8_t logout_confirmed;
	uint8_t hidden;
	uint64_t last_packet;
	uint32_t experience[MAX_SKILL_ID];
	uint8_t quest_points;
	int64_t friend_list[MAX_FRIENDS];
	int64_t ignore_list[MAX_IGNORE];
	uint16_t friend_count;
	uint16_t ignore_count;
	uint8_t combat_style;
	uint8_t bonus_armour;
	uint8_t bonus_weaponaim;
	uint8_t bonus_weaponpower;
	uint8_t bonus_magic;
	uint8_t bonus_prayer;
	uint8_t inv_count;
	struct invitem inventory[MAX_INV_SIZE];
	uint8_t offer_count;
	uint8_t partner_offer_changed;
	uint8_t trade_state;
	struct invitem trade_offer[MAX_OFFER_SIZE];
	uint8_t prayers[MAX_PRAYERS];
	uint16_t prayer_drain;
	size_t known_loc_count;
	size_t known_loc_max;
	struct loc *known_locs;
	size_t known_bound_count;
	size_t known_bound_max;
	struct bound *known_bounds;
	struct ground_item *known_items;
	size_t known_item_count;
	size_t known_item_max;
	uint64_t last_update;
	struct projectile_config *projectile;
	uint16_t projectile_sprite;
	uint16_t projectile_target_player;
	uint16_t projectile_target_npc;
	uint8_t action;
	struct spell_config *spell;
	uint16_t action_npc;
	uint16_t action_player;
	uint16_t action_slot;
	uint16_t action_slot2;
	struct ground_item action_item;
	struct bound action_bound;
	struct loc action_loc;
	uint16_t bubble_id;
	uint8_t ranged_timer;
	uint8_t retreat_timer;
	uint8_t spell_timer;
	uint8_t teleported;
	uint16_t bank_count;
	struct bank_item bank[MAX_BANK_SIZE];
	struct shop_config *shop;
	struct isaac isaac_in;
	struct isaac isaac_out;
	uint8_t isaac_ready;
	uint8_t script_active;
	struct playervar *variables;
	size_t variable_count;
	size_t variable_max;
	time_t creation_date;
	time_t login_date;
	time_t play_time;
	time_t ban_end_date;
	uint16_t chased_by_npc;
	uint16_t save_timer;
	uint16_t player_targets[MAX_CACHED_ATTACKERS];
	uint16_t player_aggressors[MAX_CACHED_ATTACKERS];
	uint64_t player_targets_time[MAX_CACHED_ATTACKERS];
	uint64_t player_aggressors_time[MAX_CACHED_ATTACKERS];
	FILE *packet_log;
};

/* mob.c */
bool mob_within_range(struct mob *, int, int, int);
int mob_distance(struct mob *, int, int);
void mob_face(struct mob *, int, int);
int mob_combat_roll(int, int, int, int, int, int);
int mob_wilderness_level(struct mob *);
size_t mob_get_nearby_npcs(struct mob *, struct npc **, size_t, bool);
size_t mob_get_nearby_players(struct mob *, struct player **, size_t);
void mob_combat_reset(struct mob *);
uint32_t mob_combat_xp(struct mob *);
size_t mob_get_nearby_locs(struct mob *, struct loc *, size_t);
size_t mob_get_nearby_bounds(struct mob *, struct bound *, size_t);
bool mob_reached_item(struct mob *, struct ground_item *);
bool mob_reached_bound(struct mob *, struct bound *);
bool mob_reached_loc(struct mob *, struct loc *);
void mob_die(struct mob *);
void mob_process_walk_queue(struct mob *);
struct npc *mob_find_nearby_npc(struct mob *, const char *, bool);
bool mob_check_reachable(struct mob *, int, int, bool);

/* player.c */
struct player *player_create(struct server *, int, const char *);
int player_load(struct player *);
void player_process_combat(struct player *);
void player_process_movement(struct player *);
void player_die(struct player *, struct player *p);
void player_close_ui(struct player *);
void player_save(struct player *);
void player_destroy(struct player *);
void player_recalculate_equip(struct player *);
void player_recalculate_combat_level(struct player *);
bool player_has_ignore(struct player *, int64_t);
bool player_has_friend(struct player *, int64_t);
bool player_public_chat_visible(struct player *, int64_t);
bool player_is_blocked(struct player *, int64_t, bool);
int player_retreat(struct player *);
int player_add_ignore(struct player *, int64_t);
int player_add_friend(struct player *, int64_t);
int player_remove_ignore(struct player *, int64_t);
int player_remove_friend(struct player *, int64_t);
int player_wear(struct player *, int);
int player_unwear(struct player *, int);
void player_award_combat_xp(struct player *, struct mob *);
void player_slow_restore(struct player *);
void player_rapid_restore(struct player *);
void player_reset_prayers(struct player *);
void player_prayer_enable(struct player *, int);
void player_prayer_disable(struct player *, int);
void player_prayer_drain(struct player *);
bool player_has_known_loc(struct player *, int, int);
void player_add_known_loc(struct player *, struct loc *);
void player_remove_known_loc(struct player *, size_t);
bool player_has_known_bound(struct player *, int, int, int);
void player_add_known_bound(struct player *, struct bound *);
bool player_has_known_item(struct player *, uint64_t);
bool player_can_see_item(struct player *, struct ground_item *);
size_t player_get_nearby_items(struct player *, struct ground_item *, size_t);
void player_clear_actions(struct player *);
void player_process_action(struct player *);
bool player_has_reagents(struct player *, struct spell_config *);
bool player_can_cast(struct player *, struct spell_config *);
void player_damage(struct player *, struct player *, int);
void player_shoot_pvp(struct player *, struct projectile_config *,
    struct player *);
void player_shoot_pvm(struct player *, struct projectile_config *,
    struct npc *);
void player_skull(struct player *, struct player *);
void player_teleport(struct player *, int, int);
void player_init_class(struct player *);
void player_init_adventurer(struct player *);
int player_get_attack_boosted(struct player *);
int player_get_defense_boosted(struct player *);
int player_get_strength_boosted(struct player *);
int32_t player_variable_get(struct player *, const char *);
void player_variable_set(struct player *, const char *, int32_t);
void player_takeobject(struct player *, struct ground_item *);
void player_attempt_logout(struct player *, bool);
void player_send_welcome(struct player *);

/* admin.c */
void player_parse_admin_command(struct player *, char *);

/* bank.c */
void player_deposit(struct player *, uint16_t, uint32_t);
void player_withdraw(struct player *, uint16_t, uint32_t);

/* incoming.c */
int player_parse_incoming(struct player *);

/* outgoing.c */
int player_send_plane_init(struct player *);
int player_send_movement(struct player *);
int player_send_npc_movement(struct player *);
int player_send_npc_appearance_update(struct player *);
int player_send_appearance_update(struct player *);
int player_send_design_ui(struct player *);
int player_send_logout(struct player *);
int player_send_logout_reject(struct player *);
int player_send_message(struct player *, const char *);
int player_send_stat(struct player *, int);
int player_send_stat_xp(struct player *, int);
int player_send_init_stats(struct player *);
int player_send_client_settings(struct player *);
int player_send_privacy_settings(struct player *);
int player_send_init_friends(struct player *);
int player_send_init_ignore(struct player *);
int player_send_pm(struct player *, int64_t, const char *);
int player_send_death(struct player *);
int player_send_inv(struct player *);
int player_send_inv_slot(struct player *, int);
int player_send_inv_remove(struct player *, int);
int player_send_equip_bonuses(struct player *);
int player_send_prayers(struct player *);
int player_send_locs(struct player *);
int player_send_bounds(struct player *);
int player_send_ground_items(struct player *);
int player_send_trade_open(struct player *);
int player_send_partner_trade_offer(struct player *);
int player_send_close_trade(struct player *);
int player_send_trade_state(struct player *);
int player_send_trade_state_remote(struct player *);
int player_send_trade_confirm(struct player *);
int player_send_show_multi(struct player *, const char **, uint8_t);
int player_send_hide_multi(struct player *);
int player_send_show_bank(struct player *);
int player_send_close_bank(struct player *);
int player_send_shop(struct player *, const char *);
int player_send_close_shop(struct player *);
int player_send_quests(struct player *);
int player_notify_friend_online(struct player *, int64_t);
int player_notify_friend_offline(struct player *, int64_t);
int player_send_effect(struct player *, struct effect *);
int player_send_mesbox(struct player *, const char *);

/* npc.c */
void npc_retreat(struct npc *);
void npc_damage(struct npc *, struct player * , int);
void npc_change(struct npc *, struct npc_config *);
void npc_teleport(struct npc *, int, int);
void npc_die(struct npc *, struct player *);
void npc_process_movement(struct npc *);
void npc_process_combat(struct npc *);

#endif
