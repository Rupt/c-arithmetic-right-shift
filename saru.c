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
#define sarulogical(type) (1)
#define sarudo(m, type) ((type)-((m) < 0))
#define saruhigh(m, n, type) (sarudo(m, type) ^ (sarudo(m, type) >> (n)))
#define sarushift(m, n, type) (((type)(m) >> (n)) | saruhigh(m, n, type))


static signed char
saruc(signed char m, uint_fast8_t n)
{
    return sarushift(m, n, unsigned char);
}

static short int
sarus(short int m, uint_fast8_t n)
{
    return sarushift(m, n, unsigned short int);
}

static int
sarui(int m, uint_fast8_t n)
{
    return sarushift(m, n, unsigned int);
}

static long int
sarul(long int m, uint_fast8_t n)
{
    return sarushift(m, n, unsigned long int);
}

static long long int
sarull(long long int m, uint_fast8_t n)
{
    return sarushift(m, n, unsigned long long int);
}

/* included by stdint.h */
static int_fast8_t
sarufast8(int_fast8_t m, uint_fast8_t n)
{
    return sarushift(m, n, uint_fast8_t);
}

static int_fast16_t
sarufast16(int_fast16_t m, uint_fast8_t n)
{
    return sarushift(m, n, uint_fast16_t);
}

static int_fast32_t
sarufast32(int_fast32_t m, uint_fast8_t n)
{
    return sarushift(m, n, uint_fast32_t);
}

static int_fast64_t
sarufast64(int_fast64_t m, uint_fast8_t n)
{
    return sarushift(m, n, uint_fast64_t);
}

static int_least8_t
saruleast8(int_least8_t m, uint_fast8_t n)
{
    return sarushift(m, n, uint_least8_t);
}

static int_least16_t
saruleast16(int_least16_t m, uint_fast8_t n)
{
    return sarushift(m, n, uint_least16_t);
}

static int_least32_t
saruleast32(int_least32_t m, uint_fast8_t n)
{
    return sarushift(m, n, uint_least32_t);
}

static int_least64_t
saruleast64(int_least64_t m, uint_fast8_t n)
{
    return sarushift(m, n, uint_least64_t);
}

static intmax_t
sarumax(intmax_t m, uint_fast8_t n)
{
    return sarushift(m, n, uintmax_t);
}

/* optionally included by stdint.h */
#ifdef INT8_MAX
static int8_t
saru8(int8_t m, uint_fast8_t n)
{
    return sarushift(m, n, uint8_t);
}
#endif

#ifdef INT16_MAX
static int16_t
saru16(int16_t m, uint_fast8_t n)
{
    return sarushift(m, n, uint16_t);
}
#endif

#ifdef INT32_MAX
static int32_t
saru32(int32_t m, uint_fast8_t n)
{
    return sarushift(m, n, uint32_t);
}
#endif

#ifdef INT64_MAX
static int64_t
saru64(int64_t m, uint_fast8_t n)
{
    return sarushift(m, n, uint64_t);
}
#endif

#ifdef INTPTR_MAX
static intptr_t
saruptr(intptr_t m, uint_fast8_t n)
{
    return sarushift(m, n, uintptr_t);
}
#endif
