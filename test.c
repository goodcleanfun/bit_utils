#include <stdint.h>
#include "greatest/greatest.h"

#include "bit_utils.h"

TEST test_bit_utils(void) {
    ASSERT_EQ(popcount(0), 0);
    ASSERT_EQ(popcount(0x80000000), 1);

    ASSERT_EQ(clz(0), 32);
    ASSERT_EQ(clz(1), 31);
    ASSERT_EQ(clz(0x80000000), 0);

    ASSERT_EQ(clz(0ULL), 64);
    ASSERT_EQ(clz(1ULL), 63);
    ASSERT_EQ(clz(0x8000000000000000), 0);

    ASSERT_EQ(ctz(0), 32);
    ASSERT_EQ(ctz(1), 0);
    ASSERT_EQ(ctz(0x80000000), 31);

    ASSERT_EQ(ctz(0ULL), 64);
    ASSERT_EQ(ctz(1ULL), 0);
    ASSERT_EQ(ctz(0x8000000000000000), 63);

    ASSERT_EQ(floor_log2(0), 0);
    ASSERT_EQ(floor_log2(1), 0);
    ASSERT_EQ(floor_log2(0x80000000), 31);

    ASSERT_EQ(floor_log2(0ULL), 0);
    ASSERT_EQ(floor_log2(1ULL), 0);
    ASSERT_EQ(floor_log2(0x8000000000000000ULL), 63);

    ASSERT_EQ(ceil_log2(0), 0);
    printf("ceil_log2(1) = %u\n", ceil_log2(1));
    ASSERT_EQ(ceil_log2(1), 0);
    ASSERT_EQ(ceil_log2(0x80000000), 31);

    ASSERT_EQ(ceil_log2(0ULL), 0);
    ASSERT_EQ(ceil_log2(1ULL), 0);
    ASSERT_EQ(ceil_log2(0x8000000000000000ULL), 63);

    ASSERT_EQ(hyper_ceil(0), 1);

    ASSERT_EQ(hyper_ceil(1), 1);
    ASSERT_EQ(hyper_ceil(0x80000000), 0x80000000);

    ASSERT_EQ(hyper_ceil(0ULL), 1ULL);
    ASSERT_EQ(hyper_ceil(1ULL), 1ULL);
    ASSERT_EQ(hyper_ceil(0x8000000000000000ULL), 0x8000000000000000ULL);

    ASSERT_EQ(ceil_div(0, 1), 0);
    ASSERT_EQ(ceil_div(1, 1), 1);
    ASSERT_EQ(ceil_div(0x80000000, 1), 0x80000000);

    ASSERT_EQ(ceil_div(0ULL, 1ULL), 0ULL);
    ASSERT_EQ(ceil_div(1ULL, 1ULL), 1ULL);
    ASSERT_EQ(ceil_div(0x8000000000000000ULL, 1ULL), 0x8000000000000000ULL);

    ASSERT_EQ(ceil_div(0, 0), 0);
    ASSERT_EQ(ceil_div(1, 0), 0);
    ASSERT_EQ(ceil_div(0x80000000, 0), 0);

    ASSERT_EQ(ceil_div(0ULL, 0ULL), 0ULL);
    ASSERT_EQ(ceil_div(1ULL, 0ULL), 0ULL);
    ASSERT_EQ(ceil_div(0x8000000000000000ULL, 0ULL), 0ULL);

    PASS();
}

/* Add definitions that need to be in the test runner's main file. */
GREATEST_MAIN_DEFS();

int32_t main(int32_t argc, char **argv) {
    GREATEST_MAIN_BEGIN();      /* command-line options, initialization. */

    RUN_TEST(test_bit_utils);

    GREATEST_MAIN_END();        /* display results */
}
