#ifndef _GC_TEST_H
#define _GC_TEST_H

#include "cmocka.h"
#include "gc.h"

void test_run_gc(void **state);
void test_copy_obj_ref(void **state);
void test_copy_obj_ref_returns_null(void **state);

#endif
