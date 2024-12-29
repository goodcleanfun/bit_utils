#ifndef BIT_UTILS_H
#define BIT_UTILS_H

// MSVC implementation by Pavel P (https://gist.github.com/pps83/3210a2f980fd02bb2ba2e5a1fc4a2ef0)
#if defined(_MSC_VER) && !defined(__clang__)
#include <intrin.h>

#define __builtin_popcount __popcnt
#define __builtin_popcountll __popcnt64

static inline int __builtin_popcountl(unsigned long x)
{
    return sizeof(x) == 8 ? __popcnt64(x) : __popcnt((unsigned)x);
}

static inline int __builtin_ctz(unsigned x)
{
    return (int)_tzcnt_u32(x);
}

static inline int __builtin_ctzll(unsigned long long x)
{
#ifdef _WIN64
    return (int)_tzcnt_u64(x);
#else
    return !!unsigned(x) ? __builtin_ctz((unsigned)x) : 32 + __builtin_ctz((unsigned)(x >> 32));
#endif
}

static inline int __builtin_ctzl(unsigned long x)
{
    return sizeof(x) == 8 ? __builtin_ctzll(x) : __builtin_ctz((unsigned)x);
}

static inline int __builtin_clz(unsigned x)
{
    return (int)_lzcnt_u32(x);
}

static inline int __builtin_clzll(unsigned long long x)
{
#ifdef _WIN64
    return (int)_lzcnt_u64(x);
#else
    return !!unsigned(x >> 32) ? __builtin_clz((unsigned)(x >> 32)) : 32 + __builtin_clz((unsigned)x);
#endif
}

static inline int __builtin_clzl(unsigned long x)
{
    return sizeof(x) == 8 ? __builtin_clzll(x) : __builtin_clz((unsigned)x);
}
#endif // defined(_MSC_VER) && !defined(__clang__)

#define clz(x) _Generic((x) \
    , unsigned: __builtin_clz \
    , int: __builtin_clz \
    , unsigned long: __builtin_clzl \
    , long: __builtin_clzl \
    , unsigned long long: __builtin_clzll \
    , long long: __builtin_clzll \
    )(x)

#define ctz(x) _Generic((x) \
    , unsigned: __builtin_ctz \
    , int: __builtin_ctz \
    , unsigned long: __builtin_ctzl \
    , long: __builtin_ctzl \
    , unsigned long long: __builtin_ctzll \
    , long long: __builtin_ctzll \
    )(x)

#define popcount(x) _Generic((x) \
    , unsigned: __builtin_popcount \
    , int: __builtin_popcount \
    , unsigned long: __builtin_popcountl \
    , long: __builtin_popcountl \
    , unsigned long long: __builtin_popcountll \
    , long long: __builtin_popcountll \
    )(x)

#endif // BIT_UTILS_H