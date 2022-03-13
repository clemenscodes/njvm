#ifndef _DEBUGGER_TEST_H
#define _DEBUGGER_TEST_H

#include "cmocka.h"
#include "debugger.h"

const struct CMUnitTest debugger_unit_tests[9];

void test_debug(void **state);
void test_prompt(void **state);
void test_inspect(void **state);
void test_step(void **state);
void test_next(void **state);
void test_run(void **state);
void test_set_breakpoint(void **state);
void test_print_obj_ref(void **state);

#endif
