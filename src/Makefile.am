AUTOMAKE_OPTIONS = subdir-objects foreign

bin_PROGRAMS =	rscsundae

AM_CPPFLAGS = -Iext/libjag/include
AM_CPPFLAGS += $(LUA_CFLAGS)
AM_CPPFLAGS += $(INIH_CFLAGS)

rscsundae_SOURCES = \
	admin.c \
	bank.c \
	buffer.c \
	mob.c \
	netio.c \
	player.c \
	inventory.c \
	npc.c \
	script.c \
	server.c \
	settings.c \
	shop.c \
	stat.c \
	trade.c \
	utility.c \
	zone.c \
	config/config.c \
	config/text.c \
	ext/flea.c \
	ext/isaac.c \
	ext/libjag/lib/jag_bzip2_decompress.c \
	ext/libjag/lib/jag_find_entry.c \
	ext/libjag/lib/jag_hash_entry_name.c  \
	ext/libjag/lib/jag_map_read_jm.c \
	ext/libjag/lib/jag_read_entry.c \
	ext/libjag/lib/jag_read_header.c \
	ext/libjag/lib/jag_unpack_entry.c \
	ext/libjag/lib/jag_unpack_file.c \
	ext/reallocarr.c \
	protocol/incoming.c \
	protocol/opcodes201.c \
	protocol/opcodes203.c \
	protocol/outgoing.c

if ! HAVE_SYSTEM_INIH
AM_CPPFLAGS += -Iext/inih
rscsundae_SOURCES += ext/inih/ini.c
endif

if HAVE_KQUEUE
rscsundae_SOURCES += loop-kqueue.c
else
if HAVE_POLL
rscsundae_SOURCES += loop-poll.c
else
rscsundae_SOURCES += loop-select.c
endif
endif

rscsundae_LDADD = -lm
rscsundae_LDADD += $(LUA_LIBS)
rscsundae_LDADD += $(INIH_LIBS)

if HAVE_LIBCRYPTO
AM_CPPFLAGS += -DHAVE_LIBCRYPTO
AM_CPPFLAGS += $(LIBCRYPTO_CFLAGS)
rscsundae_LDADD += $(LIBCRYPTO_LIBS)
endif

if HAVE_LIBTOM
rscsundae_SOURCES += protocol/rsa-libtom.c
AM_CPPFLAGS += -DWITH_RSA_LIBTOM
AM_CPPFLAGS += $(LIBTOMMATH_CFLAGS)
rscsundae_LDADD += $(LIBTOMMATH_LIBS)
else
rscsundae_SOURCES += protocol/rsa-openssl.c
AM_CPPFLAGS += -DWITH_RSA_OPENSSL
# only for testing, so slow it's unusable
#else
#rscsundae_SOURCES += protocol/rsa-tiny.c
#AM_CPPFLAGS += -Iext/tiny-bignum-c
#AM_CPPFLAGS += -DWITH_RSA_TINY
endif

rscsundae_SOURCES += persistence/database-sqlite.c
rscsundae_LDADD += $(SQLITE3_LIBS)
AM_CPPFLAGS += $(SQLITE3_CFLAGS)

rscsundae_SOURCES += persistence/pwhash-argon2.c
rscsundae_LDADD += $(LIBARGON2_LIBS)
AM_CPPFLAGS += $(LIBARGON2_CFLAGS)
