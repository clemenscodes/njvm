#ifndef _GC_H
#define _GC_H

#include "njvm.h"
#include "utils.h"

void nullify_heap_stats(void);
void swap_heaps(void);
void relocate_registers(void);
void relocate_stack_objects(void);
void relocate_sda_objects(void);
ObjRef relocate(ObjRef obj_ref);
ObjRef copy_obj_ref_to_free_memory(ObjRef obj_ref);
void collect_stats(unsigned bytes);
void print_gc_stats(void);
void purge_heap(void);
void scan(void);
void run_gc(void);

#endif