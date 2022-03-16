#ifndef _GC_TEST_H
#define _GC_TEST_H

#include "cmocka/cmocka.h"
#include "gc.h"

const struct CMUnitTest gc_unit_tests[13];

void test_nullify_heap_stats(void **state);
void test_swap_heaps(void **state);
void test_relocate_registers(void **state);
void test_relocate_stack_objects(void **state);
void test_relocate_sda_objects(void **state);
void test_relocate(void **state);
void test_relocate_returns_null(void **state);
void test_copy_obj_ref_to_free_memory(void **state);
void test_collect_stats(void **state);
void test_print_gc_stats(void **state);
void test_purge_heap(void **state);
void test_scan(void **state);
void test_run_gc(void **state);

#endif
