#include "heap.h"

void initialize_heap() {
    unsigned int bytes = vm.heap.memory * 1024;
    vm.heap.data = malloc(bytes);
    if (!vm.heap.data) {
        perror("malloc(vm.heap.data)");
    }
}
