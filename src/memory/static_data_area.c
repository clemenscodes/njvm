#include <stdint.h>
#include "stack.h"
#include <stdio.h>
#include "stdlib.h"

uint32_t size;
uint32_t* sda;

void initialize_sda(uint32_t variable_count) {
    size = variable_count;
    sda = (uint32_t *)calloc(variable_count, sizeof(uint32_t));
}

void push_global(int n) {
    push(sda[n]);
}

void pop_global(int n) {
    sda[n] = pop();
}

void free_sda(void) {
    free(sda);
}