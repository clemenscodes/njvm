#include "include/utils_test.h"

void test_utils(void **state) {
    ObjRef obj_ref = new_composite_object(4);
    assert_false(IS_PRIMITIVE(obj_ref));
    assert_int_equal(GET_ELEMENT_COUNT(obj_ref), 4);
}
