/* Attempt to find errors in sar.c */
#ifndef __cplusplus
#    include <assert.h>
#    include <limits.h>
#    include <stdint.h>
#else
#    include <cassert>
#    include <climits>
#    if __cplusplus >= 201103L
#        include <cstdint>
#    endif
#endif

#include "sar.c"

/*
 * Use unsigned to force logical shifts, then fix-up to arithmetic.
 * redefine sar.c functions prefixed with and L to test this.
 */
#define SARLDEFINE(label, type, utype)                                 \
    type                                                               \
    sarL##label(type m, type n)                                        \
    {                                                                  \
        const type logical = ((utype)-1 >> 1) > 0;                     \
        utype fill;                                                    \
        fill = -(logical & (m < 0));                                   \
        return ((utype)m >> n) | (fill << (CHAR_BIT*sizeof(m) - n));   \
    }

SARLDEFINE(c, signed char, unsigned char)
SARLDEFINE(s, short int, unsigned short int)
SARLDEFINE(i, int, unsigned int)
SARLDEFINE(l, long int, unsigned long int)

#ifdef SARLL
SARLDEFINE(ll, long long int, unsigned long long int)
#endif

#ifdef SAR8
SARLDEFINE(8, int8_t, uint8_t)
#endif

#ifdef SAR16
SARLDEFINE(16, int16_t, uint16_t)
#endif

#ifdef SAR32
SARLDEFINE(32, int32_t, uint32_t)
#endif

#ifdef SAR64
SARLDEFINE(64, int64_t, uint64_t)
#endif

#ifdef SARPTR
SARLDEFINE(ptr, intptr_t, uintptr_t)
#endif

#ifdef SARINT
SARLDEFINE(max, intmax_t, uintmax_t)
SARLDEFINE(least8, int_least8_t, int_least8_t)
SARLDEFINE(least16, int_least16_t, int_least16_t)
SARLDEFINE(least32, int_least32_t, int_least32_t)
SARLDEFINE(least64, int_least64_t, int_least64_t)
SARLDEFINE(fast8, int_fast8_t, int_fast8_t)
SARLDEFINE(fast16, int_fast16_t, int_fast16_t)
SARLDEFINE(fast32, int_fast32_t, int_fast32_t)
SARLDEFINE(fast64, int_fast64_t, int_fast64_t)
#endif


void
testeq(signed char m, signed char n, signed char eq)
{
    /* functions defined in sar.c */
    assert(sarc(m, n) == eq);
    assert(sars(m, n) == eq);
    assert(sari(m, n) == eq);
    assert(sarl(m, n) == eq);

#ifdef SARLL
    assert(sarll(m, n) == eq);
#endif

#ifdef SAR8
    assert(sar8(m, n) == eq);
#endif

#ifdef SAR16
    assert(sar16(m, n) == eq);
#endif

#ifdef SAR32
    assert(sar32(m, n) == eq);
#endif

#ifdef SAR64
    assert(sar64(m, n) == eq);
#endif

#ifdef SARPTR
    assert(sarptr(m, n) == eq);
#endif

#ifdef SARINT
    assert(sarmax(m, n) == eq);
    assert(sarleast8(m, n) == eq);
    assert(sarleast16(m, n) == eq);
    assert(sarleast32(m, n) == eq);
    assert(sarleast64(m, n) == eq);
    assert(sarfast8(m, n) == eq);
    assert(sarfast16(m, n) == eq);
    assert(sarfast32(m, n) == eq);
    assert(sarfast64(m, n) == eq);
#endif

    /* local versions which force logical shifts */
    assert(sarLc(m, n) == eq);
    assert(sarLs(m, n) == eq);
    assert(sarLi(m, n) == eq);
    assert(sarLl(m, n) == eq);

#ifdef SARLL
    assert(sarLll(m, n) == eq);
#endif

#ifdef SAR8
    assert(sarL8(m, n) == eq);
#endif

#ifdef SAR16
    assert(sarL16(m, n) == eq);
#endif

#ifdef SAR32
    assert(sarL32(m, n) == eq);
#endif

#ifdef SAR64
    assert(sarL64(m, n) == eq);
#endif

#ifdef SARPTR
    assert(sarLptr(m, n) == eq);
#endif

#ifdef SARINT
    assert(sarLmax(m, n) == eq);
    assert(sarLleast8(m, n) == eq);
    assert(sarLleast16(m, n) == eq);
    assert(sarLleast32(m, n) == eq);
    assert(sarLleast64(m, n) == eq);
    assert(sarLfast8(m, n) == eq);
    assert(sarLfast16(m, n) == eq);
    assert(sarLfast32(m, n) == eq);
    assert(sarLfast64(m, n) == eq);
#endif
}


int
main()
{
    /* some examples small enough to fit 8-bit signed char */
    signed char checks[][3] = {
        /* negative */
        {-1, 1, -1},
        {-5, 2, -2},
        {-5, 1, -3},
        {-128, 1, -64},
        /* positive */
        {1, 1, 0},
        {4, 1, 2},
        {5, 1, 2},
        {127, 1, 63},
    };
    int nchecks = sizeof(checks)/sizeof(checks[0]);
    int i;

    for (i = 0; i < nchecks; ++i)
        testeq(checks[i][0], checks[i][1], checks[i][2]);

    /* readme examples */
    assert(sari(-63, 3) == -8);
    assert(sarl(-0x200000000l, 1) == -0x100000000l);
#ifdef SARINT
    assert(sarfast32(-0xDECAF, 8) == -0xDED);
#endif

    assert(sarLi(-63, 3) == -8);
    assert(sarLl(-0x200000000l, 1) == -0x100000000l);
#ifdef SARINT
    assert(sarLfast32(-0xDECAF, 8) == -0xDED);
#endif

    return 0;
}
