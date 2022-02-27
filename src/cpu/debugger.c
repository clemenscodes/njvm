#include "debugger.h"

void debug(char *bin) {
    read_file(bin);
    printf("DEBUG: file '%s' loaded (code size = %ld, data size = %ld)\n", bin, vm.ir.size, vm.sda.size);
    exit(0);
}
void prompt(void) {
    printf("prompt\n");
}
void inspect(void) {
    printf("inspect\n");
}
void step(void) {
    printf("step\n");
}
void run(void) {
    printf("run\n");
}
void set_breakpoint(void) {
    printf("set_breakpoint\n");
}
void print_next_instruction(void) {
    printf("print_next_instruction\n");
}
void debug_stack(void) {
    printf("print_stack\n");
}
void debug_sda(void) {
    printf("print_sda\n");
}
void debug_ir(void) {
    printf("print_ir\n");
}
