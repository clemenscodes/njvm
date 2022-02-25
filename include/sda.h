#ifndef _STATIC_DATA_AREA_H
#define _STATIC_DATA_AREA_H

#include <stdint.h>
#include "stack.h"

extern size_t sda_size;

typedef struct sda {
    int *data;
    size_t size;
} StaticDataArea;

extern StaticDataArea sda;

void push_global(int n);
void pop_global(int n);
void initialize_sda(uint32_t variable_count);
void free_sda(void);
void print_sda(void);

#endif
