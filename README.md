# Portable C arithmetic right shift

The C programming language does not specify the value of  `-5 >> 1`.¹

Normal implementations choose `-5 >> 1 == -3`, which is `-5/2` rounded towards `-INFINITY`.²

That is a **s**igned **a**rithmetic **r**ight shift ([sar](https://github.com/Rupt/c-arithmetic-right-shift)).

The alternative 'logical' shift would result in a large positive number.

Functions in sar.c do some bit twiddling to provide portable arithmetic right shifts.
```C
sari(-5, 1) == -3; /* true */
```
They compile to small, branchless instructions. 
See for yourself on the [Compiler Explorer](https://godbolt.org/z/hvrY6e).

Standard integer types are supported for pedantic C99.

## Use
```C
#include "stdint.h"
#include "sar.c"

sari(-63, 3); /* -8 */
sarl(-0x200000000l, 1); /* -0x100000000l */
sarfast32(-0xDECAF, 8); /* -0xDED */
```

<details>
<summary><b>Details</b></summary>

Arithmetic right shift functions defined by "sar.c" are of the form
```C
static type sar#(type m, uint_fast8_t n);
```
where `type` is any of:
```C
signed char   /* sarc */
short         /* sars */
int           /* sari */
long int      /* sarl */
long long int /* sarll */

/* included in stdint.h */
int_fast8_t   /* sarfast8 */
int_fast16_t  /* sarfast16 */
int_fast32_t  /* sarfast32 */
int_fast64_t  /* sarfast64 */
int_least8_t  /* sarleast8 */
int_least16_t /* sarleast16 */
int_least32_t /* sarleast32 */
int_least64_t /* sarleast64 */
intmax_t      /* sarmax */

/* optionally included in stdint.h */
int8_t        /* sar8 */
int16_t       /* sar16 */
int32_t       /* sar32 */
int64_t       /* sar64 */
intptr_t      /* sarptr */
```
Static is used to reduce the exposed clutter;
please define wrappers if you want external linkage.

The following macros are also defined.
```C
/* Use external include guards. */
#define SAR_C

/* Macro which will duplicate side effects (unsafe). */
#define sarshift(m, n, type)

/* Used to construct sarshift */
#define sarlogical(type)
#define sardo(type)
#define sarhigh(m, n, type)
```

An external include guard looks like this.
```C
#ifndef SAR_C
#include "sar.c"
#endif
```
Alternatives which force logical shifts, then correct them back,
are defined in "saru.c" with the prefix `saru#`.
</details>

<details>
<summary><b>I am forced to use C++</b></summary>

C++11 is supported.
```C++
#include <cstdint>
#include "sar.c"
```

You can avoid some name mangling problems like so.
```C++
extern "C" {
#include "sar.c"
}
```
</details>

## Test
```bash
make test
```

___
¹ "The result of `E1 >> E2` is `E1` right-shifted `E2` bit positions. ... If `E1` has a signed type and a negative value, the resulting value is implementation-defined." ISO/IEC 9899:TC2 6.5.7, p84-85

² Making this code mostly useless, but hopefully also mostly harmless.
