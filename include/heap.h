#ifndef _HEAP_H
#define _HEAP_H

#include "njvm.h"

void initialize_heap(void);
void *alloc(unsigned int bytes);
void free_heap(void);

#endif
