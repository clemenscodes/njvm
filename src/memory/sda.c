#include "sda.h"

StaticDataArea sda;

void initialize_sda(uint32_t variable_count) {
    sda.size = variable_count;
    sda.data = (int *)calloc(sda.size, sizeof(int));
    if (!sda.data) {
        perror("malloc(sda)");
        exit(1);
    }
}

void push_global(int n) {
    push(sda.data[n]);
}

void pop_global(int n) {
    sda.data[n] = pop();
}

void free_sda(void) {
    free(sda.data);
}

void print_sda(void) {
    for (int i = 0; i < sda.size; i++) {
        printf("%03u:\t[%d]\n", i, sda.data[i]);
    }
}