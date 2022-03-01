#ifndef _SDA_H
#define _SDA_H

#include <stdint.h>

#include "njvm.h"
#include "stack.h"

void initialize_sda(uint32_t variable_count);
void push_global(int n);
void pop_global(int n);
void free_sda(void);
void print_sda(void);

#endif
