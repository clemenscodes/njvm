#ifndef _STACK_H
#define _STACK_H

#include <malloc.h>
#include <stdio.h>
#include <malloc.h>

#include "njvm.h"

void initialize_stack(void);
void push(Immediate immediate);
Immediate pop(void);
void free_stack(void);
void print_stack(void);

#endif
