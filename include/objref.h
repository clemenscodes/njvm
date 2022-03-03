#ifndef _OBJREF_H
#define _OBJREF_H

typedef struct {
    uint32_t size;
    unsigned char data[1];
} *ObjRef;

#endif
