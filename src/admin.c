#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "entity.h"
#include "inventory.h"
#include "script.h"
#include "server.h"
#include "stat.h"
#include "utility.h"

void player_parse_command(struct player *, const char *);
void player_parse_mod_command(struct player *, const char *);
void player_parse_dev_command(struct player *, const char *);

void
player_parse_admin_command(struct player *p, char *str)
{
	const char *cmd;

	cmd = strtok(str, " ");
	if (cmd == NULL) {
		return;
	}
	printf("admin command: %s\n", str);
	player_parse_command(p, cmd);

	if (p->rank > 0) {
		player_parse_mod_command(p, cmd);
	}

#ifndef DEV_DISABLED
	if (p->rank > 1) {
		player_parse_dev_command(p, cmd);
	}
#endif
}

void
player_parse_command(struct player *p, const char *cmd)
{
	if (strcmp(cmd, "online") == 0) {
		char mes[128];

		(void)snprintf(mes, sizeof(mes),
		    "There are currently %d players on this world",
		    p->mob.server->player_count);
		player_send_message(p, mes);
	} else if (strcmp(cmd, "onlinelist") == 0) {
		char name[32];
		char mes[2048];
		size_t mes_len = 0, name_len;

		mes[0] = '\0';
		for (size_t i = 0; i < p->mob.server->max_player_id; ++i) {
			struct player *target;

			target = p->mob.server->players[i];
			if (target == NULL || target->name < 0) {
				continue;
			}
			mod37_namedec(target->name, name);
			name_len = strlen(name);
			/* format like name1, name2, name3... */
			if ((sizeof(mes) - mes_len) >= (name_len + 3)) {
				memcpy(mes + mes_len, name, name_len);
				mes[mes_len + name_len] = ',';
				mes[mes_len + name_len + 1] = ' ';
				mes[mes_len + name_len + 2] = '\0';
				mes_len += (name_len + 2);
			}
		}
		/* remove the comma after the last entry */
		if (mes_len >= 3) {
			mes[mes_len - 2] = '\0';
		}
		player_send_mesbox(p, mes);
	} else if (strcmp(cmd, "time") == 0) {
		char time_str[64];
		char mes[128];
		char *target_name;
		struct player *target;

		target = p;
		target_name = strtok(NULL, " ");

		if (target_name != NULL && p->rank > 0) {
			int64_t encoded = mod37_nameenc(target_name);
			target = server_find_player_name37(encoded);
		}

		if (target == NULL) {
			return;
		}

		duration_to_str(time(NULL) - p->creation_date,
		    time_str, sizeof(time_str));
		snprintf(mes, sizeof(mes),
		    "This character is %s old.", time_str);
		player_send_message(p, mes);

		duration_to_str((time(NULL) - p->login_date) + p->play_time,
		    time_str, sizeof(time_str));
		snprintf(mes, sizeof(mes), "Time played: %s", time_str);
		player_send_message(p, mes);

		duration_to_str(time(NULL) - p->login_date,
		    time_str, sizeof(time_str));
		snprintf(mes, sizeof(mes), "This session: %s", time_str);
		player_send_message(p, mes);
	} else if (strcmp(cmd, "coords") == 0) {
		char msg[64];

		(void)snprintf(msg, sizeof(msg),
		    "@que@coords: x = %u, y = %u", p->mob.x, p->mob.y);
		player_send_message(p, msg);
	} else if (strcmp(cmd, "makeover") == 0) {
		if (!p->script_active && !p->mob.in_combat) {
			player_send_design_ui(p);
		}
	} else if (strcmp(cmd, "skull") == 0) {
		player_skull(p, NULL);
	}
}

