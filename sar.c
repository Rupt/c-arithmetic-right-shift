#include <limits.h>
#include <stdint.h>

/* Portable C arithmetic right shift (sar)
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
 * rounded towards -infinity.
 * 
 * The sar* functions below perform arithmetic right shifts, independent
 * of which shift is given by the implementation.
 *
 * They compile to the single shift instruction if the implementation 
 * provides it, and are always branchless and small.
 *
 * Context:
 *
 * limits.h
 *     CHAR_BIT LLONG_MAX
 * 
 * stdint.h 
 *     integer types and macros implied by their presence
 *  
 * MIT LICENSE Copyright (c) 2020 Rupert Tombs
 */

signed char sarc(signed char m, signed char n);
short int sars(short int m, short int n);
int sari(int m, int n);
long int sarl(long int m, long int n);

#ifdef LLONG_MAX
long long int sarll(long long int m, long long int n);
#endif

/* exact-width integers optionally provided by stdint.h */
#ifdef INT8_MAX
int8_t sar8(int8_t m, int8_t n);
#endif

#ifdef INT16_MAX
int16_t sar16(int16_t m, int16_t n);
#endif

#ifdef INT32_MAX
int32_t sar32(int32_t m, int32_t n);
#endif

#ifdef INT64_MAX
int64_t sar64(int64_t m, int64_t n);
#endif

#ifdef INTPTR_MAX
intptr_t sarptr(intptr_t m, intptr_t n);
#endif

/* integers necessarily provided by stdint.h if included */
#ifdef INT_LEAST8_MIN
intmax_t sarmax(intmax_t m, intmax_t n);
int_least8_t sarleast8(int_least8_t m, int_least8_t n);
int_least16_t sarleast16(int_least16_t m, int_least16_t n);
int_least32_t sarleast32(int_least32_t m, int_least32_t n);
int_least64_t sarleast64(int_least64_t m, int_least64_t n);
int_fast8_t sarfast8(int_fast8_t m, int_fast8_t n);
int_fast16_t sarfast16(int_fast16_t m, int_fast16_t n);
int_fast32_t sarfast32(int_fast32_t m, int_fast32_t n);
int_fast64_t sarfast64(int_fast64_t m, int_fast64_t n);
#endif

/* Macro to define these declared functions.
 *
 * Arguments:
 *     label is the suffix to sar.
 *     type is the signed integer type.
 *     utype is the unsigned cousin of type with the same size as type.
 * 
 * Explanation:
 *     logical flags if the implementation logically right shifts type.
 *     fill is all 1s if the high bits need to be filled.
 * 
 * we then left shift fill (which is defined since it is unsigned) to 
 * get 1s in the high bits, then logical or to set them.
 * The c standard re
 */
#define SARDEFINE(label, type, utype)                                  \
    type                                                               \
    sar##label(type m, type n)                                         \
    {                                                                  \
        const type logical = ((type)-1 >> 1) > 0;                      \
        utype fill;                                                    \
        fill = -(logical && m < 0);                                    \
        return (m >> n) | (fill << (CHAR_BIT*sizeof(m) - n));          \
    }

SARDEFINE(c, signed char, unsigned char)

SARDEFINE(s, short int, unsigned short int)

SARDEFINE(i, int, unsigned int)

SARDEFINE(l, long int, unsigned long int)

#ifdef LLONG_MAX
SARDEFINE(ll, long long int, unsigned long long int)
#endif

#ifdef INT8_MAX
SARDEFINE(8, int8_t, uint8_t)
#endif

#ifdef INT16_MAX
SARDEFINE(16, int16_t, uint16_t)
#endif

#ifdef INT32_MAX
SARDEFINE(32, int32_t, uint32_t)
#endif

#ifdef INT64_MAX
SARDEFINE(64, int64_t, uint64_t)
#endif

#ifdef INTPTR_MAX
SARDEFINE(ptr, intptr_t, uintptr_t)
#endif

#ifdef INT_LEAST8_MIN
SARDEFINE(max, intmax_t, uintmax_t)

SARDEFINE(least8, int_least8_t, int_least8_t)

SARDEFINE(least16, int_least16_t, int_least16_t)

SARDEFINE(least32, int_least32_t, int_least32_t)

SARDEFINE(least64, int_least64_t, int_least64_t)

SARDEFINE(fast8, int_fast8_t, int_fast8_t)

SARDEFINE(fast16, int_fast16_t, int_fast16_t)

SARDEFINE(fast32, int_fast32_t, int_fast32_t)

SARDEFINE(fast64, int_fast64_t, int_fast64_t)
#endif
