#include "processor.h"

void init(void) {
    printf("Ninja Virtual Machine started\n");
    initialize_stack();
}

void execute(char *arg) {
    read_file(arg);
    init();
    work();
}

void work(void) {
    while (1) {
        Bytecode instruction = vm.ir.data[vm.ir.pc];
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
    free_stack();
    if (vm.bp) free(vm.bp);
    printf("Ninja Virtual Machine stopped\n");
    exit(0);
}

void pushc_instruction(Immediate immediate) {
    ObjRef obj_ref = new_obj_ref(sizeof(Immediate));
    *(Immediate *)obj_ref->data = immediate;
    push_obj_ref(obj_ref);
}

void add_instruction(void) {
    ObjRef b = pop_obj_ref();
    ObjRef a = pop_obj_ref();
    ObjRef c = new_obj_ref(sizeof(Immediate));
    *(Immediate *)c->data = *(Immediate *)a->data + *(Immediate *)b->data;
    push_obj_ref(c);
}

void sub_instruction(void) {
    ObjRef b = pop_obj_ref();
    ObjRef a = pop_obj_ref();
    ObjRef c = new_obj_ref(sizeof(Immediate));
    *(Immediate *)c->data = *(Immediate *)a->data - *(Immediate *)b->data;
    push_obj_ref(c);
}

void mul_instruction(void) {
    ObjRef b = pop_obj_ref();
    ObjRef a = pop_obj_ref();
    ObjRef c = new_obj_ref(sizeof(Immediate));
    *(Immediate *)c->data = *(Immediate *)a->data * *(Immediate *)b->data;
    push_obj_ref(c);
}

void div_instruction(void) {
    ObjRef b = pop_obj_ref();
    ObjRef a = pop_obj_ref();
    ObjRef c = new_obj_ref(sizeof(Immediate));
    if (!*(Immediate *)b->data) fatal_error("Error: Division by zero");
    *(Immediate *)c->data = *(Immediate *)a->data / *(Immediate *)b->data;
    push_obj_ref(c);
}

void mod_instruction(void) {
    ObjRef b = pop_obj_ref();
    ObjRef a = pop_obj_ref();
    ObjRef c = new_obj_ref(sizeof(Immediate));
    if (!*(Immediate *)b->data) fatal_error("Error: Division by zero");
    *(Immediate *)c->data = *(Immediate *)a->data % *(Immediate *)b->data;
    push_obj_ref(c);
}

void rdint_instruction(void) {
    int read_integer;
    if (!scanf("%d", &read_integer)) fatal_error("Error: failed to read integer");
    ObjRef c = new_obj_ref(sizeof(Immediate));
    *(Immediate *)c->data = read_integer;
    push_obj_ref(c);
}

void wrint_instruction(void) {
    printf("%d", *(Immediate *)pop_obj_ref()->data);
}

void rdchr_instruction(void) {
    char read_character;
    if (!scanf("%c", &read_character)) fatal_error("Error: failed to read character");
    ObjRef c = new_obj_ref(sizeof(unsigned char));
    *(char *)c->data = read_character;
    push_obj_ref(c);
}

void wrchr_instruction(void) {
    printf("%c", *pop_obj_ref()->data);
}

void pushg_instruction(Immediate immediate) {
    push_global(immediate);
}

void popg_instruction(Immediate immediate) {
    pop_global(immediate);
}

void asf_instruction(Immediate immediate) {
    if ((vm.stack.size + immediate) >= MAX_ITEMS) fatal_error("Error: stack overflow");
    if (immediate < 0) fatal_error("Error: negative immediate for asf");
    push(vm.stack.fp);
    vm.stack.fp = vm.stack.sp;
    vm.stack.size += immediate;
    vm.stack.sp += immediate;
    for (int i = vm.stack.fp; i < vm.stack.sp; i++) {
        vm.stack.data[i].is_obj_ref = true;
        vm.stack.data[i].u.obj_ref = NULL;
    }
}

void rsf_instruction(void) {
    vm.stack.size -= (vm.stack.sp - vm.stack.fp);
    vm.stack.sp = vm.stack.fp;
    vm.stack.fp = pop();
}

void pushl_instruction(Immediate immediate) {
    push_obj_ref(vm.stack.data[vm.stack.fp + immediate].u.obj_ref);
}

void popl_instruction(Immediate immediate) {
    vm.stack.data[vm.stack.fp + immediate].u.obj_ref = pop_obj_ref();
}

void eq_instruction(void) {
    ObjRef b = pop_obj_ref();
    ObjRef a = pop_obj_ref();
    ObjRef c = new_obj_ref(sizeof(Immediate));
    *(Immediate *)c->data = *(Immediate *)a->data == *(Immediate *)b->data ? 1 : 0;
    push_obj_ref(c);
}

void ne_instruction(void) {
    ObjRef b = pop_obj_ref();
    ObjRef a = pop_obj_ref();
    ObjRef c = new_obj_ref(sizeof(Immediate));
    *(Immediate *)c->data = *(Immediate *)a->data != *(Immediate *)b->data ? 1 : 0;
    push_obj_ref(c);
}

void lt_instruction(void) {
    ObjRef b = pop_obj_ref();
    ObjRef a = pop_obj_ref();
    ObjRef c = new_obj_ref(sizeof(Immediate));
    *(Immediate *)c->data = *(Immediate *)a->data < *(Immediate *)b->data ? 1 : 0;
    push_obj_ref(c);
}

void le_instruction(void) {
    ObjRef b = pop_obj_ref();
    ObjRef a = pop_obj_ref();
    ObjRef c = new_obj_ref(sizeof(Immediate));
    *(Immediate *)c->data = *(Immediate *)a->data <= *(Immediate *)b->data ? 1 : 0;
    push_obj_ref(c);
}

void gt_instruction(void) {
    ObjRef b = pop_obj_ref();
    ObjRef a = pop_obj_ref();
    ObjRef c = new_obj_ref(sizeof(Immediate));
    *(Immediate *)c->data = *(Immediate *)a->data > *(Immediate *)b->data ? 1 : 0;
    push_obj_ref(c);
}

void ge_instruction(void) {
    ObjRef b = pop_obj_ref();
    ObjRef a = pop_obj_ref();
    ObjRef c = new_obj_ref(sizeof(Immediate));
    *(Immediate *)c->data = *(Immediate *)a->data >= *(Immediate *)b->data ? 1 : 0;
    push_obj_ref(c);
}

void jump_instruction(Immediate immediate) {
    vm.ir.pc = immediate;
}

void brf_instruction(Immediate immediate) {
    if (!*(Immediate *)pop_obj_ref()->data) jump_instruction(immediate);
}

void brt_instruction(Immediate immediate) {
    if (*(Immediate *)pop_obj_ref()->data == 1) jump_instruction(immediate);
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
    for (i = 0; i < immediate; i++) pop_obj_ref();
}

void pushr_instruction(void) {
    if (vm.rv) {
        push_obj_ref(vm.rv);
        free(vm.rv);
    } else
        fatal_error("Error: no value in return value register");
}

void popr_instruction(void) {
    vm.rv = pop_obj_ref();
}

void dup_instruction(void) {
    ObjRef obj_ref = pop_obj_ref();
    push_obj_ref(obj_ref);
    push_obj_ref(obj_ref);
}
