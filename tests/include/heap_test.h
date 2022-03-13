#ifndef _HEAP_TEST_H
#define _HEAP_TEST_H

#include "cmocka.h"
#include "heap.h"

const struct CMUnitTest heap_unit_tests[4];

void test_default_heap(void **state);
void test_initialize_heap(void **state);
void test_alloc(void **state);
void test_print_heap(void **state);

#endif
