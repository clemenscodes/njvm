#include "debugger.h"

void debug(char *bin) {
    read_file(bin);
    printf("DEBUG: file '%s' loaded (code size = %ld, data size = %ld)\n", bin, vm.ir.size, vm.sda.size);
    init();
    prompt();
}
void prompt(void) {
    while (1) {
        if (vm.ir.pc == vm.ir.size) {
            break;
        }
        print_next_instruction();
        printf("DEBUG: inspect, list, breakpoint, step, run, quit?\n");
        char *line = NULL;
        size_t len = 0;
        if (!getline(&line, &len, stdin)) {
            perror("(getline)");
            exit(1);
        }
        char c = line[0];
        switch (c) {
            case 'i':
                printf("inspect\n");
                if (!getline(&line, &len, stdin)) {
                    perror("(getline)");
                    exit(1);
                }
                c = line[0];
                switch (c) {
                    case 's':
                        free(line);
                        debug_stack();
                        continue;
                    case 'd':
                        free(line);
                        debug_sda();
                        continue;
                    default:
                        free(line);
                        continue;
                }
            case 'l':
                free(line);
                print_ir();
                continue;
            case 'b':
                free(line);
                set_breakpoint();
                continue;
            case 's':
                free(line);
                step();
                continue;
            case 'r':
                free(line);
                run();
                continue;
            case 'q':
                free(line);
                halt_instruction();
                exit(0);
                continue;
            default:
                free(line);
                continue;
        }
    }
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
