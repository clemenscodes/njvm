#ifndef _STACK_H
#define _STACK_H

#include <stdio.h>
#include <stdlib.h>

#include "njvm.h"

void initialize_stack(void);
void push(Immediate immediate);
Immediate pop(void);
void free_stack(void);
void print_stack(void);

#endif
