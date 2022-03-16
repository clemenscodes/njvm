#include "utils.h"

void fatalError(char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(1);
}

ObjRef newPrimObject(int dataSize) {
    if (dataSize < 4) {
        fatalError("at least 4 bytes for primitive object are required");
    }
    ObjRef obj_ref = alloc(dataSize + sizeof(Immediate));
    if (!obj_ref) {
        fatalError("failed to allocate memory for primitive object");
    }
    obj_ref->size = dataSize;
    return obj_ref;
}
