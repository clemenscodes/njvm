#include "include/utils_test.h"

void test_utils(void **state) {
    int set_size = 4;
    ObjRef obj_ref = new_composite_object(set_size);
    assert_false(IS_PRIMITIVE(obj_ref));
    int get_size = GET_ELEMENT_COUNT(obj_ref);
    assert_int_equal(set_size, get_size);
}
