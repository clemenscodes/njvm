#ifndef _SUPPORT_TEST_H
#define _SUPPORT_TEST_H

#include "../lib/build/include/support.h"
#include "cmocka/cmocka.h"

const struct CMUnitTest support_unit_tests[2];

void test_fatalError(void **state);
void test_newPrimObject(void **state);

#endif
