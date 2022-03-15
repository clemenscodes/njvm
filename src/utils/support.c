#include "utils.h"

void fatalError(char *msg) {
    fprintf(stderr, "%s\n", msg);
    abort();
    // exit(1);
}

ObjRef newPrimObject(int dataSize) {
    if (dataSize < 0) {
        fatalError("Error: no negative data size allowed");
    }
    ObjRef obj_ref = (ObjRef)alloc(dataSize + sizeof(Immediate));
    if (obj_ref == NULL) {
        fatalError("Error: failed to allocate memory for obj_ref");
    }
    obj_ref->size = dataSize;
    return obj_ref;
}
