#ifndef _HEAP_TEST_H
#define _HEAP_TEST_H

#include "cmocka.h"
#include "heap.h"

const struct CMUnitTest heap_unit_tests[3];

void test_default_heap(void **state);
void test_initialize_heap(void **state);
void test_alloc(void **state);

#endif
