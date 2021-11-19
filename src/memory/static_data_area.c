#include <stdint.h>
#include "stack.h"

uint32_t sda[MAXITEMS];

void push_global(int n) {
    push(sda[n]);
}

void pop_global(int n) {
    int global_var_value = pop();
    sda[n] = global_var_value;
}