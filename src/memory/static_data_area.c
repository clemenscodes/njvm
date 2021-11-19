#include "stack.h"

int sda[MAXITEMS];

void push_global(int n) {
    push(sda[n]);
}

void pop_global(int n) {
    int global_var_value = pop();
    sda[n] = global_var_value;
}