void
player_parse_mod_command(struct player *p, const char *cmd)
{
	if (strcmp(cmd, "kick") == 0) {
		char *name;
		int64_t encoded;
		struct player *target;

		name = strtok(NULL, " ");
		if (name == NULL) {
			player_send_message(p,
			    "Usage: kick name_with_spaces");
			return;
		}
		encoded = mod37_nameenc(name);
		target = server_find_player_name37(encoded);
		if (target != NULL) {
			player_send_logout(target);
		}
	} else if (strcmp(cmd, "findplayer") == 0) {
		char *name;
		int64_t encoded;
		struct player *target;

		name = strtok(NULL, " ");
		if (name == NULL) {
			player_send_message(p,
			    "Usage: findplayer name_with_spaces");
			return;
		}
		encoded = mod37_nameenc(name);
		target = server_find_player_name37(encoded);
		if (target != NULL) {
			player_teleport(p,
			    target->mob.x, target->mob.y);
		}
	} else if (strcmp(cmd, "bringplayer") == 0) {
		char *name;
		int64_t encoded;
		struct player *target;

		name = strtok(NULL, " ");
		if (name == NULL) {
			player_send_message(p,
			    "Usage: bringplayer name_with_spaces");
			return;
		}
		encoded = mod37_nameenc(name);
		target = server_find_player_name37(encoded);
		if (target != NULL) {
			player_teleport(target,
			    p->mob.x, p->mob.y);
		}
	} else if (strcmp(cmd, "uniform") == 0) {
		int weap, top, bottom;

		weap = config_find_entity("blackmace",
			p->mob.server->entity_config,
			p->mob.server->entity_config_count);
		assert(weap != -1);

		top = config_find_entity("redrobe",
			p->mob.server->entity_config,
			p->mob.server->entity_config_count);
		assert(top != -1);

		bottom = config_find_entity("blueplatemaillegs",
			p->mob.server->entity_config,
			p->mob.server->entity_config_count);
		assert(bottom != -1);

		p->sprites[ANIM_SLOT_HAND] = weap + 1;
		p->sprites[ANIM_SLOT_SHIRT] = top + 1;
		p->sprites[ANIM_SLOT_LEGS] = bottom + 1;
		p->sprites[ANIM_SLOT_TROUSERS] = 0;
		p->appearance_changed = true;
	} else if (strcmp(cmd, "hide") == 0) {
		p->hidden = !p->hidden;
		if (p->hidden) {
			player_send_message(p,
			    "You are now hidden from players. Your chat will not be visible");
		} else {
			player_send_message(p,
			    "You are now visible to players.");
		}
	} else if (strcmp(cmd, "tele") == 0) {
		char *x_str;
		char *y_str;

		x_str = strtok(NULL, " ");
		y_str = strtok(NULL, " ");

		if (x_str == NULL || y_str == NULL) {
			player_send_message(p,
			    "Usage: tele relative_x relative_y");
			return;
		}

		/* jagex coordinate syntax not yet supported */
		player_teleport(p,
		    p->mob.x + strtol(x_str, NULL, 10),
		    p->mob.y + strtol(y_str, NULL, 10));
	} else if (strcmp(cmd, "ftele") == 0) {
		char *x_str;
		char *y_str;

		x_str = strtok(NULL, " ");
		y_str = strtok(NULL, " ");

		if (x_str == NULL || y_str == NULL) {
			player_send_message(p, "Usage: ftele x y");
			return;
		}

		/* jagex coordinate syntax not yet supported */
		player_teleport(p,
		    strtol(x_str, NULL, 10),
		    strtol(y_str, NULL, 10));
	} else if (strcmp(cmd, "sysmes") == 0) {
		server_sysmes(cmd + sizeof("sysmes"));
	} else if (strcmp(cmd, "tempban") == 0) {
		char *name;
		int64_t encoded;
		struct player *target;

		name = strtok(NULL, " ");
		if (name == NULL) {
			player_send_message(p,
			    "Usage: tempban name_with_spaces");
			return;
		}
		encoded = mod37_nameenc(name);
		target = server_find_player_name37(encoded);
		if (target != NULL) {
			target->ban_end_date = time(NULL) + ((24 * 60) * 60);
			player_send_logout(target);
		}
	} else if (strcmp(cmd, "permban") == 0) {
		char *name;
		int64_t encoded;
		struct player *target;

		name = strtok(NULL, " ");
		if (name == NULL) {
			player_send_message(p,
			    "Usage: permban name_with_spaces");
			return;
		}
		encoded = mod37_nameenc(name);
		target = server_find_player_name37(encoded);
		if (target != NULL) {
			target->ban_end_date = time(NULL) +
			    ((64000 * 60) * 60);
			player_send_logout(target);
		}
	} else if (strcmp(cmd, "reload") == 0) {
		script_shutdown(p->mob.server->lua);
		p->mob.server->lua = script_init(p->mob.server);
		for (size_t i = 0; i < p->mob.server->max_player_id; ++i) {
			struct player *target = p->mob.server->players[i];
			if (target != NULL) {
				target->script_active = false;
				player_send_message(target,
				    "@red@Script engine reloaded");
			}
		}
		for (size_t i = 0; i < p->mob.server->max_npc_id; ++i) {
			struct npc *target = p->mob.server->npcs[i];
			if (target != NULL) {
				target->busy = false;
			}
		}
	} else if (strcmp(cmd, "saveall") == 0) {
		for (size_t i = 0; i < p->mob.server->max_player_id; ++i) {
			struct player *target = p->mob.server->players[i];
			if (target != NULL) {
				player_save(target);
			}
		}
	} else if (strcmp(cmd, "noclip") == 0) {
		p->mob.noclip = !p->mob.noclip;
		player_send_message(p,
		    p->mob.noclip ? "Noclipping on" : "Noclipping off");
	}
}

