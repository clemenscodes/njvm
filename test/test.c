#include <stdarg.h>
#include <setjmp.h>
#include <stddef.h>
#include <cmocka.h>

#include "opcode.h"

static void test(void **state) {
    assert_int_equal(HALT, 0);
}

int main() {
    const struct CMUnitTest tests[] =
        {
            cmocka_unit_test(test),
        };

    return cmocka_run_group_tests(tests, NULL, NULL);
}