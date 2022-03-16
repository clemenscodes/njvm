#ifndef _HEAP_H
#define _HEAP_H

#include "njvm.h"

void initialize_heap(unsigned memory);
void *alloc(unsigned bytes);
void free_heap(void);
void print_heap_objects(void);
void print_heap_bytes(void);

#endif
