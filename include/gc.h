#ifndef _GC_H
#define _GC_H

#include <stdint.h>

#include "njvm.h"
#include "utils.h"

void swap_heaps(void);
void nullify_heap_stats(void);
void relocate_registers(void);
void relocate_stack_objects(void);
void relocate_sda_objects(void);
void collect_stats(ObjRef obj_ref, size_t bytes);
void run_gc(void);
ObjRef copy_obj_ref(ObjRef obj_ref);
void collect_obj_ref_stats(ObjRef obj_ref);
void print_gc_stats(void);

#endif