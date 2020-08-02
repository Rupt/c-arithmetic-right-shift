/* Attempt to find errors in sar.c */
#include <limits.h>
#include <stdint.h>
#include <assert.h>
#include "sar.c"

/* Use unsigned to force logical shifts; make them arithmetic. */
#define SARDEFINELOGICAL(label, type, utype)                           \
    type                                                               \
    sarlogical##label(type m, type n)                                  \
    {                                                                  \
        const type logical = ((utype)-1 >> 1) > 0;                     \
        utype fill;                                                    \
        fill = -(logical && m < 0);                                    \
        return ((utype)m >> n) | (fill << (CHAR_BIT*sizeof(m) - n));   \
    }


void
testneg()
{
    assert(sarc(-5, 1) == -3);
}


int
main()
{
    testneg();
    return 0;
}
