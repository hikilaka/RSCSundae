RSC Sundae on Win32
===================

Currently only cross-compilation from a Unix-like system with mingw-w64 has
been tested.  Use `prepare.sh` to set up the environment.  Set the `CC`
variable in Makefile to the path of your toolchain.  The script automates
some of the downloads.

Download DLL binaries
---------------------

- Lua: https://sourceforge.net/projects/luabinaries/files/5.4.2/Windows%20Libraries/Dynamic/lua-5.4.2_Win32_dllw6_lib.zip/download
