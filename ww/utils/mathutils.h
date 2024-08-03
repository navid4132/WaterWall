#pragma once
#include "basic_types.h"
#include <math.h> //cel,log2,pow
#include <stdint.h>
#include <stdlib.h>

// windows defines min/max in header <stdlib.h> :)
#undef max
#undef min
#undef MAX
#undef MIN

// Waterwall requires minimum c11, so its ok to use this c11 feature

// NOLINTNEXTLINE
#define max(a, b) _Generic((a), unsigned int: maxUInt, int: maxInt, double: maxDouble, ssize_t: maxSsize)(a, b)

static inline unsigned int maxUInt(unsigned int a, unsigned int b)
{
    return a > b ? a : b;
}
static inline int maxInt(int a, int b)
{
    return a > b ? a : b;
}
static inline double maxDouble(double a, double b)
{
    return a > b ? a : b;
}
static inline ssize_t maxSsize(ssize_t a, ssize_t b)
{
    return a > b ? a : b;
}
static inline long maxLong(long a, long b)
{
    return a > b ? a : b;
}

// NOLINTNEXTLINE
#define min(a, b) _Generic((a), unsigned int: minUInt, int: minInt, double: minDouble, ssize_t: minSsize)(a, b)

static inline unsigned int minUInt(unsigned int a, unsigned int b)
{
    return a < b ? a : b;
}

static inline int minInt(int a, int b)
{
    return a < b ? a : b;
}
static inline double minDouble(double a, double b)
{
    return a < b ? a : b;
}
static inline ssize_t minSsize(ssize_t a, ssize_t b)
{
    return a < b ? a : b;
}
static inline long minLong(long a, long b)
{
    return a < b ? a : b;
}



#define ISSIGNED(t) (((t) (-1)) < ((t) 0))

#define UMAXOF(t) (((0x1ULL << ((sizeof(t) * 8ULL) - 1ULL)) - 1ULL) | (0xFULL << ((sizeof(t) * 8ULL) - 4ULL)))

#define SMAXOF(t) (((0x1ULL << ((sizeof(t) * 8ULL) - 1ULL)) - 1ULL) | (0x7ULL << ((sizeof(t) * 8ULL) - 4ULL)))

#define MAXOF(t) ((unsigned long long) (ISSIGNED(t) ? SMAXOF(t) : UMAXOF(t)))

#if __BIG_ENDIAN__
#ifndef htonll
#define htonll(x) (x)
#endif
#ifndef ntohll
#define ntohll(x) (x)
#endif
#else
#ifndef htonll
#define htonll(x) (((uint64_t) htonl((x) & 0xFFFFFFFF) << 32) | htonl((x) >> 32)) // NOLINT
#endif
#ifndef ntohll
#define ntohll(x) (((uint64_t) ntohl((x) & 0xFFFFFFFF) << 32) | ntohl((x) >> 32)) // NOLINT
#endif
#endif
