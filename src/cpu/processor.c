#include "processor.h"

int a, b;
char c;

void init(void) {
    printf("Ninja Virtual Machine started\n");
}

void execute(char *arg) {
    read_file(arg);
    init();
    work();
}

void work(void) {
    Bytecode instruction = vm.ir.data[vm.ir.pc];
    Opcode opcode = decode_instruction(instruction).opcode;
    while (opcode != HALT) {
        instruction = vm.ir.data[vm.ir.pc];
        opcode = decode_instruction(instruction).opcode;
        vm.ir.pc++;
        execute_instruction(instruction);
    }
}

void execute_instruction(Bytecode bytecode) {
    Instruction instruction = decode_instruction(bytecode);
    Opcode opcode = instruction.opcode;
    Immediate immediate = instruction.immediate;
    switch (opcode) {
        case halt:
            halt_instruction();
        case pushc:
            pushc_instruction(immediate);
            break;
        case add:
            add_instruction();
            break;
        case sub:
            sub_instruction();
            break;
        case mul:
            mul_instruction();
            break;
        case divide:
            div_instruction();
            break;
        case mod:
            mod_instruction();
            break;
        case rdint:
            rdint_instruction();
            break;
        case wrint:
            wrint_instruction();
            break;
        case rdchr:
            rdchr_instruction();
            break;
        case wrchr:
            wrchr_instruction();
            break;
        case pushg:
            pushg_instruction(immediate);
            break;
        case popg:
            popg_instruction(immediate);
            break;
        case asf:
            asf_instruction(immediate);
            break;
        case rsf:
            rsf_instruction();
            break;
        case pushl:
            pushl_instruction(immediate);
            break;
        case popl:
            popl_instruction(immediate);
            break;
        case eq:
            eq_instruction();
            break;
        case ne:
            ne_instruction();
            break;
        case lt:
            lt_instruction();
            break;
        case le:
            le_instruction();
            break;
        case gt:
            gt_instruction();
            break;
        case ge:
            ge_instruction();
            break;
        case jump:
            jump_instruction(immediate);
            break;
        case brf:
            brf_instruction(immediate);
            break;
        case brt:
            brt_instruction(immediate);
            break;
        case call:
            call_instruction(immediate);
            break;
        case ret:
            ret_instruction();
            break;
        case drop:
            drop_instruction(immediate);
            break;
        case pushr:
            pushr_instruction();
            break;
        case popr:
            popr_instruction();
            break;
        case dup:
            dup_instruction();
            break;
        default:
            fprintf(stderr, "Unknown opcode %d\n", opcode);
            halt_instruction();
    }
}

void halt_instruction(void) {
    free_sda();
    free_ir();
    if (vm.bp) free(vm.bp);
    printf("Ninja Virtual Machine stopped\n");
}

void pushc_instruction(Immediate immediate) {
    push(immediate);
}

void add_instruction(void) {
    b = pop();
    a = pop();
    push(a + b);
}

void sub_instruction(void) {
    b = pop();
    a = pop();
    push(a - b);
}

void mul_instruction(void) {
    b = pop();
    a = pop();
    push(a * b);
}

void div_instruction(void) {
    b = pop();
    a = pop();
    if (!b) fatal_error("Error: Division by zero");
    push(a / b);
}

void mod_instruction(void) {
    b = pop();
    a = pop();
    if (!b) fatal_error("Error: Division by zero");
    push(a % b);
}

void wrchr_instruction(void) {
    c = pop();
    printf("%c", c);
}

void rdchr_instruction(void) {
    if (!scanf("%c", &c)) fatal_error("Error: failed to read character");
    push(c);
}

void rdint_instruction(void) {
    if (!scanf("%d", &b)) fatal_error("Error: failed to read integer");
    push(b);
}

void wrint_instruction(void) {
    printf("%d", pop());
}

void pushg_instruction(Immediate immediate) {
    push_global(immediate);
}

void popg_instruction(Immediate immediate) {
    pop_global(immediate);
}

void asf_instruction(Immediate immediate) {
    push(vm.stack.fp);
    vm.stack.fp = vm.stack.sp;
    vm.stack.size += immediate;
    vm.stack.data = realloc(vm.stack.data, (vm.stack.size) * sizeof(int));
    if (!vm.stack.data) perror("realloc(vm.stack.data)");
    vm.stack.sp += immediate;
    for (int i = vm.stack.fp; i < vm.stack.sp; i++) vm.stack.data[i] = 0;
}

void rsf_instruction(void) {
    vm.stack.size -= (vm.stack.sp - vm.stack.fp);
    vm.stack.data = realloc(vm.stack.data, (vm.stack.size) * sizeof(int));
    if (!vm.stack.data) perror("realloc(vm.stack.data)");
    vm.stack.sp = vm.stack.fp;
    vm.stack.fp = pop();
}

void pushl_instruction(Immediate immediate) {
    push(vm.stack.data[vm.stack.fp + immediate]);
}

void popl_instruction(Immediate immediate) {
    vm.stack.data[vm.stack.fp + immediate] = vm.stack.data[vm.stack.sp - 1];
}

void eq_instruction(void) {
    b = pop();
    a = pop();
    a == b ? push(1) : push(0);
}

void ne_instruction(void) {
    b = pop();
    a = pop();
    a != b ? push(1) : push(0);
}

void lt_instruction(void) {
    b = pop();
    a = pop();
    a < b ? push(1) : push(0);
}

void le_instruction(void) {
    b = pop();
    a = pop();
    a <= b ? push(1) : push(0);
}

void gt_instruction(void) {
    b = pop();
    a = pop();
    a > b ? push(1) : push(0);
}

void ge_instruction(void) {
    b = pop();
    a = pop();
    a >= b ? push(1) : push(0);
}

void jump_instruction(Immediate immediate) {
    vm.ir.pc = immediate;
}

void brf_instruction(Immediate immediate) {
    if (!pop()) jump_instruction(immediate);
}

void brt_instruction(Immediate immediate) {
    if (pop() == 1) jump_instruction(immediate);
}

void call_instruction(Immediate immediate) {
    push(vm.ir.pc);
    vm.ir.pc = immediate;
}

void ret_instruction(void) {
    vm.ir.pc = pop();
}

void drop_instruction(Immediate immediate) {
    int i;
    for (i = 0; i < immediate; i++) pop();
}

void pushr_instruction(void) {
    if (vm.rv) {
        push(*vm.rv);
        free(vm.rv);
    } else fatal_error("Error: no value in return value register");
}

void popr_instruction(void) {
    vm.rv = malloc(sizeof(int));
    if (!vm.rv) perror("malloc(vm.rv)");
    *vm.rv = pop();
}

void dup_instruction(void) {
    Immediate immediate = pop();
    push(immediate);
    push(immediate);
}
