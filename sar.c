/*
 * Portable C arithmetic right shift (sar)
 *
 * The C specification leaves the right shift m >> n
 * implementation-defined if m is a negative integer.
 *     (ISO/IEC 9899:TC2 6.5.7:5, p84-85)
 *
 * The logical right shift inserts 0s in the high bits.
 *
 * The arithmetic right shift inserts 1s in the high bits if the target
 * m is negative, but inserts 0s otherwise.
 *
 * This preserves its sign, and makes
 *      m >> n  equal to  m/2**n ,
 * rounded towards -ININITY.
 *
 * The sar* functions below perform arithmetic right shifts, independent
 * of which shift is given by the implementation.
 *
 * They compile to the single shift instruction if the implementation
 * provides it, and are always branchless and small.
 *
 * Context:
 *
 * limits.h (optional)
 *     LLONG_MAX
 *
 * stdint.h
 *     integer types and macros implied by their presence
 *
 * MIT LICENSE Copyright (c) 2020 Rupert Tombs
 */

/* use include guards outside your files */
#define SAR_C

/* macro implementation TODO doc */
#define sarlogical(m) (((0*(m) - 1) >> 1) > 0)
#define sardo(m) (0*(m) - (sarlogical(m) & (m < 0)))
#define sarhigh(m, n) (sardo(m) ^ (sardo(m) >> (n)))
#define sarshift(m, n) (((m) >> (n)) | sarhigh(m, n))


static signed char 
sarc(signed char m, uint_fast8_t n)
{
    return sarshift(m, n);
}

static short int
sars(short int m, uint_fast8_t n)
{
    return sarshift(m, n);
}

static int
sari(int m, uint_fast8_t n)
{
    return sarshift(m, n);
}

static long int
sarl(long int m, uint_fast8_t n)
{
    return sarshift(m, n);
}

static long long int
sarll(long long int m, uint_fast8_t n)
{
    return sarshift(m, n);
}

/* integers included by stdint.h */
static intmax_t
sarmax(intmax_t m, uint_fast8_t n)
{
    return sarshift(m, n);
}

static int_least8_t
sarleast8(int_least8_t m, uint_fast8_t n)
{
    return sarshift(m, n);
}

static int_least16_t
sarleast16(int_least16_t m, uint_fast8_t n)
{
    return sarshift(m, n);
}

static int_least32_t
sarleast32(int_least32_t m, uint_fast8_t n)
{
    return sarshift(m, n);
}

static int_least64_t
sarleast64(int_least64_t m, uint_fast8_t n)
{
    return sarshift(m, n);
}

static int_fast8_t
sarfast8(int_fast8_t m, uint_fast8_t n)
{
    return sarshift(m, n);
}

static int_fast16_t
sarfast16(int_fast16_t m, uint_fast8_t n)
{
    return sarshift(m, n);
}

static int_fast32_t
sarfast32(int_fast32_t m, uint_fast8_t n)
{
    return sarshift(m, n);
}

static int_fast64_t
sarfast64(int_fast64_t m, uint_fast8_t n)
{
    return sarshift(m, n);
}

/* exact-width integers optionally included by stdint.h */
#ifdef INT8_MAX
static int8_t
sar8(int8_t m, uint_fast8_t n)
{
    return sarshift(m, n);
}
#endif

#ifdef INT16_MAX
static int16_t
sar16(int16_t m, uint_fast8_t n)
{
    return sarshift(m, n);
}
#endif

#ifdef INT32_MAX
static int32_t
sar32(int32_t m, uint_fast8_t n)
{
    return sarshift(m, n);
}
#endif

#ifdef INT64_MAX
static int64_t
sar64(int64_t m, uint_fast8_t n)
{
    return sarshift(m, n);
}
#endif

#ifdef INTPTR_MAX
static intptr_t
sarptr(intptr_t m, uint_fast8_t n)
{
    return sarshift(m, n);
}
#endif
