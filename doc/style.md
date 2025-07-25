Coding style for RSC Sundae
===========================

C code
------

C code is written in BSD Kernel Normal Form, a variant of "one
true brace style". You can read about KNF here:

http://bxr.su/NetBSD/share/misc/style

Memory allocation is avoided where possible during runtime (it's okay
during startup) for performance and predictable reliable behaviour
while the server is running.  If allocation is necessary, use `calloc()`
or `reallocarr()` to avoid overflow from multiplications in malloc's
arguments.

Functions return `-1` on error and `0` on success, in line with POSIX.

Functions in `buffer.h` are all bounds-checked.  Only ignore their
return value if truncation is known to be impossible or doesn't
matter.

Avoid the use of `sprintf`, `strcpy`, `strcat`, etc.  Use
`snprintf` instead.

Do not use `alloca` or variable-length stack based arrays to avoid
unpredictable stack size increases.

Lua code
--------

* Do not use global variables in content scripts except if they are constant
  (not ever changed).
* Avoid using math.random(), for authentic randomness behaviour
  in content scripts use random() and randomvar() instead.
* under_scores are preferred over camelCase. THVariableName may be
  acceptable for getvar() variables in content originally designed by
  Tytn H.
