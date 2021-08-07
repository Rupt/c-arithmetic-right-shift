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

#ifndef SARU_C
#define SARU_C

/*
 * Modified from SARBODY in "sar.c".
 *
 * Force logical right shifts by casting to unsigned types.
 */
#define SARUBODY(type, utype)                                          \
    const int logical = (((utype)-1) >> 1) > 0;                        \
    utype fixu = -(logical & (m < 0));                                 \
    utype saru = ((utype)m >> n) | (fixu ^ (fixu >> n));               \
    return *(type*)&saru;


static inline signed char
saruc(signed char m, char n)
{
    SARUBODY(signed char, unsigned char);
}

static inline short int
sarus(short int m, char n)
{
    SARUBODY(short int, unsigned short int);
}

static inline int
sarui(int m, char n)
{
    SARUBODY(int, unsigned int);
}

static inline long
sarul(long m, char n)
{
    SARUBODY(long, unsigned long);
}

static inline long long
sarull(long long m, char n)
{
    SARUBODY(long long, unsigned long long);
}

/* included in stdint.h */
#ifdef UINT_FAST8_MAX
static inline int_fast8_t
sarufast8(int_fast8_t m, char n)
{
    SARUBODY(int_fast8_t, uint_fast8_t);
}

static inline int_fast16_t
sarufast16(int_fast16_t m, char n)
{
    SARUBODY(int_fast16_t, uint_fast16_t);
}

static inline int_fast32_t
sarufast32(int_fast32_t m, char n)
{
    SARUBODY(int_fast32_t, uint_fast32_t);
}

static inline int_fast64_t
sarufast64(int_fast64_t m, char n)
{
    SARUBODY(int_fast64_t, uint_fast64_t);
}

static inline int_least8_t
saruleast8(int_least8_t m, char n)
{
    SARUBODY(int_least8_t, uint_least8_t);
}

static inline int_least16_t
saruleast16(int_least16_t m, char n)
{
    SARUBODY(int_least16_t, uint_least16_t);
}

static inline int_least32_t
saruleast32(int_least32_t m, char n)
{
    SARUBODY(int_least32_t, uint_least32_t);
}

static inline int_least64_t
saruleast64(int_least64_t m, char n)
{
    SARUBODY(int_least64_t, uint_least64_t);
}

static inline intmax_t
sarumax(intmax_t m, char n)
{
    SARUBODY(intmax_t, uintmax_t);
}
#endif /* ifdef UINT_FAST8_MAX */

/* optionally included in stdint.h */
#ifdef INT8_MAX
static inline int8_t
saru8(int8_t m, char n)
{
    SARUBODY(int8_t, uint8_t);
}
#endif

#ifdef INT16_MAX
static inline int16_t
saru16(int16_t m, char n)
{
    SARUBODY(int16_t, uint16_t);
}
#endif

#ifdef INT32_MAX
static inline int32_t
saru32(int32_t m, char n)
{
    SARUBODY(int32_t, uint32_t);
}
#endif

#ifdef INT64_MAX
static inline int64_t
saru64(int64_t m, char n)
{
    SARUBODY(int64_t, uint64_t);
}
#endif

#ifdef INTPTR_MAX
static inline intptr_t
saruptr(intptr_t m, char n)
{
    SARUBODY(intptr_t, uintptr_t);
}
#endif

#endif /* ifdef SARU_C */
