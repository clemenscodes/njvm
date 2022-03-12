#include "include/utils_test.h"

void test_utils(void **state) {
    initialize_heap(DEFAULT_HEAP_SIZE);
    int set_size = 4;
    ObjRef obj_ref = new_composite_object(set_size);
    assert_false(IS_PRIMITIVE(obj_ref));
    int get_size = GET_ELEMENT_COUNT(obj_ref);
    assert_int_equal(set_size, get_size);
    for (int i = 0; i < set_size; i++) {
        assert_null(GET_REFS_PTR(obj_ref)[i]);
    }
}
