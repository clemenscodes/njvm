#ifndef _HEAP_H
#define _HEAP_H

#include "njvm.h"

void initialize_heap(unsigned memory);
ObjRef alloc(unsigned bytes);
void free_heap(void);
void purge_heap_half(void *half);
void print_heap_objects(void);
void print_heap_bytes(void);

#endif
