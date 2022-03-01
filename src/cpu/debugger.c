#include "debugger.h"

void debug(char *bin) {
    read_file(bin);
    printf("DEBUG: file '%s' loaded (code size = %ld, data size = %ld)\n", bin, vm.ir.size, vm.sda.size);
    init();
    prompt();
    exit(0);
}

void prompt(void) {
    while (vm.ir.pc != vm.ir.size) {
        print_next_instruction();
        printf("DEBUG: inspect, list, breakpoint, step, run, quit?\n");
        char *line = read_line();
        char c = line[0];
        if (c == '\n') {
            free(line);
            line = read_line();
        }
        switch (c) {
            case 'i':
                printf("inspect\n");
                line = read_line();
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
                debug_ir();
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
    uint32_t instruction = vm.ir.data[vm.ir.pc];
    vm.ir.pc++;
    execute_instruction(instruction);
}

void run(void) {
    while (vm.ir.pc != vm.ir.size) {
        if (vm.bp) {
            if (*vm.bp == vm.ir.pc) {
                vm.bp = NULL;
                free(vm.bp);
                printf("DEBUG [breakpoint]: cleared\n");
                prompt();
                break;
            }
        }
        step();
    }
}

void set_breakpoint(void) {
    if (vm.bp) {
        printf("DEBUG [breakpoint]: breakpoint is set at %d\n", *vm.bp);
    } else {
        printf("DEBUG [breakpoint]: cleared\n");
    }
    printf("DEBUG [breakpoint]: address to set, -1 to clear, <ret> for no change?\n");
    int bp;
    if (!scanf("%i", &bp)) {
        printf("Error: failed to read integer");
        exit(1);
    }
    if (bp < -1) {
        return;
    }
    if (bp == -1) {
        vm.bp = NULL;
        free(vm.bp);
        printf("DEBUG [breakpoint]: now cleared\n");
        return;
    }
    vm.bp = malloc(sizeof(int));
    *vm.bp = bp;
    printf("DEBUG [breakpoint]: now set at %d\n", *vm.bp);
}

void print_next_instruction(void) {
    printf("print_next_instruction\n");
}

void debug_stack(void) {
    printf("-----------------------------\n");
    print_stack();
    printf("-----------------------------\n");
}

void debug_sda(void) {
    printf("-----------------------------\n");
    print_sda();
    printf("-----------------------------\n");
}

void debug_ir(void) {
    printf("-----------------------------\n");
    print_ir();
    printf("-----------------------------\n");
}
