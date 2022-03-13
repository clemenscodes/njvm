#ifndef _GC_TEST_H
#define _GC_TEST_H

#include "cmocka.h"
#include "gc.h"

const struct CMUnitTest gc_unit_tests[8];

void test_run_gc(void **state);
void test_copy_obj_ref(void **state);
void test_copy_obj_ref_returns_null(void **state);
void test_nullify_heap_stats(void **state);
void test_swap_heaps(void **state);
void test_relocate_registers(void **state);
void test_relocate_stack_objects(void **state);
void test_relocate_sda_objects(void **state);

#endif
