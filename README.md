# Portable C arithmetic right shift

The C programming language does not specify the value of  `-5 >> 1`.¹

Normal implementations choose `-5 >> 1 == -3`, which is `-5/2` rounded towards `-INFINITY`.²

That is a **s**igned **a**rithmetic **r**ight shift (**sar**).

The alternative 'logical' shift would result in a large positive number.

Functions in sar.c do some bit twiddling to provide portable arithmetic right shifts.
```C
sari(-5, 1) == -3; /* true */
```
They compile to small, branchless instructions. See for yourself on the [Compiler Explorer](https://godbolt.org/z/jqjEz7).

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

```C
/* standard integer types */
signed char sarc(signed char m, signed char n);
short int sars(short int m, short int n);
int sari(int m, int n);
long int sarl(long int m, long int n);

/* since C99 */
long long int sarll(long long int m, long long int n);

/* if stdint.h provides */
int8_t sar8(int8_t m, int8_t n);
int16_t sar16(int16_t m, int16_t n);
int32_t sar32(int32_t m, int32_t n);
int64_t sar64(int64_t m, int64_t n);
intptr_t sarptr(intptr_t m, intptr_t n);

/* if stdint.h */
intmax_t sarmax(intmax_t m, intmax_t n);
int_least8_t sarleast8(int_least8_t m, int_least8_t n);
int_least16_t sarleast16(int_least16_t m, int_least16_t n);
int_least32_t sarleast32(int_least32_t m, int_least32_t n);
int_least64_t sarleast64(int_least64_t m, int_least64_t n);
int_fast8_t sarfast8(int_fast8_t m, int_fast8_t n);
int_fast16_t sarfast16(int_fast16_t m, int_fast16_t n);
int_fast32_t sarfast32(int_fast32_t m, int_fast32_t n);
int_fast64_t sarfast64(int_fast64_t m, int_fast64_t n);

/* macro used to define these functions */
#define SARDEFINE(label, type, utype)
```
</details>

<details>
<summary>Help, I am forced to use C++</summary>

```C++
#include <climits>
#include <cstdint> /* optional, since C++11 */
#include "sar.c"
```
</details>

## Test
```bash
make test
```

___
¹ "The result of `E1 >> E2` is `E1` right-shifted `E2` bit positions. ... If `E1` has a signed type and a negative value, the resulting value is implementation-defined." ISO/IEC 9899:TC2 6.5.7, p84-85

² Making this code mostly useless, but hopefully also mostly harmless.
