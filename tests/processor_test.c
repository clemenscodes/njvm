#include "include/processor_test.h"

const struct CMUnitTest processor_unit_tests[] = {
    cmocka_unit_test(test_init),
    cmocka_unit_test(test_execute),
    cmocka_unit_test(test_execute_instruction),
    cmocka_unit_test(test_halt_instruction),
    cmocka_unit_test(test_pushc_instruction),
    cmocka_unit_test(test_add_instruction),
    cmocka_unit_test(test_sub_instruction),
    cmocka_unit_test(test_mul_instruction),
    cmocka_unit_test(test_div_instruction),
    cmocka_unit_test(test_mod_instruction),
    cmocka_unit_test(test_wrchr_instruction),
    cmocka_unit_test(test_rdchr_instruction),
    cmocka_unit_test(test_rdint_instruction),
    cmocka_unit_test(test_wrint_instruction),
    cmocka_unit_test(test_pushg_instruction),
    cmocka_unit_test(test_popg_instruction),
    cmocka_unit_test(test_asf_instruction),
    cmocka_unit_test(test_rsf_instruction),
    cmocka_unit_test(test_pushl_instruction),
    cmocka_unit_test(test_popl_instruction),
    cmocka_unit_test(test_eq_instruction),
    cmocka_unit_test(test_ne_instruction),
    cmocka_unit_test(test_lt_instruction),
    cmocka_unit_test(test_le_instruction),
    cmocka_unit_test(test_gt_instruction),
    cmocka_unit_test(test_ge_instruction),
    cmocka_unit_test(test_jump_instruction),
    cmocka_unit_test(test_brf_instruction),
    cmocka_unit_test(test_brt_instruction),
    cmocka_unit_test(test_call_instruction),
    cmocka_unit_test(test_ret_instruction),
    cmocka_unit_test(test_drop_instruction),
    cmocka_unit_test(test_pushr_instruction),
    cmocka_unit_test(test_popr_instruction),
    cmocka_unit_test(test_dup_instruction),
    cmocka_unit_test(test_new_instruction),
    cmocka_unit_test(test_getf_instruction),
    cmocka_unit_test(test_putf_instruction),
    cmocka_unit_test(test_newa_instruction),
    cmocka_unit_test(test_getfa_instruction),
    cmocka_unit_test(test_putfa_instruction),
    cmocka_unit_test(test_getsz_instruction),
    cmocka_unit_test(test_pushn_instruction),
    cmocka_unit_test(test_refeq_instruction),
    cmocka_unit_test(test_refne_instruction),
};

void test_init(void **state) {}
void test_execute(void **state) {}
void test_execute_instruction(void **state) {}
void test_halt_instruction(void **state) {}
void test_pushc_instruction(void **state) {}
void test_add_instruction(void **state) {}
void test_sub_instruction(void **state) {}
void test_mul_instruction(void **state) {}
void test_div_instruction(void **state) {}
void test_mod_instruction(void **state) {}
void test_wrchr_instruction(void **state) {}
void test_rdchr_instruction(void **state) {}
void test_rdint_instruction(void **state) {}
void test_wrint_instruction(void **state) {}
void test_pushg_instruction(void **state) {}
void test_popg_instruction(void **state) {}
void test_asf_instruction(void **state) {}
void test_rsf_instruction(void **state) {}
void test_pushl_instruction(void **state) {}
void test_popl_instruction(void **state) {}
void test_eq_instruction(void **state) {}
void test_ne_instruction(void **state) {}
void test_lt_instruction(void **state) {}
void test_le_instruction(void **state) {}
void test_gt_instruction(void **state) {}
void test_ge_instruction(void **state) {}
void test_jump_instruction(void **state) {}
void test_brf_instruction(void **state) {}
void test_brt_instruction(void **state) {}
void test_call_instruction(void **state) {}
void test_ret_instruction(void **state) {}
void test_drop_instruction(void **state) {}
void test_pushr_instruction(void **state) {}
void test_popr_instruction(void **state) {}
void test_dup_instruction(void **state) {}
void test_new_instruction(void **state) {}
void test_getf_instruction(void **state) {}
void test_putf_instruction(void **state) {}
void test_newa_instruction(void **state) {}
void test_getfa_instruction(void **state) {}
void test_putfa_instruction(void **state) {}
void test_getsz_instruction(void **state) {}
void test_pushn_instruction(void **state) {}
void test_refeq_instruction(void **state) {}
void test_refne_instruction(void **state) {}
