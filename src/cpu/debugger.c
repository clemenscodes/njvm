#include "debugger.h"

void debug(char *bin) {
    printf("DEBUG:\tfile\t:  '%s'\n", bin);
    printf("\tcode\t:  %ld instructions\n", vm.ir.size);
    printf("\tdata\t:  %ld objects\n", vm.sda.size);
    printf("\tstack\t:  %ld slots\n", vm.stack.max_items);
    printf("\theap\t:  2 * %ld bytes\n", vm.heap.available);
    printf("Ninja Virtual Machine started\n");
    prompt();
}

void prompt(void) {
    Opcode opcode = decode_instruction(vm.ir.data[vm.ir.pc]).opcode;
    while (opcode != halt) {
        print_instruction(vm.ir.pc);
        printf("DEBUG: inspect, list, breakpoint, step, run, quit?\n");
        char *line = read_line();
        char c = line[0];
        if (c == '\n' || c == '\0') {
            line = read_line();
            c = line[0];
        }
        switch (c) {
            case 'i': {
                printf("DEBUG: [inspect]: stack, data, object?\n");
                line = read_line();
                c = line[0];
                switch (c) {
                    case 's': {
                        free(line);
                        print_stack();
                        printf("---------------- end of stack ----------------\n");
                        continue;
                    }
                    case 'd': {
                        free(line);
                        print_sda();
                        printf("----------------- end of sda -----------------\n");
                        continue;
                    }
                    case 'o': {
                        printf("object reference?\n");
                        line = read_line();
                        ObjRef obj_ref = (ObjRef)strtol(line, (char **)NULL, 16);
                        print_obj_ref(obj_ref);
                        free(line);
                        continue;
                    }
                    default:
                        free(line);
                        continue;
                }
            }
            case 'l': {
                free(line);
                print_ir();
                printf("---------------- end of instructions ----------------\n");
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
                opcode = halt;
                continue;
            }
            case 'q': {
                free(line);
                halt_instruction();
                opcode = halt;
                continue;
            }
            default: {
                free(line);
                continue;
            }
        }
    }
}

void step(void) {
    Bytecode instruction = vm.ir.data[vm.ir.pc];
    vm.ir.pc++;
    execute_instruction(instruction);
}

void run(void) {
    Opcode opcode = decode_instruction(vm.ir.data[vm.ir.pc]).opcode;
    while (opcode != halt) {
        if (vm.bp) {
            if (*vm.bp == vm.ir.pc) {
                vm.bp = NULL;
                printf("DEBUG [breakpoint]: cleared\n");
                prompt();
                break;
            }
        }
        Bytecode instruction = vm.ir.data[vm.ir.pc];
        opcode = decode_instruction(instruction).opcode;
        vm.ir.pc++;
        execute_instruction(instruction);
    }
}

void set_breakpoint(void) {
    if (vm.bp) {
        printf("DEBUG [breakpoint]: breakpoint is set at %d\n", *vm.bp);
    } else {
        printf("DEBUG [breakpoint]: cleared\n");
    }
    printf("DEBUG [breakpoint]: address to set, -1 to clear, <ret> for no change?\n");
    bigRead(stdin);
    bip.op1 = bip.res;
    int bp = bigToInt();
    if (!bp) {
        fatalError("Error: failed to read integer");
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
    vm.bp = alloc(sizeof(int));
    if (!vm.bp) {
        perror("(malloc)");
    }
    *vm.bp = bp;
    printf("DEBUG [breakpoint]: now set at %d\n", *vm.bp);
}

void print_obj_ref(ObjRef obj_ref) {
    if (!obj_ref) {
        return;
    }
    printf("ObjRef: %p\n", (void *)obj_ref);
    char *type;
    unsigned int bytes = get_obj_ref_bytes(obj_ref);
    if (IS_PRIMITIVE(obj_ref)) {
        type = "PRIMITIVE\0";
        printf("Type: %s\n", type);
        printf("Bytes: %u\n", bytes);
        printf("Value: [");
        bip.op1 = obj_ref;
        bigPrint(stdout);
        printf("]\n");
    } else {
        type = "COMPOUND\0";
        unsigned int fields = GET_ELEMENT_COUNT(obj_ref);
        printf("Type: %s\n", type);
        printf("Bytes: %u\n", bytes);
        printf("Fields: %u\n", fields);
        for (int i = 0; i < fields; i++) {
            printf("[%u] = %p\n", i, (void *)GET_REFS_PTR(obj_ref)[i]);
        }
    }
    printf("---------------- end of object ----------------\n");
}

void print_memory_in_be_bytes(void *ptr, int bytes) {
    unsigned char *address = ptr;
    for (int i = 0; i < bytes; i++) {
        printf("%02hhX ", address[i]);
    }
    printf("\n");
}

void print_memory_in_le_bits(void *ptr, int bytes) {
    unsigned char *address = ptr;
    int bits = bytes * 8;
    for (int i = bits - 1; i >= 0; i--) {
        if ((i % 8 == 7) && (i <= bits - 2)) {
            printf(" ");
        }
        printf("%d", *address >> i & 1);
    }
    printf("\n");
}

void print_memory_in_be_bits(void *ptr, int bytes) {
    unsigned char *address = ptr;
    int bits = bytes * 8;
    for (int i = 0; i < bits; i++) {
        if ((i % 8 == 0) && (i != 0)) {
            printf(" ");
        }
        printf("%d", *address >> i & 1);
    }
    printf("\n");
}

void print_obj_ref_in_be_bytes(ObjRef obj_ref) {
    size_t bytes = get_obj_ref_bytes(obj_ref);
    print_memory_in_be_bytes(obj_ref, bytes);
}

void print_obj_ref_in_be_bits(ObjRef obj_ref) {
    size_t bytes = get_obj_ref_bytes(obj_ref);
    print_memory_in_be_bits(obj_ref, bytes);
}

void print_obj_ref_in_le_bits(ObjRef obj_ref) {
    size_t bytes = get_obj_ref_bytes(obj_ref);
    print_memory_in_le_bits(obj_ref, bytes);
}
