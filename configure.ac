AC_PREREQ([2.65])
AC_INIT([rscsundae], [0.0.1], [stormy@mailfence.com])
AM_INIT_AUTOMAKE([-Wall foreign])
AC_PROG_CC
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
 Makefile
 src/Makefile
 doc/Makefile
])

AM_MAINTAINER_MODE([disable])

CFLAGS="$CFLAGS -Wall"
CFLAGS="$CFLAGS -Wextra"
CFLAGS="$CFLAGS -std=gnu99"
AC_CHECK_FUNCS([arc4random_buf])
AC_CHECK_FUNCS([clock_gettime])
AC_CHECK_FUNCS([reallocarr])
AC_CHECK_FUNCS([daemon])
AC_CHECK_FUNCS([timerfd_create])
AC_CHECK_HEADERS([sys/time.h])
AC_CHECK_HEADERS([sys/timerfd.h])
AC_CHECK_HEADERS([bzlib.h])

AC_SEARCH_LIBS([BZ2_bzDecompressInit], [bz2], [
	], [
		AC_MSG_ERROR([unable to find the bzip2 library])
	]
)

PKG_CHECK_MODULES([LUA], [lua-5.4], [
	], [
		PKG_CHECK_MODULES([LUA], [lua5.4])
	])

PKG_CHECK_MODULES([SQLITE3], [sqlite3])

AM_CONDITIONAL(HAVE_SYSTEM_INIH, true)
PKG_CHECK_MODULES([INIH], [inih], [
	], [
		AM_CONDITIONAL(HAVE_SYSTEM_INIH, false)
	])

AM_CONDITIONAL(HAVE_LIBCRYPTO, true)
PKG_CHECK_MODULES([LIBCRYPTO], [libcrypto], [
	], [
		AM_CONDITIONAL(HAVE_LIBCRYPTO, false)
	])

PKG_CHECK_MODULES([LIBARGON2], [libargon2])

AM_SILENT_RULES([yes])

AC_ARG_WITH([libtom],
	[AS_HELP_STRING([--with-libtom],
		[use libtommath for RSA decryption (instead of libcrypto) @<:@default=no@:>@])],
	[],
	[with_libtom=no])

AC_ARG_WITH([kqueue],
	[AS_HELP_STRING([--with-kqueue],
		[use kqueue for the event loop (best on BSD systems) @<:@default=check@:>@])],
	[],
	[with_kqueue=check])

AC_ARG_WITH([select],
	[AS_HELP_STRING([--with-select],
		[use select for the event loop (not recommended) @<:@default=no@:>@])],
	[],
	[with_select=no])

AM_CONDITIONAL(HAVE_LIBTOM, false)
AS_IF([test "x$with_libtom" != xno],
	[PKG_CHECK_MODULES([LIBTOMMATH], [libtommath],
		[
			AM_CONDITIONAL(HAVE_LIBTOM, true)
		]
	)])

# prefer kqueue
AM_CONDITIONAL(HAVE_KQUEUE, false)
AS_IF([test "x$with_kqueue" != xno],
	[AC_CHECK_FUNCS([kqueue],
		[
			AM_CONDITIONAL(HAVE_KQUEUE, true)
		],
		[],
	)])

AM_CONDITIONAL(HAVE_POLL, false)
AS_IF([test "x$with_select" = xno],
	[
		AC_CHECK_FUNCS([poll], [AM_CONDITIONAL(HAVE_POLL, true)], [])
	])

# gethostbyname: Solaris libnsl
AC_SEARCH_LIBS([gethostbyname], [bind nsl network], [], [
	AC_MSG_ERROR([unable to find the gethostbyname() function])
])

# bind: SVR4 libsocket
AC_SEARCH_LIBS([bind], [socket network], [], [
	AC_MSG_ERROR([unable to find the bind() function])
])

AC_DEFUN([GCC_W_NO_FORMAT_TRUNC],[
	result=yes
	AC_MSG_CHECKING([whether ${CC} accepts -Wno-format-truncation])
	old_cflags="$CFLAGS"
	CFLAGS="$CFLAGS -Werror -Wno-format-truncation"
	AC_LINK_IFELSE([AC_LANG_PROGRAM([],[])],[],[result=no])
	echo $result
	if test "X$result" = "Xyes"; then
		CFLAGS="$old_cflags -Wno-format-truncation"
	else
		CFLAGS="$old_cflags"
	fi
])

GCC_W_NO_FORMAT_TRUNC

AC_OUTPUT
