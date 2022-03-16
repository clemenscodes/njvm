#ifndef _HEAP_TEST_H
#define _HEAP_TEST_H

#include "cmocka/cmocka.h"
#include "heap.h"

const struct CMUnitTest heap_unit_tests[5];

void test_default_heap(void **state);
void test_initialize_heap(void **state);
void test_alloc(void **state);
void test_print_heap_objects(void **state);
void test_print_heap_bytes(void **state);

#endif
