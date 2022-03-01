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
        print_instruction(vm.ir.pc);
        printf("DEBUG: inspect, list, breakpoint, step, run, quit?\n");
        char *line = read_line();
        char c = line[0];
        if (c == '\n') {
            free(line);
            line = read_line();
        }
        switch (c) {
            case 'i':
                printf("DEBUG: [inspect]: stack, data?\n");
                line = read_line();
                c = line[0];
                switch (c) {
                    case 's':
                        free(line);
                        printf("-----------------------------\n");
                        print_stack();
                        printf("-----------------------------\n");
                        continue;
                    case 'd':
                        free(line);
                        printf("-----------------------------\n");
                        print_sda();
                        printf("-----------------------------\n");
                        continue;
                    default:
                        free(line);
                        continue;
                }
            case 'l':
                free(line);
                printf("-----------------------------\n");
                print_ir();
                printf("-----------------------------\n");
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
    if (vm.bp) 
        printf("DEBUG [breakpoint]: breakpoint is set at %d\n", *vm.bp);
    else
        printf("DEBUG [breakpoint]: cleared\n");
    printf("DEBUG [breakpoint]: address to set, -1 to clear, <ret> for no change?\n");
    int bp;
    if (!scanf("%i", &bp))
        fatal_error("Error: failed to read integer");
    if (bp < -1)
        return;
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
