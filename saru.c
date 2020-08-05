/*
 * Version of sar with forced correction of logical shifts.
 *
 * Made for use in testing ("test.c").
 *
 * MIT LICENSE Copyright (c) 2020 Rupert Tombs
 */

/* Use external include guards. */
#define SARU_C

/*
 * Modified from sarshift and friends in "sar.c".
 *
 * Force logical right shifts by casting to unsigned types with 0*(u).
 */
#define sarulogical(m) (1)
#define sarudo(m) (-((m) < 0))
#define saruhigh(m, n, u) (sarudo(m) ^ ((0*(u) + sarudo(m)) >> (n)))
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

/* included by stdint.h */
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

static intmax_t
sarumax(intmax_t m, uint_fast8_t n)
{
    return sarushift(m, n, (uintmax_t)m);
}

/* optionally included by stdint.h */
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
