#include "include/opcode_test.h"

const struct CMUnitTest opcode_tests[] = {
    cmocka_unit_test(test_encode_opcode),
    cmocka_unit_test(test_decode_opcode),
};

void test_encode_opcode(void **state) {
    assert_int_equal(encode_opcode(halt), 0x00000000);
    assert_int_equal(encode_opcode(pushc), 0x01000000);
    assert_int_equal(encode_opcode(add), 0x02000000);
    assert_int_equal(encode_opcode(sub), 0x03000000);
    assert_int_equal(encode_opcode(mul), 0x04000000);
    assert_int_equal(encode_opcode(divide), 0x05000000);
    assert_int_equal(encode_opcode(mod), 0x06000000);
    assert_int_equal(encode_opcode(rdint), 0x07000000);
    assert_int_equal(encode_opcode(wrint), 0x08000000);
    assert_int_equal(encode_opcode(rdchr), 0x09000000);
    assert_int_equal(encode_opcode(wrchr), 0x0a000000);
    assert_int_equal(encode_opcode(pushg), 0x0b000000);
    assert_int_equal(encode_opcode(popg), 0x0c000000);
    assert_int_equal(encode_opcode(asf), 0x0d000000);
    assert_int_equal(encode_opcode(rsf), 0x0e000000);
    assert_int_equal(encode_opcode(pushl), 0x0f000000);
    assert_int_equal(encode_opcode(popl), 0x10000000);
    assert_int_equal(encode_opcode(eq), 0x11000000);
    assert_int_equal(encode_opcode(ne), 0x12000000);
    assert_int_equal(encode_opcode(lt), 0x13000000);
    assert_int_equal(encode_opcode(le), 0x14000000);
    assert_int_equal(encode_opcode(gt), 0x15000000);
    assert_int_equal(encode_opcode(ge), 0x16000000);
    assert_int_equal(encode_opcode(jump), 0x17000000);
    assert_int_equal(encode_opcode(brf), 0x18000000);
    assert_int_equal(encode_opcode(brt), 0x19000000);
    assert_int_equal(encode_opcode(call), 0x1a000000);
    assert_int_equal(encode_opcode(ret), 0x1b000000);
    assert_int_equal(encode_opcode(drop), 0x1c000000);
    assert_int_equal(encode_opcode(pushr), 0x1d000000);
    assert_int_equal(encode_opcode(popr), 0x1e000000);
    assert_int_equal(encode_opcode(dup), 0x1f000000);
    assert_int_equal(encode_opcode(new), 0x20000000);
    assert_int_equal(encode_opcode(getf), 0x21000000);
    assert_int_equal(encode_opcode(putf), 0x22000000);
    assert_int_equal(encode_opcode(newa), 0x23000000);
    assert_int_equal(encode_opcode(getfa), 0x24000000);
    assert_int_equal(encode_opcode(putfa), 0x25000000);
    assert_int_equal(encode_opcode(getsz), 0x26000000);
    assert_int_equal(encode_opcode(pushn), 0x27000000);
    assert_int_equal(encode_opcode(refeq), 0x28000000);
    assert_int_equal(encode_opcode(refne), 0x29000000);
}

void test_decode_opcode(void **state) {
    assert_int_equal(decode_opcode(0x00000000), halt);
    assert_int_equal(decode_opcode(0x01000000), pushc);
    assert_int_equal(decode_opcode(0x02000000), add);
    assert_int_equal(decode_opcode(0x03000000), sub);
    assert_int_equal(decode_opcode(0x04000000), mul);
    assert_int_equal(decode_opcode(0x05000000), divide);
    assert_int_equal(decode_opcode(0x06000000), mod);
    assert_int_equal(decode_opcode(0x07000000), rdint);
    assert_int_equal(decode_opcode(0x08000000), wrint);
    assert_int_equal(decode_opcode(0x09000000), rdchr);
    assert_int_equal(decode_opcode(0x0a000000), wrchr);
    assert_int_equal(decode_opcode(0x0b000000), pushg);
    assert_int_equal(decode_opcode(0x0c000000), popg);
    assert_int_equal(decode_opcode(0x0d000000), asf);
    assert_int_equal(decode_opcode(0x0e000000), rsf);
    assert_int_equal(decode_opcode(0x0f000000), pushl);
    assert_int_equal(decode_opcode(0x10000000), popl);
    assert_int_equal(decode_opcode(0x11000000), eq);
    assert_int_equal(decode_opcode(0x12000000), ne);
    assert_int_equal(decode_opcode(0x13000000), lt);
    assert_int_equal(decode_opcode(0x14000000), le);
    assert_int_equal(decode_opcode(0x15000000), gt);
    assert_int_equal(decode_opcode(0x16000000), ge);
    assert_int_equal(decode_opcode(0x17000000), jump);
    assert_int_equal(decode_opcode(0x18000000), brf);
    assert_int_equal(decode_opcode(0x19000000), brt);
    assert_int_equal(decode_opcode(0x1a000000), call);
    assert_int_equal(decode_opcode(0x1b000000), ret);
    assert_int_equal(decode_opcode(0x1c000000), drop);
    assert_int_equal(decode_opcode(0x1d000000), pushr);
    assert_int_equal(decode_opcode(0x1e000000), popr);
    assert_int_equal(decode_opcode(0x1f000000), dup);
    assert_int_equal(decode_opcode(0x20000000), new);
    assert_int_equal(decode_opcode(0x21000000), getf);
    assert_int_equal(decode_opcode(0x22000000), putf);
    assert_int_equal(decode_opcode(0x23000000), newa);
    assert_int_equal(decode_opcode(0x24000000), getfa);
    assert_int_equal(decode_opcode(0x25000000), putfa);
    assert_int_equal(decode_opcode(0x26000000), getsz);
    assert_int_equal(decode_opcode(0x27000000), pushn);
    assert_int_equal(decode_opcode(0x28000000), refeq);
    assert_int_equal(decode_opcode(0x29000000), refne);
}
