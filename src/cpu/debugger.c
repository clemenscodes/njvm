#include "debugger.h"

void debug(char *bin) {
    read_file(bin);
    printf("DEBUG: file '%s' loaded (code size = %ld, data size = %ld)\n", bin, vm.ir.size, vm.sda.size);
    init();
    prompt();
}

void prompt(void) {
    while (1) {
        print_instruction(vm.ir.pc);
        printf("DEBUG: inspect, list, breakpoint, step, run, quit?\n");
        char *line = read_line();
        char c = line[0];
        if (c == '\n' || c == '\0') {
            line = read_line();
            c = line[0];
        }
        switch (c) {
            case 'i':
                printf("DEBUG: [inspect]: stack, data, object?\n");
                line = read_line();
                c = line[0];
                switch (c) {
                    case 's': {
                        free(line);
                        printf("---------------------------------------\n");
                        print_stack();
                        printf("---------------------------------------\n");
                        continue;
                    }
                    case 'd': {
                        free(line);
                        printf("---------------------------------------\n");
                        print_sda();
                        printf("---------------------------------------\n");
                        continue;
                    }
                    case 'o': {
                        printf("object reference?\n");
                        line = read_line();
                        printf("---------------------------------------\n");
                        print_obj_ref(line);
                        printf("---------------------------------------\n");
                        free(line);
                        continue;
                    }
                    default:
                        free(line);
                        continue;
                }
            case 'l': {
                free(line);
                printf("---------------------------------------\n");
                print_ir();
                printf("---------------------------------------\n");
                continue;
            }
            case 'b': {
                free(line);
                set_breakpoint();
                continue;
            }
            case 's': {
                free(line);
                step();
                continue;
            }
            case 'r': {
                free(line);
                run();
                continue;
            }
            case 'q': {
                free(line);
                halt_instruction();
            }
            default: {
                free(line);
                continue;
            }
        }
    }
}

void step(void) {
    uint32_t instruction = vm.ir.data[vm.ir.pc];
    vm.ir.pc++;
    execute_instruction(instruction);
}

void run(void) {
    while (1) {
        if (vm.bp)
            if (*vm.bp == vm.ir.pc) {
                vm.bp = NULL;
                free(vm.bp);
                printf("DEBUG [breakpoint]: cleared\n");
                prompt();
                break;
            }
        step();
    }
}

void set_breakpoint(void) {
    int bp;
    if (vm.bp)
        printf("DEBUG [breakpoint]: breakpoint is set at %d\n", *vm.bp);
    else
        printf("DEBUG [breakpoint]: cleared\n");
    printf("DEBUG [breakpoint]: address to set, -1 to clear, <ret> for no change?\n");
    bigRead(stdin);
    bip.op1 = bip.res;
    bp = bigToInt();
    if (!bp) fatalError("Error: failed to read integer");
    if (bp < -1) return;
    if (bp == -1) {
        vm.bp = NULL;
        free(vm.bp);
        printf("DEBUG [breakpoint]: now cleared\n");
        return;
    }
    vm.bp = malloc(sizeof(int));
    if (!vm.bp) perror("(malloc)");
    *vm.bp = bp;
    printf("DEBUG [breakpoint]: now set at %d\n", *vm.bp);
}
