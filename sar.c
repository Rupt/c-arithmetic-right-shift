/*
 * Portable C _s_igned _a_rithmetic _r_ight shift (sar)
 *
 * The C specification leaves the right shift m >> n
 * implementation-defined if m is a negative integer.
 *     (ISO/IEC 9899:TC2 6.5.7:5, p84-85)
 *
 * The logical right shift inserts 0s in its high binary bits.
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
 * They compile to code which uses the single shift instruction if the
 * implementation provides it, and which is always branchless and small.
 *
 * Context:
 * stdint.h
 *     integer types and macros implied by their presence
 *
 * MIT LICENSE Copyright (c) 2020 Rupert Tombs
 */

/* Use external include guards. */
#define SAR_C

/*
 * Macro signed arithmetic shift
 *
 * sarshift does generic m >> n, but duplicates side effects (unsafe).
 * It sets the n high bits by a bitwise OR with the value of sarhigh.
 *
 * sarhigh sets its n high bits by a twiddle from sardo.
 *
 * sardo returns -1 (binary 1...1) if we need to set the high bits, with
 * the motif 0*(m) used for type casting.
 *
 * sarlogical flags if the implementation provides a logical shift.
 */
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

/* included in stdint.h */
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

static intmax_t
sarmax(intmax_t m, uint_fast8_t n)
{
    return sarshift(m, n);
}

/* optionally included in stdint.h */
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
