#include <stdint.h>
#include "greatest/greatest.h"

#include "bit_utils.h"

TEST test_bit_utils(void) {
    ASSERT_EQ(popcount(0), 0);
    ASSERT_EQ(popcount(0x80000000), 1);

    ASSERT_EQ(clz(0), 32);
    ASSERT_EQ(clz(1), 31);
    ASSERT_EQ(clz(0x80000000), 0);

    ASSERT_EQ(clz(0ull), 64);
    ASSERT_EQ(clz(1ull), 63);
    ASSERT_EQ(clz(0x8000000000000000), 0);

    ASSERT_EQ(ctz(0), 32);
    ASSERT_EQ(ctz(1), 0);
    ASSERT_EQ(ctz(0x80000000), 31);

    ASSERT_EQ(ctz(0ull), 64);
    ASSERT_EQ(ctz(1ull), 0);
    ASSERT_EQ(ctz(0x8000000000000000), 63);

    PASS();
}

/* Add definitions that need to be in the test runner's main file. */
GREATEST_MAIN_DEFS();

int32_t main(int32_t argc, char **argv) {
    GREATEST_MAIN_BEGIN();      /* command-line options, initialization. */

    RUN_TEST(test_bit_utils);

    GREATEST_MAIN_END();        /* display results */
}
