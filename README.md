# Portable C arithmetic right shift

> Right shifting a signed quantity will fill with bit signs ("arithmetic shift")
> on some machines and with 0-bits ("logical shift") on others.

&mdash; *The C Programming Language* K&R

Signed right shifts in C have implementation-defined behaviour¹.

Common implementations choose to fill with sign bits
(gcc¹, clang², msvc³).

That is a **s**igned **a**rithmetic **r**ight shift
([sar](https://github.com/Rupt/c-arithmetic-right-shift)).

The logical shift would result in a large positive number.

Functions in sar.c do some bit twiddling to provide portable arithmetic right shifts.
```C
sari(-5, 1) == -3; /* true */
```
They compile to small, branchless instructions; see for yourself on the [Compiler Explorer](https://godbolt.org/z/Pc6zcc).

Standard integer types are supported for pedantic C99 and C++11.

## Use
```C
#include "stdint.h"
#include "sar.c"

sari(-63, 3); /* -8 */
sarl(-0x200000000L, 1); /* -0x100000000L */
sarfast32(-0xDECAF, 8); /* -0xDED */
sar8(15, 2); /* 3 */
```

<details>
<summary><b>Details</b></summary>

Arithmetic right shift functions defined by "sar.c" are of the form
```C
static type sar##(type m, uint_fast8_t n);
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

/* Macro to define the sar## function bodies. Not standalone. */
#define SARBODY(type, utype)
```
An external include guard looks like this.
```C
#ifndef SAR_C
#include "sar.c"
#endif
```

Alternatives which force logical shifts, then correct them back,
are defined in "saru.c" with the prefixes `saru##` and `SARU`.
</details>

<details>
<summary><b>C++ is supported</b></summary>
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
make
```

___
¹ *"The result of `E1 >> E2` is `E1` right-shifted `E2` bit positions. ...
If `E1` has a signed type and a negative value, the resulting value is
implementation-defined."*, ISO C N2176 6.5.7, p84-85

² *"Signed ‘>>’ acts on negative numbers by sign extension."*,
[GCC C Implementation-Defined Behavior 4.5 Integers](https://gcc.gnu.org/onlinedocs/gcc/Integers-implementation.html#Integers-implementation)

³ *"GCC is currently the defacto-standard open source
compiler today"*,
[Clang - Features and Goals](https://clang.llvm.org/features.html#gcccompat).

⁴ *"the Microsoft C++ compiler uses the sign bit to fill vacated bit positions"*
[Left Shift and Right Shift Operators (>> and <<)](https://docs.microsoft.com/en-us/cpp/cpp/left-shift-and-right-shift-operators-input-and-output?view=msvc-160#right-shifts)
