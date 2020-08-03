# Portable C arithmetic right shift

The C programming language does not specify the value of  `-5 >> 1`.¹

Normal implementations choose `-5 >> 1 == -3`, which is `-5/2` rounded towards `-INFINITY`.²

That is a **s**igned **a**rithmetic **r**ight shift (**sar**).

The alternative 'logical' shift would result in a large positive number.

Functions in sar.c do some bit twiddling to provide portable arithmetic right shifts.
```c
sari(-5, 1) == -3; /* true */
```
They compile to small, branchless instructions. See for yourself on the [Compiler Explorer](https://godbolt.org/z/Ge35ze).

Standard integer types are supported, with compatibility back to pedantic C89.

## Use
```c
#include "limits.h"
#include "stdint.h" /* optional */
#include "sar.c"

sari(-63, 3); /* -8 */
sarl(-0x200000000l, 1); /* -0x100000000l */
sarfast32(-0xDECAF, 8); /* -0xDED */
```

## Test
```bash
make test
```

___
¹ "The result of `E1 >> E2` is `E1` right-shifted `E2` bit positions. ... If `E1` has a signed type and a negative value, the resulting value is implementation-defined." ISO/IEC 9899:TC2 6.5.7, p84-85

² Making this code mostly useless, but hopefully also mostly harmless.
