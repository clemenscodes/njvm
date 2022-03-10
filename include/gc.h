#ifndef _GC_H
#define _GC_H

#include "njvm.h"
#include "utils.h"

void run_gc(void);
void copy_obj_ref(ObjRef obj_ref);
void collect_obj_ref_stats(ObjRef obj_ref);
void print_gc_stats(void);

#endif