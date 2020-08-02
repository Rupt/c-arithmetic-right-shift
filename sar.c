#include <limits.h>
#include <stdint.h>
#include <stdio.h>

/* Portable branchless arithmetic right shift (sar) in c.
 *
 * The C specification leaves the right shift m >> n 
 * implementation-defined if m is a negative integer.
 *     (ISO/IEC 9899:TC2 6.5.7, p84-85)
 *
 * An arithmetic right shift inserts 1s in the high bits.
 * A logical right shifts inserts 0s in the high bits.
 * 
 * These tools ensure that negative integers have 1s inserted,
 * independent of which shift is given by the implementation.
 *
 * Code generated is the single shift instruction if the
 * implementation provides it, and always branchless.
 *
 * Context:
 * limits.h 
 *     CHAR_BIT
 *     // for long long int if available)
 *     LLONG_MAX 
 *
 * stdint.h
 *     // for fixed-width types if available)
 *     INT8_MAX INT16_MAX INT32_MAX INT64_MAX 
 *     int8_t int16_t int32_t int64_t
 *     UINT8_MAX UINT16_MAX UINT32_MAX UINT64_MAX 
 *     uint8_t uint16_t uint32_t uint64_t
 * 
 * MIT license Copyright (c) 2020 Rupert Tombs
 *
 * TODO _Generic
 */

signed char sarc(signed char m, signed char n);
short sars(short m, short n);
int sari(int m, int n);
long int sarl(long int m, long int n);

#if defined(LLONG_MAX) && defined(ULLONG_MAX)
long long int sarll(long long int m, long long int n);
#endif

#if defined(INT8_MAX) && defined(UINT8_MAX)
int8_t sar8(int8_t m, int8_t n);
#endif

#if defined(INT16_MAX) && defined(UINT16_MAX)
int16_t sar16(int16_t m, int16_t n);
#endif

#if defined(INT32_MAX) && defined(UINT32_MAX)
int32_t sar32(int32_t m, int32_t n);
#endif

#if defined(INT64_MAX) && defined(UINT64_MAX)
int64_t sar64(int64_t m, int64_t n);
#endif

/* Macro to define these declared functions.
 *
 * Arguments:
 *     label is the suffix to sar.
 *     type is the target signed integer type.
 *     utype is an unsigned equivalent of type.
 * 
 * Explanation:
 *     logical flags if the implementation logically right shifts type.
 *     fill is all 1s if the high bits need to be filled.
 * 
 * we then left shift fill (which is defined since it is unsigned)
 * to get 1s in the high bits, then logical or (|) to insert them.
 */
#define SARDEFINE(label, type, utype) \
    type \
    sar##label(type m, type n) \
    { \
        const type logical = ((type)-1 >> 1) > 0; \
        utype fill = -(logical && m < 0); \
        return (m >> n) | (fill << (CHAR_BIT*sizeof(m) - n)); \
    }

SARDEFINE(c, signed char, unsigned char)
SARDEFINE(s, short, unsigned short)
SARDEFINE(i, int, unsigned int)
SARDEFINE(l, long int, unsigned long int)

#if defined(LLONG_MAX) && defined(ULLONG_MAX)
SARDEFINE(ll, long long int, unsigned long long int)
#endif

#if defined(INT8_MAX) && defined(UINT8_MAX)
SARDEFINE(8, int8_t, uint8_t)
#endif

#if defined(INT16_MAX) && defined(UINT16_MAX)
SARDEFINE(16, int16_t, uint16_t)
#endif

#if defined(INT32_MAX) && defined(UINT32_MAX)
SARDEFINE(32, int32_t, uint32_t)
#endif

#if defined(INT64_MAX) && defined(UINT64_MAX)
SARDEFINE(64, int64_t, uint64_t)
#endif
