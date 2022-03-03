#include "utils.h"

void fatalError(char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

ObjRef newPrimObject(int dataSize) {
    ObjRef obj_ref = malloc(dataSize + sizeof(Immediate));
    if (!obj_ref) fatalError("Error: failed to allocate memory for obj_ref");
    obj_ref->size = dataSize;
    return obj_ref;
}
