# now — microsecond timestamps

`now` represents time as one unsigned 64-bit count of **microseconds
since 1970-01-01 00:00 UTC** (`u64`). It converts that value to and from
`struct timeval`, `struct tm` (extended with microseconds) and text.
A single integer timestamp is easy to store in shared memory or a
record, easy to compare, and keeps sub-second precision that `time_t`
lacks.

## API (`now.h`)

| Function | Purpose |
|---|---|
| `u64 Micro_Now(void)` | Current time from `gettimeofday`. |
| `u64 Micro_From_Timeval(tv_t)` / `tv_t Micro_To_Timeval(u64)` | Convert to and from `struct timeval`. |
| `u64 Micro_From_tm(tm_t *)` | Local `tm` plus `tm_usec` to microseconds, via `mktime`. Returns 0 for years before 1970. |
| `void Micro_To_GMT(u64, tm_t *)` / `Micro_To_Local(u64, tm_t *)` | Break a timestamp into UTC or local fields. |
| `int Micro_To_String_GMT(buf, size, fmt, u64)` / `Micro_To_String_Local(...)` | Format with `strftime` and append `.uuuuuu`. The default format is `%y.%m.%d.%H.%M.%S`. |
| `u64 Micro_From_String(char *buf, tm_t *out)` | Parse local time in the order year, month, day, hour, minute, second, fraction. Any non-digit separators are accepted. Missing trailing fields default to the start of the period, and the fraction is padded to 6 digits. |

Types: `tm_t` is `{ struct tm tm; int tm_usec; }`, `tv_t` is
`struct timeval`, and `TM` is `struct tm`.

## Directory and build layout

```
now/
  now.h                   public header (installed to ~/cmn)
  micro_now.c micro_from_tv.c micro_to_tv.c micro_from_tm.c
  micro_to_gmt.c micro_to_loc.c micro_to_str_gmt.c micro_to_str_loc.c
  micro_from_str.c        one function per file
  makefile                LIBRARIES =   (empty)
  UNIT.deps               base 1, require sys
```

The unit has no test program. Build inside a `base` project:
`repo add now`, then `make` in `now/`.

## Example (validated in a temporary copy, TZ=America/New_York)

```c
#include <now.h>
char b[64]; tm_t t;
u64 m = Micro_From_String("2026-11-05 21:59:30.25", &t);
Micro_To_String_GMT(b, sizeof b, NULL, m);                    /* default fmt */
Micro_To_String_Local(b, sizeof b, "%Y-%m-%d %H:%M:%S", m);
Micro_From_Timeval(Micro_To_Timeval(m)) == m;                 /* round trip */
```

Output:

```
1793933970250000 26.11.06.02.59.30.250000
2026-11-05 21:59:30.250000
1793933970250000
```

## Dependencies

- **Link-time:** none. `libnow.a` needs only libc
  (`gettimeofday`, `mktime`, `gmtime_r`, `localtime_r`, `strftime`,
  `snprintf`, `memset`, `isdigit`). A test program linked with only
  `-lnow` builds and runs.
- **Compile-time:** `now.h` includes `<common.h>`, which is installed by
  `sys`, for the `u64`/`s32` types. That is why `UNIT.deps` lists
  `require sys`: the header must be present, but `libsys` is never
  linked.
- **Indirect:** none.
- **Makefile `-l` list:** empty, which matches the code.

## Using this unit from C++

This unit can be used from **C and C++**. Keep the unit's `.c` implementation
files compiled as C with `gcc`/`CC`; compile your C++ client with `g++`/`CXX`
and use `g++` for the final mixed-language link. There is no need to rebuild
the C library as C++.

Base's shared rules recognize C++ product sources named `.cc` and compile
them with `CXX` and `CXXFLAGS` (for example `make CXX=g++`). `CPP` names
the preprocessor, not the C++ compiler. The commands below assume the
headers and libraries have already been installed into `$HOME/cmn` and
`$HOME/lib`. GNU C++17 on Linux x86-64 is the example target; GNU extensions
in the shared types/headers are intentional.

`now.h` and its nested `common.h` provide their own `extern "C"` guards.
`tm_t` is an anonymous-struct typedef, so use `tm_t fields{}` in C++, not
`struct tm_t`. Its member is a `struct tm` named `tm`; no compatibility
define or user linkage wrapper is needed. For text parsing/formatting,
use mutable arrays for parameters declared `char *`, for example
`char input[] = "2026-11-05 21:59:30.25";` before `Micro_From_String`.

Save as `use_now.cc`:

```cpp
#include <now.h>
int main() {
    u64 stamp = Micro_Now();
    tm_t fields{};
    Micro_To_GMT(stamp, &fields);
    return Micro_From_Timeval(Micro_To_Timeval(stamp)) == stamp ? 0 : 1;
}
```

```sh
g++ -std=gnu++17 -I"$HOME/cmn" use_now.cc -L"$HOME/lib" -lnow -o use_now
./use_now
```

The C++ example above was compiled, linked and run on Linux x86-64 using
Clang 22.1.8 via `zig c++ -std=gnu++17 -nostdlib++`, with GCC 14.2-built C
objects where needed. It uses no C++ standard-library runtime. The `g++`
command is the GNU-toolchain form; that driver was not available for this
smoke check. This is not an exhaustive API or concurrency test.

## License

The original files are offered under `Apache-2.0 OR GPL-2.0-or-later`;
you choose either license. See `LICENSE` and `LICENSES/`. Copyright
notices are retained; see the SPDX identifier in each source file.

## Version

Version tag: `v0.2.0`.
