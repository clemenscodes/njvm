#include "utils.h"

void fatalError(char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

ObjRef newPrimObject(int dataSize) {
    if (dataSize < 1) {
        printf("Bad data size: %d\n", dataSize);
        fatalError("Error: at least 1 byte is required");
    }
    ObjRef obj_ref = alloc(dataSize + sizeof(Immediate));
    if (!obj_ref) {
        fatalError("Error: failed to allocate memory for obj_ref");
    }
    obj_ref->size = dataSize;
    return obj_ref;
}
