#ifndef _STATIC_DATA_AREA_H
#define _STATIC_DATA_AREA_H

#include <stdint.h>
#include "stack.h"

extern int *sda;
extern int size;

typedef struct sda {
    int *data;
} StaticDataArea;

void push_global(int n);
void pop_global(int n);
void initialize_sda(uint32_t variable_count);
void free_sda(void);
void print_sda(void);

#endif
