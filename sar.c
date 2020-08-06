/*
 * Portable C signed arithmetic right shift (sar)
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
 * Macro for the signed arithmetic shift function body.
 * Designed to be branchless with maximum portability.
 *
 * Performs the implemented right shift, then fills in the high bits
 * if and only if needed.
 *
 * `logical' flags if the implementation logically shifts this type.
 *
 * Bits in `fix' are set to binary 1...1 if the high fill is needed,
 * but to 0...0 otherwise.
 *
 * The motif (fix.i ^ (fix.i >> n)) twiddles 1s to the n high bits (and
 * 0s thereafter) if fix is 1...1, but is 0...0 otherwise.
 *
 * The union is intended to avoid undefined or implementation-defined
 * behavior in representation of -1 and in casting unsigned to signed.
 *
 * Arguments type and utype are an integer and its unsigned equivalent.
 */
#define SARBODY(type, utype)                                           \
    const utype logical = (((type)-1) >> 1) > 0;                       \
    union {type i; utype u;} fix;                                      \
    fix.u = -(logical & (m < 0));                                      \
    return (m >> n) | (fix.i ^ (fix.i >> n))


static signed char
sarc(signed char m, uint_fast8_t n)
{
    SARBODY(signed char, unsigned char);
}

static short int
sars(short int m, uint_fast8_t n)
{
    SARBODY(short int, unsigned short int);
}

static int
sari(int m, uint_fast8_t n)
{
    SARBODY(int, unsigned int);
}

static long int
sarl(long int m, uint_fast8_t n)
{
    SARBODY(long int, unsigned long int);
}

static long long int
sarll(long long int m, uint_fast8_t n)
{
    SARBODY(long long int, unsigned long long int);
}

/* included in stdint.h */
static int_fast8_t
sarfast8(int_fast8_t m, uint_fast8_t n)
{
    SARBODY(int_fast8_t, uint_fast8_t);
}

static int_fast16_t
sarfast16(int_fast16_t m, uint_fast8_t n)
{
    SARBODY(int_fast16_t, uint_fast16_t);
}

static int_fast32_t
sarfast32(int_fast32_t m, uint_fast8_t n)
{
    SARBODY(int_fast32_t, uint_fast32_t);
}

static int_fast64_t
sarfast64(int_fast64_t m, uint_fast8_t n)
{
    SARBODY(int_fast64_t, uint_fast64_t);
}

static int_least8_t
sarleast8(int_least8_t m, uint_fast8_t n)
{
    SARBODY(int_least8_t, uint_least8_t);
}

static int_least16_t
sarleast16(int_least16_t m, uint_fast8_t n)
{
    SARBODY(int_least16_t, uint_least16_t);
}

static int_least32_t
sarleast32(int_least32_t m, uint_fast8_t n)
{
    SARBODY(int_least32_t, uint_least32_t);
}

static int_least64_t
sarleast64(int_least64_t m, uint_fast8_t n)
{
    SARBODY(int_least64_t, uint_least64_t);
}

static intmax_t
sarmax(intmax_t m, uint_fast8_t n)
{
    SARBODY(intmax_t, uintmax_t);
}

/* optionally included in stdint.h */
#ifdef INT8_MAX
static int8_t
sar8(int8_t m, uint_fast8_t n)
{
    SARBODY(int8_t, uint8_t);
}
#endif

#ifdef INT16_MAX
static int16_t
sar16(int16_t m, uint_fast8_t n)
{
    SARBODY(int16_t, uint16_t);
}
#endif

#ifdef INT32_MAX
static int32_t
sar32(int32_t m, uint_fast8_t n)
{
    SARBODY(int32_t, uint32_t);
}
#endif

#ifdef INT64_MAX
static int64_t
sar64(int64_t m, uint_fast8_t n)
{
    SARBODY(int64_t, uint64_t);
}
#endif

#ifdef INTPTR_MAX
static intptr_t
sarptr(intptr_t m, uint_fast8_t n)
{
    SARBODY(intptr_t, uintptr_t);
}
#endif
