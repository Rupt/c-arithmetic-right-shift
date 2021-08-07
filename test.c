/* Attempt to find errors in sar.c */
#ifndef __cplusplus
#   include <assert.h>
#   ifdef NSARSTDINT
#       include <stdint.h>
#   endif
#else
#   include <cassert>
#   ifdef NSARSTDINT
#       include <cstdint>
#   endif
#endif
#include "sar.c"
#include "saru.c"


void
testeq(signed char m, signed char n, signed char eq)
{
    /* included in sar.c */
    assert(sarc(m, n) == eq);
    assert(sars(m, n) == eq);
    assert(sari(m, n) == eq);
    assert(sarl(m, n) == eq);
    assert(sarll(m, n) == eq);

#ifdef UINT_FAST8_MAX
    assert(sarfast8(m, n) == eq);
    assert(sarfast16(m, n) == eq);
    assert(sarfast32(m, n) == eq);
    assert(sarfast64(m, n) == eq);
    assert(sarleast8(m, n) == eq);
    assert(sarleast16(m, n) == eq);
    assert(sarleast32(m, n) == eq);
    assert(sarleast64(m, n) == eq);
    assert(sarmax(m, n) == eq);
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

    /* versions which correct logical shifts */
    /* included in saru.c */
    assert(saruc(m, n) == eq);
    assert(sarus(m, n) == eq);
    assert(sarui(m, n) == eq);
    assert(sarul(m, n) == eq);
    assert(sarull(m, n) == eq);

#ifdef UINT_FAST8_MAX
    assert(sarufast8(m, n) == eq);
    assert(sarufast16(m, n) == eq);
    assert(sarufast32(m, n) == eq);
    assert(sarufast64(m, n) == eq);
    assert(saruleast8(m, n) == eq);
    assert(saruleast16(m, n) == eq);
    assert(saruleast32(m, n) == eq);
    assert(saruleast64(m, n) == eq);
    assert(sarumax(m, n) == eq);
#endif

#ifdef INT8_MAX
    assert(saru8(m, n) == eq);
#endif

#ifdef INT16_MAX
    assert(saru16(m, n) == eq);
#endif

#ifdef INT32_MAX
    assert(saru32(m, n) == eq);
#endif

#ifdef INT64_MAX
    assert(saru64(m, n) == eq);
#endif

#ifdef INTPTR_MAX
    assert(saruptr(m, n) == eq);
#endif
}

int
main()
{
    /* some examples small enough to fit 8-bit signed char */
    signed char checks[][3] = {
        {0, 1, 0},
        {0, 7, 0},
        /* negative */
        {-1, 0, -1},
        {-1, 1, -1},
        {-1, 7, -1},
        {-5, 0, -5},
        {-5, 2, -2},
        {-5, 1, -3},
        {-128, 1, -64},
        /* positive */
        {1, 0, 1},
        {1, 1, 0},
        {4, 1, 2},
        {5, 0, 5},
        {5, 1, 2},
        {127, 0, 127},
        {127, 1, 63},
        {127, 6, 1},
        {127, 7, 0},
    };
    int nchecks = sizeof(checks) / sizeof(*checks);

    for (int i = 0; i < nchecks; ++i)
        testeq(checks[i][0], checks[i][1], checks[i][2]);

    /* readme examples */
    assert(sari(-63, 3) == -8);
    assert(sarl(-0x200000000L, 1) == -0x100000000L);
#ifdef UINT_FAST8_MAX
     assert(sarfast32(-0xDECAF, 8) == -0xDED);
#endif
#ifdef INT8_MAX
     assert(sar8(15, 2) == 3);
#endif

    assert(sarui(-63, 3) == -8);
    assert(sarul(-0x200000000L, 1) == -0x100000000L);
#ifdef UINT_FAST8_MAX
     assert(sarufast32(-0xDECAF, 8) == -0xDED);
#endif
#ifdef INT8_MAX
     assert(saru8(15, 2) == 3);
#endif
}
