#include <stdint.h>
#include "greatest/greatest.h"

#include "bit_utils.h"

TEST test_bit_utils(void) {
    unsigned int x = 0;
    unsigned int y = 0x80000000;
    int popx = popcount(x);
    ASSERT_EQ(popx, 0);
    int popy = popcount(y);
    ASSERT_EQ(popy, 1);
    PASS();
}

/* Add definitions that need to be in the test runner's main file. */
GREATEST_MAIN_DEFS();

int32_t main(int32_t argc, char **argv) {
    GREATEST_MAIN_BEGIN();      /* command-line options, initialization. */

    RUN_TEST(test_bit_utils);

    GREATEST_MAIN_END();        /* display results */
}
