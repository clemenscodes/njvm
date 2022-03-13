#ifndef _MACROS_TEST_H
#define _MACROS_TEST_H

#include "cmocka.h"
#include "macros.h"
#include "bytecode.h"
#include "immediate.h"
#include "debugger.h"

const struct CMUnitTest macros_unit_tests[10];

void test_immediate_macro(void **state);
void test_sign_extend_macro(void **state);
void test_msb_macro(void **state);
void test_broken_heart_macro(void **state);
void test_is_primitive_macro(void **state);
void test_get_element_count_macro(void **state);
void test_get_refs_ptr_macro(void **state);
void test_forward_ptr_mask_macro(void **state);
void test_msb_and_bh_mask_macro(void **state);
void test_get_forward_ptr_macro(void **state);

#endif
