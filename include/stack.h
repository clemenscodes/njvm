#ifndef _STACK_H
#define _STACK_H

#include <malloc.h>
#include <stdio.h>
#include <malloc.h>

#include "njvm.h"
#include "objref.h"


void initialize_stack(uint32_t bytes);
void push(Immediate immediate);
void push_obj_ref(ObjRef obj_ref);
Immediate pop(void);
ObjRef pop_obj_ref(void);
void free_stack(void);
void print_stack(void);

#endif
