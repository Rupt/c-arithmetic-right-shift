# Portable C arithmetic right shift

The C programming language does not specify the value of  `-5 >> 1`.[1]

Normal implementations sensibly choose `-5 >> 1 == -3`, which is `-5/2` rounded towards `-INFINITY`.
That is a **s**igned **a**rithmetic **r**ight shift (sar).[2]

Functions in sar.c provide arithmetic right shift behavior with more certainty.
```c
sari(-5, 1) == -3; /* true */
```
Compilation produces small and branchless instructions (check on the [Compiler Explorer](https://godbolt.org/z/6PzT3h)).
Compatible back to C89.

### Use
```c
#include "limits.h"
#include "stdint.h" /* optional */
#include "sar.c"

sari(-63, 3); /* -8 */
sarl(-0x200000000l, 1); /* -0x100000000l */
```
### Test
```bash
make test
```
___
[1]: "The result of `E1 >> E2` is `E1` right-shifted `E2` bit positions. ... If `E1` has a signed type and a negative value, the resulting value is implementation-defined." ISO/IEC 9899:TC2 6.5.7, p84-85

[2]: Making this code normally useless. Perhaps it can claim to be mostly harmless.
