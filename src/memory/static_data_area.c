#include "static_data_area.h"

uint32_t sda_size;
int* sda;

void initialize_sda(uint32_t variable_count) {
    sda_size = variable_count;
    sda = (int *)calloc(variable_count, sizeof(int));
    if (sda == NULL) {
        perror("malloc(sda)");
        exit(1);
    }
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
    for (int i = 0; i < sda_size; i++) {
        printf("%03u:\t[%d]\n", i, sda[i]);
    }
}