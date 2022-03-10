#ifndef _GC_H
#define _GC_H

#include "njvm.h"
#include "utils.h"

void run_gc(void);
void print_gc_stats(void);
void *copy_obj_ref(ObjRef obj_ref);

#endif