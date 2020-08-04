# Portable C arithmetic right shift

The C programming language does not specify the value of  `-5 >> 1`.¹

Normal implementations choose `-5 >> 1 == -3`, which is `-5/2` rounded towards `-INFINITY`.²

That is a **s**igned **a**rithmetic **r**ight shift ([sar](https://github.com/Rupt/c-arithmetic-right-shift)).

The alternative 'logical' shift would result in a large positive number.

Functions in sar.c do some bit twiddling to provide portable arithmetic right shifts.
```C
sari(-5, 1) == -3; /* true */
```
They compile to small, branchless instructions. See for yourself on the [Compiler Explorer](https://godbolt.org/z/978xs5).

Standard integer types are supported, with compatibility back to pedantic C89.

## Use
```C
#include "limits.h"
#include "stdint.h" /* optional */
#include "sar.c"

sari(-63, 3); /* -8 */
sarl(-0x200000000l, 1); /* -0x100000000l */
sarfast32(-0xDECAF, 8); /* -0xDED */
```

<details>
<summary>Details</summary>

Functions defined by sar.c are listed here.
```C
/* standard integer types */
static signed char sarc(signed char m, signed char n);
static short int sars(short int m, short int n);
static int sari(int m, int n);
static long int sarl(long int m, long int n);

/* since C99 (or C++11) */
static long long int sarll(long long int m, long long int n);

/* types optionally included by stdint.h */
static int8_t sar8(int8_t m, int8_t n);
static int16_t sar16(int16_t m, int16_t n);
static int32_t sar32(int32_t m, int32_t n);
static int64_t sar64(int64_t m, int64_t n);
static intptr_t sarptr(intptr_t m, intptr_t n);

/* types necessarily included by stdint.h */
static intmax_t sarmax(intmax_t m, intmax_t n);
static int_least8_t sarleast8(int_least8_t m, int_least8_t n);
static int_least16_t sarleast16(int_least16_t m, int_least16_t n);
static int_least32_t sarleast32(int_least32_t m, int_least32_t n);
static int_least64_t sarleast64(int_least64_t m, int_least64_t n);
static int_fast8_t sarfast8(int_fast8_t m, int_fast8_t n);
static int_fast16_t sarfast16(int_fast16_t m, int_fast16_t n);
static int_fast32_t sarfast32(int_fast32_t m, int_fast32_t n);
static int_fast64_t sarfast64(int_fast64_t m, int_fast64_t n);
```
Static is used to reduce the exposed clutter;
please define wrappers if you want external linkage.

The following macros are also defined.
```C
/* for use with external include guards */
#define SAR_C

/* if sarll is defined */
#define SARLL

/* if corresponding optional stdint.h functions are defined */
#define SAR8
#define SAR16
#define SAR32
#define SAR64
#define SARPTR

/* if other stdint.h functions are defined */
#define SARINT

/* to define the above functions, or your addition */
#define SARDEFINE(label, type, utype)
```

An external include guard looks like this.
```C
#ifndef SAR_C
#include "sar.c"
#endif
```
</details>

<details>
<summary>I am forced to use C++</summary>

C++ is supported.
```C++
#include <climits>
#include <cstdint> /* optional, since C++11 */
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
