/* Attempt to find errors in sar.c */
#ifndef __cplusplus
#    include <assert.h>
#    include <stdint.h>
#else
#    include <cassert>
#    include <cstdint>
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

    assert(sarfast8(m, n) == eq);
    assert(sarfast16(m, n) == eq);
    assert(sarfast32(m, n) == eq);
    assert(sarfast64(m, n) == eq);
    assert(sarleast8(m, n) == eq);
    assert(sarleast16(m, n) == eq);
    assert(sarleast32(m, n) == eq);
    assert(sarleast64(m, n) == eq);
    assert(sarmax(m, n) == eq);

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

    /* versions which correction of logical shifts */
    assert(saruc(m, n) == eq);
    assert(sarus(m, n) == eq);
    assert(sarui(m, n) == eq);
    assert(sarul(m, n) == eq);
    assert(sarull(m, n) == eq);

    assert(sarufast8(m, n) == eq);
    assert(sarufast16(m, n) == eq);
    assert(sarufast32(m, n) == eq);
    assert(sarufast64(m, n) == eq);
    assert(saruleast8(m, n) == eq);
    assert(saruleast16(m, n) == eq);
    assert(saruleast32(m, n) == eq);
    assert(saruleast64(m, n) == eq);
    assert(sarumax(m, n) == eq);

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

    for (int i = 0; i < nchecks; ++i)
        testeq(checks[i][0], checks[i][1], checks[i][2]);

    /* readme examples */
    assert(sari(-63, 3) == -8);
    assert(sarl(-0x200000000l, 1) == -0x100000000l);
    assert(sarfast32(-0xDECAF, 8) == -0xDED);
    assert(sar8(15, 2) == 3);

    assert(sarui(-63, 3) == -8);
    assert(sarul(-0x200000000l, 1) == -0x100000000l);
    assert(sarufast32(-0xDECAF, 8) == -0xDED);
    assert(saru8(15, 2) == 3);

    return 0;
}
