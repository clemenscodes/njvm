#include <stdint.h>
#include <stdio.h>

#include "stack.h"
#include "stdlib.h"

uint32_t size;
uint32_t* sda;

void initialize_sda(uint32_t variable_count) {
    size = variable_count;
    sda = (uint32_t*)calloc(variable_count, sizeof(uint32_t));
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

void print_sda(void) {
    for (int i = 0; i < size; i++) {
        printf("%03u:\t", i);
        if (sda == NULL) {
            printf("nil\n");
        } else {
            printf("[%d]\n", sda[i]);
        }
    }
}