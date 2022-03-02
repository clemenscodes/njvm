#include "test.h"

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_halt),
        cmocka_unit_test(test_pushc),
        cmocka_unit_test(test_encode_instruction),
        cmocka_unit_test(test_decode_instruction),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
