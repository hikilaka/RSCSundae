RSC Sundae 🍨
==========

* Official repository: https://git.sr.ht/~stormy/rscsundae
* Official website: https://rscsundae.org

RSC Sundae is a simple, single-threaded RS Classic server emulator
written in C99.  It is based on clean-room reverse engineering and
contains no copyrighted source code.  For content scripting, it
features an implementation of the original RuneScript API in Lua
based on public documents.

It was inspired by the RSC-C client's lack of a native server.
Since RSC-C runs on old and low-power mobile devices, RSC Sundae
targets similar devices.

RSC Sundae accurately replicates all RS Classic content from the final
F2P-only version of the game (10th December 2001) - lots of preserved
data exists for this revision.  This is accomplished using the original
game's unmodified free data files.  By using the same API and data
sources as the original game, the hope is that it is more difficult to
implement content inaccurately.

For clients, RSC Sundae supports:

* 110 protocol (original Java mudclient110 from December 2001)
* 135 protocol (used by Runebot, RuneScape's first ever bot)
* 204 protocol (the final version of RSC before "Retro Revival" in 2009,
used by RSC-C, and STS)

Most other late 2001 to March 2003 clients should work as well,
including all 2002 versions.

RSC Sundae has a few special features as well:

* Live script reloading, allowing game updates without a restart
* Extremely low system requirements (under 32 MB RAM usage)
* 1:1 replication of NPC behaviour
* Per-player packet logging

RSC Sundae will never support:

* Multiple threads
* Protocol versions beyond 204
* Protocol versions with the "spook cipher"
* Custom private server protocols or data formats
* Integration with proprietary services like Discord

Building
--------

RSC Sundae is developed on NetBSD. I occasionally test it on
Mac OS X 10.4 and Alpine Linux. If I break something on another
UNIX-like platform, please send a patch.

For Windows, instead refer to `platform/win32/README.md`.

Dependencies:

* BZip2 (for decompressing Jagex Archives to load the original game data)
* Lua 5.4 (for running content scripts)
* inih (for parsing the configuration file)
* libcrypto from OpenSSL (for RSA decryption, and random number generation on some systems)
* SQLite3 (for player save file persistence)
* Argon2 (for secure password storage)

On Debian Linux and derivatives, install the following:

	build-essential pkgconf libbz2-dev liblua5.4-dev libinih-dev libssl-dev libsqlite3-dev libargon2-dev autoconf automake

On Alpine Linux, install the following:

	build-base pkgconf bzip2-dev lua5.4-dev inih-dev openssl-dev sqlite-dev argon2-dev autoconf automake

To regenerate the build files, run `autoreconf -fi`.

Run `./configure && make -j2` to build the server.
You only need to run `./configure` once.

Contributing
------------

Read `doc/style.md` first.

Use `git format-patch`. You can email `stormy@mailfence.com`.

Fuzzing & profiling
-------------------

Sundae is wired up for performance profiling with gperftools and fuzzing
with AFL.

For profiling, configure with:

	CFLAGS="-DPROFILE" LDFLAGS="-lprofiler" ./configure

For fuzzing, configure with:

	CC=afl-gcc \
	CFLAGS="-DFUZZ -D_FORTIFY_SOURCE=2 -fstack-protector-all -fsanitize=undefined" \
	LDFLAGS="-fsanitize=undefined" ./configure

Credits
-------

* Stormy wrote the bulk of the engine and most of the content.
* Mister Hat (frogdoubler) contributed player persistence support via SQLite,
  the Dragon Slayer quest, Vampire Slayer, Prince Ali rescue, and
  Ernest the Chicken.
* Zachary Penn (Hikilaka) contributed many enhancements to the scripting API,
  teleportation spells, mixing dyes and capes, and player variables support.
* Pazaz served as an influence with their 2004scape project, listened to
  a lot of my theorizing, and helped answer obscure RS questions.
* Protosstribe got me interested in reverse engineering old clients.
* Members of the RSC community (especially RSC 2001, Logg, 1e Luis)
  recorded many packet captures, without which a lot of information
  used to write this code would be lost.

Resources
---------

* https://github.com/2003scape/rsc-c
* https://web.archive.org/web/20011122124112/http://www.jagex.com/manual/index.html
* https://web.archive.org/web/20080907105147/http://gowerarchive.googlepages.com/documents#Runescript
* https://classic.runescape.wiki/w/User:Stormykins/135_Protocol
