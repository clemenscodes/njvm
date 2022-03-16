#ifndef _SDA_TEST_H
#define _SDA_TEST_H

#include "cmocka/cmocka.h"
#include "sda.h"

const struct CMUnitTest sda_unit_tests[2];

void test_default_sda(void **state);
void test_initialize_sda(void **state);

#endif
