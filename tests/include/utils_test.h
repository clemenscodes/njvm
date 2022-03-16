#ifndef _UTILS_TEST_H
#define _UTILS_TEST_H

#include "cmocka/cmocka.h"
#include "utils.h"

const struct CMUnitTest utils_unit_tests[13];

void test_open_file(void **state);
void test_seek_file(void **state);
void test_close_file(void **state);
void test_check_ninja_binary_format(void **state);
void test_check_ninja_version(void **state);
void test_check_ninja_instruction_count(void **state);
void test_check_ninja_variable_count(void **state);
void test_new_composite_object(void **state);
void test_get_obj_ref_bytes(void **state);
void test_get_obj_ref_size(void **state);
void test_set_broken_heart(void **state);
void test_set_forward_pointer(void **state);
void test_get_obj_ref_from_forward_pointer(void **state);

#endif
