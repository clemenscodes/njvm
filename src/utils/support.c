#include "../lib/build/include/support.h"
#include "../lib/build/include/bigint.h"
#include "utils.h"

void fatalError(char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

ObjRef newPrimObject(int dataSize) {
    ObjRef obj_ref = new_obj_ref(dataSize);
    obj_ref->size = dataSize;
    return obj_ref;
}
