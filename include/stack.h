#ifndef _STACK_H
#define _STACK_H

#include <malloc.h>
#include <stdio.h>

#include "../lib/build/include/bigint.h"
#include "njvm.h"

void initialize_stack(unsigned memory);
void push(Immediate immediate);
void push_obj_ref(ObjRef obj_ref);
Immediate pop(void);
ObjRef pop_obj_ref(void);
void free_stack(void);
void print_stack(void);

#endif
