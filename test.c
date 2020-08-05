/* Attempt to find errors in sar.c */
#ifndef __cplusplus
#    include <assert.h>
#    include <stdint.h>
#else
#    include <cassert>
#    include <cstdint>
#endif
#include "sar.c"

/* macro implementation TODO doc */
#define sarudo(m, u) (0*(u) - (m < 0))
#define saruhigh(m, n, u) (sarudo((m), (u)) ^ (sarudo((m), (u)) >> (n)))
#define sarushift(m, n, u) (((m) >> (n)) | saruhigh(m, n, u))

static signed char 
saruc(signed char m, uint_fast8_t n)
{
    return sarushift(m, n, (unsigned char)m);
}

static short int
sarus(short int m, uint_fast8_t n)
{
    return sarushift(m, n, (unsigned short int)m);
}

static int
sarui(int m, uint_fast8_t n)
{
    return sarushift(m, n, (unsigned int)m);
}

static long int
sarul(long int m, uint_fast8_t n)
{
    return sarushift(m, n, (unsigned long int)m);
}

static long long int
sarull(long long int m, uint_fast8_t n)
{
    return sarushift(m, n, (unsigned long long int)m);
}

/* integers provided by stdint.h */
static intmax_t
sarumax(intmax_t m, uint_fast8_t n)
{
    return sarushift(m, n, (uintmax_t)m);
}

static int_least8_t
saruleast8(int_least8_t m, uint_fast8_t n)
{
    return sarushift(m, n, (uint_least8_t)m);
}

static int_least16_t
saruleast16(int_least16_t m, uint_fast8_t n)
{
    return sarushift(m, n, (uint_least16_t)m);
}

static int_least32_t
saruleast32(int_least32_t m, uint_fast8_t n)
{
    return sarushift(m, n, (uint_least32_t)m);
}

static int_least64_t
saruleast64(int_least64_t m, uint_fast8_t n)
{
    return sarushift(m, n, (uint_least64_t)m);
}

static int_fast8_t
sarufast8(int_fast8_t m, uint_fast8_t n)
{
    return sarushift(m, n, (uint_fast8_t)m);
}

static int_fast16_t
sarufast16(int_fast16_t m, uint_fast8_t n)
{
    return sarushift(m, n, (uint_fast16_t)m);
}

static int_fast32_t
sarufast32(int_fast32_t m, uint_fast8_t n)
{
    return sarushift(m, n, (uint_fast32_t)m);
}

static int_fast64_t
sarufast64(int_fast64_t m, uint_fast8_t n)
{
    return sarushift(m, n, (uint_fast64_t)m);
}

/* exact-width integers optionally provided by stdint.h */
#ifdef INT8_MAX
static int8_t
saru8(int8_t m, uint_fast8_t n)
{
    return sarushift(m, n, (uint8_t)m);
}
#endif

#ifdef INT16_MAX
static int16_t
saru16(int16_t m, uint_fast8_t n)
{
    return sarushift(m, n, (uint8_t)m);
}
#endif

#ifdef INT32_MAX
static int32_t
saru32(int32_t m, uint_fast8_t n)
{
    return sarushift(m, n, (uint8_t)m);
}
#endif

#ifdef INT64_MAX
static int64_t
saru64(int64_t m, uint_fast8_t n)
{
    return sarushift(m, n, (uint8_t)m);
}
#endif

#ifdef INTPTR_MAX
static intptr_t
saruptr(intptr_t m, uint_fast8_t n)
{
    return sarushift(m, n, (uint8_t)m);
}
#endif


void
testeq(signed char m, signed char n, signed char eq)
{
    /* functions defined in sar.c */
    assert(sarc(m, n) == eq);
    assert(sars(m, n) == eq);
    assert(sari(m, n) == eq);
    assert(sarl(m, n) == eq);
    assert(sarll(m, n) == eq);

    assert(sarmax(m, n) == eq);
    assert(sarleast8(m, n) == eq);
    assert(sarleast16(m, n) == eq);
    assert(sarleast32(m, n) == eq);
    assert(sarleast64(m, n) == eq);
    assert(sarfast8(m, n) == eq);
    assert(sarfast16(m, n) == eq);
    assert(sarfast32(m, n) == eq);
    assert(sarfast64(m, n) == eq);

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

    /* local versions which force logical shifts */
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
    int i;

    for (i = 0; i < nchecks; ++i)
        testeq(checks[i][0], checks[i][1], checks[i][2]);

    /* readme examples */
    assert(sari(-63, 3) == -8);
    assert(sarl(-0x200000000l, 1) == -0x100000000l);
    assert(sarfast32(-0xDECAF, 8) == -0xDED);

    assert(sarui(-63, 3) == -8);
    assert(sarul(-0x200000000l, 1) == -0x100000000l);
    assert(sarufast32(-0xDECAF, 8) == -0xDED);

    return 0;
}
