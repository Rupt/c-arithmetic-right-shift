/* Attempt to find errors in sar.c */
#include <assert.h>
#include <limits.h>
#include <stdint.h>
#include "sar.c"

/*
 * Use unsigned to force logical shifts, and make them arithmetic.
 * redefine sar.c functions prefixed with and L to test this.
 */
#define LSARDEFINE(label, type, utype)                                 \
    type                                                               \
    Lsar##label(type m, type n)                                        \
    {                                                                  \
        const type logical = ((utype)-1 >> 1) > 0;                     \
        utype fill;                                                    \
        fill = -(logical && m < 0);                                    \
        return ((utype)m >> n) | (fill << (CHAR_BIT*sizeof(m) - n));   \
    }

LSARDEFINE(c, signed char, unsigned char)
LSARDEFINE(s, short int, unsigned short int)
LSARDEFINE(i, int, unsigned int)
LSARDEFINE(l, long int, unsigned long int)

#ifdef LLONG_MAX
LSARDEFINE(ll, long long int, unsigned long long int)
#endif

#ifdef INT8_MAX
LSARDEFINE(8, int8_t, uint8_t)
#endif

#ifdef INT16_MAX
LSARDEFINE(16, int16_t, uint16_t)
#endif

#ifdef INT32_MAX
LSARDEFINE(32, int32_t, uint32_t)
#endif

#ifdef INT64_MAX
LSARDEFINE(64, int64_t, uint64_t)
#endif

#ifdef INTPTR_MAX
LSARDEFINE(ptr, intptr_t, uintptr_t)
#endif

#ifdef INT_LEAST8_MIN
LSARDEFINE(max, intmax_t, uintmax_t)
LSARDEFINE(least8, int_least8_t, int_least8_t)
LSARDEFINE(least16, int_least16_t, int_least16_t)
LSARDEFINE(least32, int_least32_t, int_least32_t)
LSARDEFINE(least64, int_least64_t, int_least64_t)
LSARDEFINE(fast8, int_fast8_t, int_fast8_t)
LSARDEFINE(fast16, int_fast16_t, int_fast16_t)
LSARDEFINE(fast32, int_fast32_t, int_fast32_t)
LSARDEFINE(fast64, int_fast64_t, int_fast64_t)
#endif


void
testeq(signed char m, signed char n, signed char eq)
{
    /* functions defined in sar.c */
    assert(sarc(m, n) == eq);
    assert(sars(m, n) == eq);
    assert(sari(m, n) == eq);
    assert(sarl(m, n) == eq);

#ifdef LLONG_MAX
    assert(sarll(m, n) == eq);
#endif

#ifdef INT8_MAX
    assert(sar8(m, n) == eq);
#endif

#ifdef INT16_MAX
    assert(sar16(m, n) == eq);
#endif

#ifdef INT32_MAX
    assert(sar32(m, n) == eq);
#endif

#ifdef INT64_MAX
    assert(sar64(m, n) == eq);
#endif

#ifdef INTPTR_MAX
    assert(sarptr(m, n) == eq);
#endif

#ifdef INT_LEAST8_MIN
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
    assert(Lsarc(m, n) == eq);
    assert(Lsars(m, n) == eq);
    assert(Lsari(m, n) == eq);
    assert(Lsarl(m, n) == eq);

#ifdef LLONG_MAX
    assert(Lsarll(m, n) == eq);
#endif

#ifdef INT8_MAX
    assert(Lsar8(m, n) == eq);
#endif

#ifdef INT16_MAX
    assert(Lsar16(m, n) == eq);
#endif

#ifdef INT32_MAX
    assert(Lsar32(m, n) == eq);
#endif

#ifdef INT64_MAX
    assert(Lsar64(m, n) == eq);
#endif

#ifdef INTPTR_MAX
    assert(Lsarptr(m, n) == eq);
#endif

#ifdef INT_LEAST8_MIN
    assert(Lsarmax(m, n) == eq);
    assert(Lsarleast8(m, n) == eq);
    assert(Lsarleast16(m, n) == eq);
    assert(Lsarleast32(m, n) == eq);
    assert(Lsarleast64(m, n) == eq);
    assert(Lsarfast8(m, n) == eq);
    assert(Lsarfast16(m, n) == eq);
    assert(Lsarfast32(m, n) == eq);
    assert(Lsarfast64(m, n) == eq);
#endif
}


int
main()
{
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
    
    assert(sari(-63, 3) == -8);
    assert(sarl(-0x200000000l, 1) == -0x100000000l);
#ifdef INT_LEAST8_MIN
    assert(sarfast32(-0xDECAF, 8) == -0xDED);
#endif

    return 0;
}
