/*
 * Version of sar with forced correction of logical shifts.
 *
 * Made for use in testing ("test.c").
 *
 * Context:
 * stdint.h
 *     integer types and macros implied by their presence
 *
 * MIT LICENSE Copyright (c) 2020 Rupert Tombs
 */

/* Use external include guards. */
#define SARU_C

/*
 * Modified from SARBODY in "sar.c".
 *
 * Force logical right shifts by casting to unsigned types.
 */
#define SARUBODY(type, utype)                                          \
    const int logical = (((utype)-1) >> 1) > 0;                      \
    union {type i; utype u;} fix, sar;                                 \
    fix.u = -(logical & (m < 0));                                      \
    sar.u = ((utype)m >> n) | (fix.u ^ (fix.u >> n));                  \
    return sar.i


static signed char
saruc(signed char m, uint_fast8_t n)
{
    SARUBODY(signed char, unsigned char);
}

static short int
sarus(short int m, uint_fast8_t n)
{
    SARUBODY(short int, unsigned short int);
}

static int
sarui(int m, uint_fast8_t n)
{
    SARUBODY(int, unsigned int);
}

static long int
sarul(long int m, uint_fast8_t n)
{
    SARUBODY(long int, unsigned long int);
}

static long long int
sarull(long long int m, uint_fast8_t n)
{
    SARUBODY(long long int, unsigned long long int);
}

/* included in stdint.h */
static int_fast8_t
sarufast8(int_fast8_t m, uint_fast8_t n)
{
    SARUBODY(int_fast8_t, uint_fast8_t);
}

static int_fast16_t
sarufast16(int_fast16_t m, uint_fast8_t n)
{
    SARUBODY(int_fast16_t, uint_fast16_t);
}

static int_fast32_t
sarufast32(int_fast32_t m, uint_fast8_t n)
{
    SARUBODY(int_fast32_t, uint_fast32_t);
}

static int_fast64_t
sarufast64(int_fast64_t m, uint_fast8_t n)
{
    SARUBODY(int_fast64_t, uint_fast64_t);
}

static int_least8_t
saruleast8(int_least8_t m, uint_fast8_t n)
{
    SARUBODY(int_least8_t, uint_least8_t);
}

static int_least16_t
saruleast16(int_least16_t m, uint_fast8_t n)
{
    SARUBODY(int_least16_t, uint_least16_t);
}

static int_least32_t
saruleast32(int_least32_t m, uint_fast8_t n)
{
    SARUBODY(int_least32_t, uint_least32_t);
}

static int_least64_t
saruleast64(int_least64_t m, uint_fast8_t n)
{
    SARUBODY(int_least64_t, uint_least64_t);
}

static intmax_t
sarumax(intmax_t m, uint_fast8_t n)
{
    SARUBODY(intmax_t, uintmax_t);
}

/* optionally included in stdint.h */
#ifdef INT8_MAX
static int8_t
saru8(int8_t m, uint_fast8_t n)
{
    SARUBODY(int8_t, uint8_t);
}
#endif

#ifdef INT16_MAX
static int16_t
saru16(int16_t m, uint_fast8_t n)
{
    SARUBODY(int16_t, uint16_t);
}
#endif

#ifdef INT32_MAX
static int32_t
saru32(int32_t m, uint_fast8_t n)
{
    SARUBODY(int32_t, uint32_t);
}
#endif

#ifdef INT64_MAX
static int64_t
saru64(int64_t m, uint_fast8_t n)
{
    SARUBODY(int64_t, uint64_t);
}
#endif

#ifdef INTPTR_MAX
static intptr_t
saruptr(intptr_t m, uint_fast8_t n)
{
    SARUBODY(intptr_t, uintptr_t);
}
#endif
