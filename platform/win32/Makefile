CC=		/usr/pkg/cross/i686-w64-mingw32-msvcrt/bin/i686-w64-mingw32-gcc

SRCDIR=		../../src

LDFLAGS=	-L.
LDFLAGS+=	-llua54
LDFLAGS+=	-lm -lwsock32 -lws2_32
LDFLAGS+=	-s

CFLAGS=		-O2 -Wall -std=c99
CFLAGS+=	-fstack-protector-strong
CFLAGS+=	-Wno-error=incompatible-pointer-types
CFLAGS+=	-D_FORTIFY_SOURCE=2
CFLAGS+=	-s

CFLAGS+=	-I./phc-winner-argon2-20190702/include
CFLAGS+=	-I./sqlite-amalgamation-3460100
CFLAGS+=	-I./libtommath-1.3.0
CFLAGS+=	-I./bzip2-1.0.8
CFLAGS+=	-I./include
CFLAGS+=	-I${SRCDIR}/ext/inih
CFLAGS+=	-I${SRCDIR}/ext/libjag/include

# target Windows XP
CFLAGS+=	-D_WIN32_WINNT=0x0601

CFLAGS+=	-D_POSIX_C_SOURCE=199309L
CFLAGS+=	-DWITH_RSA_LIBTOM=1
CFLAGS+=	-DHAVE_SYS_TIME_H=1
CFLAGS+=	-DARGON2_NO_THREADS=1
CFLAGS+=	-DSQLITE_MUTEX_NOOP=1

OBJS=		${SRCDIR}/admin.o
OBJS+=		${SRCDIR}/bank.o
OBJS+=		${SRCDIR}/buffer.o
OBJS+=		${SRCDIR}/config/config.o
OBJS+=		${SRCDIR}/config/text.o
OBJS+=		${SRCDIR}/ext/flea.o
OBJS+=		${SRCDIR}/ext/inih/ini.o
OBJS+=		${SRCDIR}/ext/isaac.o
OBJS+=		${SRCDIR}/ext/libjag/lib/jag_bzip2_decompress.o
OBJS+=		${SRCDIR}/ext/libjag/lib/jag_find_entry.o
OBJS+=		${SRCDIR}/ext/libjag/lib/jag_hash_entry_name.o
OBJS+=		${SRCDIR}/ext/libjag/lib/jag_map_read_jm.o
OBJS+=		${SRCDIR}/ext/libjag/lib/jag_read_entry.o
OBJS+=		${SRCDIR}/ext/libjag/lib/jag_read_header.o
OBJS+=		${SRCDIR}/ext/libjag/lib/jag_unpack_entry.o
OBJS+=		${SRCDIR}/ext/libjag/lib/jag_unpack_file.o
OBJS+=		${SRCDIR}/ext/reallocarr.o
OBJS+=		${SRCDIR}/inventory.o
OBJS+=		${SRCDIR}/loop-select.o
OBJS+=		${SRCDIR}/mob.o
OBJS+=		${SRCDIR}/netio.o
OBJS+=		${SRCDIR}/npc.o
OBJS+=		${SRCDIR}/persistence/database-sqlite.o
OBJS+=		${SRCDIR}/persistence/pwhash-argon2.o
OBJS+=		${SRCDIR}/player.o
OBJS+=		${SRCDIR}/protocol/incoming.o
OBJS+=		${SRCDIR}/protocol/opcodes201.o
OBJS+=		${SRCDIR}/protocol/opcodes203.o
OBJS+=		${SRCDIR}/protocol/outgoing.o
OBJS+=		${SRCDIR}/protocol/rsa-libtom.o
OBJS+=		${SRCDIR}/script.o
OBJS+=		${SRCDIR}/server.o
OBJS+=		${SRCDIR}/settings.o
OBJS+=		${SRCDIR}/shop.o
OBJS+=		${SRCDIR}/stat.o
OBJS+=		${SRCDIR}/trade.o
OBJS+=		${SRCDIR}/utility.o
OBJS+=		${SRCDIR}/zone.o

OBJS+=		./sqlite-amalgamation-3460100/sqlite3.o
OBJS+=		./bzip2-1.0.8/blocksort.o
OBJS+=		./bzip2-1.0.8/bzlib.o
OBJS+=		./bzip2-1.0.8/compress.o
OBJS+=		./bzip2-1.0.8/crctable.o
OBJS+=		./bzip2-1.0.8/decompress.o
OBJS+=		./bzip2-1.0.8/huffman.o
OBJS+=		./bzip2-1.0.8/randtable.o

OBJS+=		./libtommath-1.3.0/mpi.o

OBJS+=		./phc-winner-argon2-20190702/src/argon2.o
OBJS+=		./phc-winner-argon2-20190702/src/blake2/blake2b.o
OBJS+=		./phc-winner-argon2-20190702/src/core.o
OBJS+=		./phc-winner-argon2-20190702/src/encoding.o
OBJS+=		./phc-winner-argon2-20190702/src/ref.o

all: rscsundae.exe

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

rscsundae.exe: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o rscsundae.exe

clean:
	rm -f rscsundae.exe
	rm -f $(OBJS)
