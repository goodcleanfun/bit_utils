#ifndef BIT_UTILS_H
#define BIT_UTILS_H

#include <stdint.h>
#include <stdbool.h>

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


static inline uint64_t u64_floor_log2(uint64_t x) {
    return x == 0 ? 0 : 63 - clz(x);
}

static inline uint64_t u64_ceil_log2(uint64_t x) {
    return x == 0ULL || x == 1ULL ? 0 : 64 - clz(x - 1ULL);
}

// Smallest power of 2 not less than x
static inline uint64_t u64_hyper_ceil(uint64_t x) {
    return (1ULL << u64_ceil_log2(x));
}

static inline uint64_t u64_ceil_div(uint64_t x, uint64_t y) {
    if (y == 0 || x == 0) return 0; // Avoid division by zero
    return (1ULL + ((x - 1ULL) / y));
}

static inline uint32_t u32_floor_log2(uint32_t x) {
    return x == 0 ? 0 : 31 - clz(x);
}

static inline uint32_t u32_ceil_log2(uint32_t x) {
    return x == 0 || x == 1 ? 0 : 32 - clz(x - 1);
}

static inline uint32_t u32_hyper_ceil(uint32_t x) {
    return (1 << u32_ceil_log2(x));
}

static inline uint32_t u32_ceil_div(uint32_t x, uint32_t y) {
    if (y == 0 || x == 0) return 0; // Avoid division by zero
    return (1 + ((x - 1) / y));
}

#define floor_log2(x) _Generic((x) \
    , uint32_t: u32_floor_log2 \
    , int32_t: u32_floor_log2 \
    , uint64_t: u64_floor_log2 \
    , int64_t: u64_floor_log2 \
    )(x)

#define ceil_log2(x) _Generic((x) \
    , uint32_t: u32_ceil_log2 \
    , int32_t: u32_ceil_log2 \
    , uint64_t: u64_ceil_log2 \
    , int64_t: u64_ceil_log2 \
    )(x)

#define hyper_ceil(x) _Generic((x) \
    , uint32_t: u32_hyper_ceil \
    , int32_t: u32_hyper_ceil \
    , uint64_t: u64_hyper_ceil \
    , int64_t: u64_hyper_ceil \
    )(x)

#define ceil_div(x, y) _Generic((x, y) \
    , uint32_t: u32_ceil_div \
    , int32_t: u32_ceil_div \
    , uint64_t: u64_ceil_div \
    , int64_t: u64_ceil_div \
    )(x, y)


static inline bool i8_is_power_of_two(int8_t x) {
    return x > 0 && ((x & (x - 1)) == 0);
}

static inline bool u8_is_power_of_two(uint8_t x) {
    return x && ((x & (x - 1)) == 0);
}

static inline bool i16_is_power_of_two(int16_t x) {
    return x > 0 && ((x & (x - 1)) == 0);
}

static inline bool u16_is_power_of_two(uint16_t x) {
    return x && ((x & (x - 1)) == 0);
}

static inline bool i32_is_power_of_two(int32_t x) {
    return x > 0 && ((x & (x - 1)) == 0);
}

static inline bool u32_is_power_of_two(uint32_t x) {
    return x && ((x & (x - 1)) == 0);
}

static inline bool i64_is_power_of_two(int64_t x) {
    return x > 0 && ((x & (x - 1ULL)) == 0);
}

static inline bool u64_is_power_of_two(uint64_t x) {
    return x && ((x & (x - 1ULL)) == 0);
}

#define is_power_of_two(x) _Generic((x) \
    , uint32_t: u32_is_power_of_two \
    , int32_t: i32_is_power_of_two \
    , uint64_t: u64_is_power_of_two \
    , int64_t: i64_is_power_of_two \
    , int8_t: i8_is_power_of_two \
    , uint8_t: u8_is_power_of_two \
    , int16_t: i16_is_power_of_two \
    , uint16_t: u16_is_power_of_two \
    )(x)

#endif // BIT_UTILS_H