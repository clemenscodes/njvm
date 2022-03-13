#ifndef _HEAP_H
#define _HEAP_H

#include "njvm.h"

void initialize_heap(unsigned int memory);
void *alloc(size_t size);
void free_heap(void);
void print_heap(void);

#endif
