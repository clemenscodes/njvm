#include "heap.h"

void initialize_heap() {
    vm.heap.data = malloc(vm.heap.memory * 1024);
    if (!vm.heap.data) perror("malloc(vm.heap.data)");
}