void
player_parse_dev_command(struct player *p, const char *cmd)
{
	if (strcmp(cmd, "give") == 0) {
		struct item_config *item_config;
		char *item_str;
		char *amount_str;
		char mes[64];
		int amount;

		item_str = strtok(NULL, " ");
		amount_str = strtok(NULL, " ");

		if (item_str == NULL || amount_str == NULL) {
			player_send_message(p, "Usage: give itemname amount");
			return;
		}

		for (size_t i = 0; item_str[i] != '\0'; ++i) {
			if (item_str[i] == '_') {
				item_str[i] = ' ';
			}
		}
		item_config = server_find_item_config(item_str);
		if (item_config == NULL) {
			(void)snprintf(mes, sizeof(mes),
			    "No such item: %s", item_str);
			player_send_message(p, mes);
			return;
		}
		amount = strtol(amount_str, NULL, 10);
		if (item_config->weight > 0 &&
		    (MAX_INV_SIZE - p->inv_count) < amount) {
			player_send_message(p, "Not enough space!");
			return;
		}
		player_inv_give(p, item_config, amount);
	} else if (strcmp(cmd, "empty") == 0) {
		p->inv_count = 0;
		player_send_inv(p);
	} else if (strcmp(cmd, "advancestat") == 0) {
		char *stat_str;
		char *xp_str;
		int stat = -1;
		int xp = 0;

		stat_str = strtok(NULL, " ");
		xp_str = strtok(NULL, " ");

		if (stat_str == NULL || xp_str == NULL) {
			player_send_message(p, "Usage: advancestat attack 4000");
			return;
		}

		for (int i = 0; i < MAX_SKILL_ID; ++i) {
			if (strcasecmp(stat_str, skill_names[i]) == 0) {
				stat = i;
				break;
			}
		}

		if (stat == -1) {
			char mes[32];

			(void)snprintf(mes, sizeof(mes),
			    "Unknown stat name: %s", stat_str);
			player_send_message(p, mes);
			return;
		}

		xp = strtol(xp_str, NULL, 10);

		stat_advance(p, stat, xp, 0);
	} else if (strcmp(cmd, "getvar") == 0) {
		char *varname;
		int32_t value;
		char msg[64];

		varname = strtok(NULL, " ");

		if (varname == NULL) {
			player_send_message(p, "Usage: getvar varname");
			return;
		}

		value = player_variable_get(p, varname);

		(void)snprintf(msg, sizeof(msg),
			"@que@%s=%d", varname, value);
		player_send_message(p, msg);
	} else if (strcmp(cmd, "setvar") == 0) {
		char *varname;
		char *value_str;
		int32_t value;

		varname = strtok(NULL, " ");
		value_str = strtok(NULL, " ");

		if (varname == NULL || value_str == NULL) {
			player_send_message(p, "Usage: setvar varname value");
			return;
		}

		value = strtol(value_str, NULL, 10);

		player_variable_set(p, varname, value);
	} else if (strcmp(cmd, "listvar") == 0) {
		if (p->variable_count == 0) {
			player_send_message(p, "You have no custom variables");
			return;
		}
		for (size_t i = 0; i < p->variable_count; i++) {
			char msg[64];

			(void)snprintf(msg, sizeof(msg),
				"@que@%s=%d", p->variables[i].name,
				p->variables[i].value);
			player_send_message(p, msg);
		}
	} else if (strcmp(cmd, "openshop") == 0) {
		char *varname;

		varname = strtok(NULL, " ");

		if (varname == NULL) {
			player_send_message(p, "Usage: openshop varname");
			return;
		}

		player_send_shop(p, varname);
	} else if (strcmp(cmd, "addnpc") == 0) {
		struct npc_config *config;
		char *name;

		name = strtok(NULL, " ");
		if (name == NULL) {
			player_send_message(p, "Usage: addnpc name");
			return;
		}

		for (size_t i = 0; name[i] != '\0'; ++i) {
			if (name[i] == '_') {
				name[i] = ' ';
			}
		}

		config = server_find_npc_config(name);
		if (config == NULL) {
			player_send_message(p, "Warning: npc not found");
			return;
		}

		server_add_npc(config->id, p->mob.x, p->mob.y);
	}
}
