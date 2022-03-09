#ifndef _HEAP_H
#define _HEAP_H

#include "njvm.h"

void initialize_heap(void);
ObjRef alloc(unsigned int bytes);

#endif
