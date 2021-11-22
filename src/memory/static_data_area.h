#ifndef _STATIC_DATA_AREA_H
#define _STATIC_DATA_AREA_H

#include "stack.h"

extern int *sda;
extern int size;

void push_global(int n);
void pop_global(int n);
void initialize_sda(size_t variable_count);
void free_sda(void);
void print_sda(void);

#endif
