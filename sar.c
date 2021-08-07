/*
 * Portable C signed arithmetic right shift (sar)
 *
 * The C standard makes  m >> n  implementation-defined if m is negative.
 *                                                    (ISO C N2176 6.5.7 6.5.7)
 *
 * The logical right shift inserts 0s in its high binary bits.
 *
 * The arithmetic right shift inserts 1s in the high bits if the target
 * m is negative, but inserts 0s otherwise. This preserves its sign, so
 *      m >> n  equals  m / 2**n ,
 * rounded towards -ININITY.
 *
 * The sar* functions below perform arithmetic right shifts, independent
 * of which shift is given by the implementation.
 *
 * They compile to code which uses the single shift instruction if the
 * implementation provides it, and which is always branchless and small.
 *
 * Context:
 * stdint.h (optional)
 *     for more integer types and macros
 *
 * MIT LICENSE Copyright (c) 2020 Rupert Tombs
 */

#ifndef SAR_C
#define SAR_C

/*
 * Macro for the signed arithmetic shift function body.
 * Designed to be branchless with maximum portability.
 *
 * Arguments type and utype are an integer and its unsigned equivalent.
 *
 * Performs the implemented right shift, then fills in the high bits
 * if and only if needed.
 *
 * `logical' flags if the implementation logically shifts this type.
 *
 * Bits in `fix' are set to binary 1...1 if the high fill is needed,
 * but to 0...0 otherwise.
 *
 * (fix ^ (fix >> n)) twiddles 1s to the n high bits (and 0s
 * after) if fix is 1...1, but is 0...0 otherwise.
 *
 * The *(type*) &fixu pun reinterprets the bits of fixu as signed.
 * It is well defined since corresponding (un-)signed types are an exception
 * to strict-aliasing rules.
 */
#define SARBODY(type, utype)                                                   \
    const int logical = (((type)-1) >> 1) > 0;                                 \
    utype fixu = -(logical & (m < 0));                                         \
    type fix = *(type*) &fixu;                                                 \
    return (m >> n) | (fix ^ (fix >> n))


static inline signed char
sarc(signed char m, char n)
{
    SARBODY(signed char, unsigned char);
}

static inline short int
sars(short int m, char n)
{
    SARBODY(short int, unsigned short int);
}

static inline int
sari(int m, char n)
{
    SARBODY(int, unsigned int);
}

static inline long
sarl(long m, char n)
{
    SARBODY(long, unsigned long);
}

static inline long long
sarll(long long m, char n)
{
    SARBODY(long long, unsigned long long);
}

/* included in stdint.h */
#ifdef UINT_FAST8_MAX
static inline int_fast8_t
sarfast8(int_fast8_t m, char n)
{
    SARBODY(int_fast8_t, uint_fast8_t);
}

static inline int_fast16_t
sarfast16(int_fast16_t m, char n)
{
    SARBODY(int_fast16_t, uint_fast16_t);
}

static inline int_fast32_t
sarfast32(int_fast32_t m, char n)
{
    SARBODY(int_fast32_t, uint_fast32_t);
}

static inline int_fast64_t
sarfast64(int_fast64_t m, char n)
{
    SARBODY(int_fast64_t, uint_fast64_t);
}

static inline int_least8_t
sarleast8(int_least8_t m, char n)
{
    SARBODY(int_least8_t, uint_least8_t);
}

static inline int_least16_t
sarleast16(int_least16_t m, char n)
{
    SARBODY(int_least16_t, uint_least16_t);
}

static inline int_least32_t
sarleast32(int_least32_t m, char n)
{
    SARBODY(int_least32_t, uint_least32_t);
}

static inline int_least64_t
sarleast64(int_least64_t m, char n)
{
    SARBODY(int_least64_t, uint_least64_t);
}

static inline intmax_t
sarmax(intmax_t m, char n)
{
    SARBODY(intmax_t, uintmax_t);
}
#endif /* ifdef UINT_FAST8_MAX */

/* optionally included in stdint.h */
#ifdef INT8_MAX
static inline int8_t
sar8(int8_t m, char n)
{
    SARBODY(int8_t, uint8_t);
}
#endif

#ifdef INT16_MAX
static inline int16_t
sar16(int16_t m, char n)
{
    SARBODY(int16_t, uint16_t);
}
#endif

#ifdef INT32_MAX
static inline int32_t
sar32(int32_t m, char n)
{
    SARBODY(int32_t, uint32_t);
}
#endif

#ifdef INT64_MAX
static inline int64_t
sar64(int64_t m, char n)
{
    SARBODY(int64_t, uint64_t);
}
#endif

#ifdef INTPTR_MAX
static inline intptr_t
sarptr(intptr_t m, char n)
{
    SARBODY(intptr_t, uintptr_t);
}
#endif

#endif /* ifndef SAR_C */
