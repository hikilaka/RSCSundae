#include <stdlib.h>
#include <string.h>
#include "server.h"

int
server_parse_settings(void *user, const char *section,
   const char *name, const char *value)
{
	struct server *s = (struct server *)user;

	if (strcmp(section, "server") == 0) {
		if (strcmp(name, "name") == 0) {
			s->name = strdup(value);
		} else if (strcmp(name, "bind_addr") == 0) {
			s->bind_addr = strdup(value);
		} else if (strcmp(name, "port") == 0) {
			s->port = strtol(value, NULL, 10);
		} else if (strcmp(name, "rsa_exponent") == 0) {
			s->rsa_exponent = strdup(value);
		} else if (strcmp(name, "rsa_modulus") == 0) {
			s->rsa_modulus = strdup(value);
		} else if (strcmp(name, "log_packets") == 0) {
			s->log_packets = (strtol(value, NULL, 10) != 0);
		} else if (strcmp(name, "register_required") == 0) {
			s->register_required = (strtol(value, NULL, 10) != 0);
		} else if (strcmp(name, "client_registration") == 0) {
			s->client_registration =
			    (strtol(value, NULL, 10) != 0);
		} else if (strcmp(name, "max_per_ip") == 0) {
			s->max_per_ip = strtol(value, NULL, 10);
		} else if (strcmp(name, "protocol110") == 0) {
			s->protocol110 =
			    (strtol(value, NULL, 10) != 0);
		} else if (strcmp(name, "protocol204") == 0) {
			s->protocol204 =
			    (strtol(value, NULL, 10) != 0);
		} else {
			return 0;
		}
	} else if (strcmp(section, "gameplay") == 0) {
		if (strcmp(name, "maps_revision") == 0) {
			s->maps_rev = strtol(value, NULL, 10);
		} else if (strcmp(name, "config_revision") == 0) {
			s->config_rev = strtol(value, NULL, 10);
		} else if (strcmp(name, "start_tile_x") == 0) {
			s->start_tile_x = strtol(value, NULL, 10);
		} else if (strcmp(name, "start_tile_y") == 0) {
			s->start_tile_y = strtol(value, NULL, 10);
		} else if (strcmp(name, "xp_multiplier") == 0) {
			s->xp_multiplier = strtol(value, NULL, 10);
		} else if (strcmp(name, "check_reagents") == 0) {
			s->cast_without_runes = (strtol(value, NULL, 10) == 0);
		} else if (strcmp(name, "spell_timer") == 0) {
			s->spell_timer = (strtol(value, NULL, 10) != 0);
		} else if (strcmp(name, "restrict_npc_aggression") == 0) {
			s->restrict_npc_aggression =
			    (strtol(value, NULL, 10) != 0);
		} else if (strcmp(name, "movement_timer") == 0) {
			s->movement_timer =
			    (strtol(value, NULL, 10) != 0);
		} else if (strcmp(name, "untradables") == 0) {
			s->untradables =
			    (strtol(value, NULL, 10) != 0);
		} else if (strcmp(name, "ranged_xp_per_hit") == 0) {
			s->ranged_xp_per_hit =
			    (strtol(value, NULL, 10) != 0);
		} else {
			return 0;
		}
	} else if (strcmp(section, "database") == 0) {
		if (strcmp(name, "sqlite_filename") == 0) {
			s->database.filename = strdup(value);
		} else if (strcmp(name, "sqlite_wal") == 0) {
			s->database.use_wal = (strtol(value, NULL, 10) != 0);
		} else {
			return 0;
		}
	} else {
		return 0;
	}
	return 1;
}
