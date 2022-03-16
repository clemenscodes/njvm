#include "include/support_test.h"

const struct CMUnitTest support_unit_tests[] = {
    cmocka_unit_test(test_fatalError),
    cmocka_unit_test(test_newPrimObject),
};

void test_fatalError(void **state) {}
void test_newPrimObject(void **state) {}
