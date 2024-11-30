#ifndef BIT_UTILS_H
#define BIT_UTILS_H

// MSVC implementation by Pavel P (https://gist.github.com/pps83/3210a2f980fd02bb2ba2e5a1fc4a2ef0)
#if defined(_MSC_VER) && !defined(__clang__)
#include <intrin.h>

#define __builtin_popcount __popcnt
#define __builtin_popcountll __popcnt64

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


static inline int clz(unsigned x)
{
    return x ? __builtin_clz(x) : 32;
}

static inline int clzl(unsigned long x)
{
    return x ? __builtin_clzl(x) : 32;
}

static inline int clzll(unsigned long long x)
{
    return x ? __builtin_clzll(x) : 64;
}

static inline int ctz(unsigned x)
{
    return x ? __builtin_ctz(x) : 32;
}

static inline int ctzl(unsigned long x)
{
    return x ? __builtin_ctzl(x) : 32;
}

static inline int ctzll(unsigned long long x)
{
    return x ? __builtin_ctzll(x) : 64;
}

static inline int popcount(unsigned x)
{
    return __builtin_popcount(x);
}

static inline int popcountl(unsigned long x)
{
    return __builtin_popcount(x);
}

static inline int popcountll(unsigned long long x)
{ 
    return __builtin_popcountll(x);
}

#endif // BIT_UTILS_H