#ifndef _PROCESSOR_TEST_H
#define _PROCESSOR_TEST_H

#include "cmocka.h"
#include "processor.h"

const struct CMUnitTest processor_unit_tests[45];

void test_init(void **state);
void test_execute(void **state);
void test_execute_instruction(void **state);
void test_halt_instruction(void **state);
void test_pushc_instruction(void **state);
void test_add_instruction(void **state);
void test_sub_instruction(void **state);
void test_mul_instruction(void **state);
void test_div_instruction(void **state);
void test_mod_instruction(void **state);
void test_wrchr_instruction(void **state);
void test_rdchr_instruction(void **state);
void test_rdint_instruction(void **state);
void test_wrint_instruction(void **state);
void test_pushg_instruction(void **state);
void test_popg_instruction(void **state);
void test_asf_instruction(void **state);
void test_rsf_instruction(void **state);
void test_pushl_instruction(void **state);
void test_popl_instruction(void **state);
void test_eq_instruction(void **state);
void test_ne_instruction(void **state);
void test_lt_instruction(void **state);
void test_le_instruction(void **state);
void test_gt_instruction(void **state);
void test_ge_instruction(void **state);
void test_jump_instruction(void **state);
void test_brf_instruction(void **state);
void test_brt_instruction(void **state);
void test_call_instruction(void **state);
void test_ret_instruction(void **state);
void test_drop_instruction(void **state);
void test_pushr_instruction(void **state);
void test_popr_instruction(void **state);
void test_dup_instruction(void **state);
void test_new_instruction(void **state);
void test_getf_instruction(void **state);
void test_putf_instruction(void **state);
void test_newa_instruction(void **state);
void test_getfa_instruction(void **state);
void test_putfa_instruction(void **state);
void test_getsz_instruction(void **state);
void test_pushn_instruction(void **state);
void test_refeq_instruction(void **state);
void test_refne_instruction(void **state);

#endif
