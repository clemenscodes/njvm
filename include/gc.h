#ifndef _GC_H
#define _GC_H

#include <stdint.h>

#include "njvm.h"
#include "utils.h"

void nullify_heap_stats(void);
void swap_heaps(void);
void relocate_registers(void);
void relocate_stack_objects(void);
void relocate_sda_objects(void);
void collect_stats(size_t bytes);
void run_gc(void);
ObjRef copy_obj_ref(ObjRef obj_ref);
void print_gc_stats(void);

#endif