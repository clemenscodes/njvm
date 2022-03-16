#ifndef _STACK_TEST_H
#define _STACK_TEST_H

#include "cmocka.h"
#include "stack.h"

const struct CMUnitTest stack_unit_tests[2];

void test_default_stack(void **state);
void test_initialize_stack(void **state);

#endif
