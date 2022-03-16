#ifndef _MACROS_TEST_H
#define _MACROS_TEST_H

#include "bytecode.h"
#include "cmocka.h"
#include "debugger.h"
#include "immediate.h"
#include "macros.h"

const struct CMUnitTest macros_unit_tests[11];

void test_immediate_macro(void **state);
void test_sign_extend_macro(void **state);
void test_msb_macro(void **state);
void test_broken_heart_macro(void **state);
void test_is_primitive_macro(void **state);
void test_is_copied_macro(void **state);
void test_get_element_count_macro(void **state);
void test_get_refs_ptr_macro(void **state);
void test_forward_ptr_mask_macro(void **state);
void test_get_forward_ptr_macro(void **state);

#endif
