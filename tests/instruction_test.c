#include "include/instruction_test.h"

const struct CMUnitTest instruction_unit_tests[] = {
    cmocka_unit_test(test_instruction),
    cmocka_unit_test(test_encode_instruction),
    cmocka_unit_test(test_decode_instruction),
};

void test_instruction(void **state) {
    Opcode opcode = pushc;
    Immediate immediate = 1;
    Instruction instruction = create_new_instruction(opcode, immediate);
    assert_int_equal(instruction.opcode, opcode);
    assert_int_equal(instruction.immediate, immediate);
}

void test_encode_instruction(void **state) {
    assert_int_equal(encode_instruction(pushc, 1), 0x01000001);
    assert_int_equal(encode_instruction(pushc, -1), 0x01ffffff);
}

void test_decode_instruction(void **state) {
    Instruction instruction;
    instruction = decode_instruction(0x01000001);
    assert_int_equal(instruction.opcode, pushc);
    assert_int_equal(instruction.immediate, 1);
    instruction = decode_instruction(0x01ffffff);
    assert_int_equal(instruction.opcode, pushc);
    assert_int_equal(instruction.immediate, -1);
}
