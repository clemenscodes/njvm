#include "processor.h"

void init(void) {
    printf("Ninja Virtual Machine started\n");
    initialize_stack();
    vm.rv = NULL;
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
        case new:
            new_instruction(immediate);
            break;
        case getf:
            getf_instruction(immediate);
            break;
        case putf:
            putf_instruction(immediate);
            break;
        case newa:
            newa_instruction();
            break;
        case getfa:
            getfa_instruction();
            break;
        case putfa:
            putfa_instruction();
            break;
        case getsz:
            getsz_instruction();
            break;
        case pushn:
            pushn_instruction();
            break;
        case refeq:
            refeq_instruction();
            break;
        case refne:
            refne_instruction();
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
    bigFromInt(immediate);
    push_obj_ref(bip.res);
}

void add_instruction(void) {
    bip.op1 = pop_obj_ref();
    bip.op2 = pop_obj_ref();
    bigAdd();
    push_obj_ref(bip.res);
}

void sub_instruction(void) {
    bip.op2 = pop_obj_ref();
    bip.op1 = pop_obj_ref();
    bigSub();
    push_obj_ref(bip.res);
}

void mul_instruction(void) {
    bip.op1 = pop_obj_ref();
    bip.op2 = pop_obj_ref();
    bigMul();
    push_obj_ref(bip.res);
}

void div_instruction(void) {
    bip.op2 = pop_obj_ref();
    bip.op1 = pop_obj_ref();
    bigDiv();
    push_obj_ref(bip.res);
}

void mod_instruction(void) {
    bip.op2 = pop_obj_ref();
    bip.op1 = pop_obj_ref();
    bigDiv();
    push_obj_ref(bip.rem);
}

void rdint_instruction(void) {
    bigRead(stdin);
    push_obj_ref(bip.res);
}

void wrint_instruction(void) {
    bip.op1 = pop_obj_ref();
    bigPrint(stdout);
}

void rdchr_instruction(void) {
    char read_character;
    if (!scanf("%c", &read_character)) fatalError("Error: failed to read character");
    bigFromInt((int)read_character);
    push_obj_ref(bip.res);
}

void wrchr_instruction(void) {
    bip.op1 = pop_obj_ref();
    printf("%c", (char)bigToInt());
}

void pushg_instruction(Immediate immediate) {
    push_global(immediate);
}

void popg_instruction(Immediate immediate) {
    pop_global(immediate);
}

void asf_instruction(Immediate immediate) {
    if ((vm.stack.size + immediate) >= MAX_ITEMS) fatalError("Error: stack overflow");
    if (immediate < 0) fatalError("Error: negative immediate for asf");
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
    bip.op2 = pop_obj_ref();
    bip.op1 = pop_obj_ref();
    bigFromInt(bigCmp() == 0 ? 1 : 0);
    push_obj_ref(bip.res);
}

void ne_instruction(void) {
    bip.op2 = pop_obj_ref();
    bip.op1 = pop_obj_ref();
    bigFromInt(bigCmp() != 0 ? 1 : 0);
    push_obj_ref(bip.res);
}

void lt_instruction(void) {
    bip.op2 = pop_obj_ref();
    bip.op1 = pop_obj_ref();
    bigFromInt(bigCmp() < 0 ? 1 : 0);
    push_obj_ref(bip.res);
}

void le_instruction(void) {
    bip.op2 = pop_obj_ref();
    bip.op1 = pop_obj_ref();
    bigFromInt(bigCmp() <= 0 ? 1 : 0);
    push_obj_ref(bip.res);
}

void gt_instruction(void) {
    bip.op2 = pop_obj_ref();
    bip.op1 = pop_obj_ref();
    bigFromInt(bigCmp() > 0 ? 1 : 0);
    push_obj_ref(bip.res);
}

void ge_instruction(void) {
    bip.op2 = pop_obj_ref();
    bip.op1 = pop_obj_ref();
    bigFromInt(bigCmp() >= 0 ? 1 : 0);
    push_obj_ref(bip.res);
}

void jump_instruction(Immediate immediate) {
    vm.ir.pc = immediate;
}

void brf_instruction(Immediate immediate) {
    bip.op1 = pop_obj_ref();
    if (!bigToInt()) jump_instruction(immediate);
}

void brt_instruction(Immediate immediate) {
    bip.op1 = pop_obj_ref();
    if (bigToInt() == 1) jump_instruction(immediate);
}

void call_instruction(Immediate immediate) {
    push(vm.ir.pc);
    vm.ir.pc = immediate;
}

void ret_instruction(void) {
    vm.ir.pc = pop();
}

void drop_instruction(Immediate immediate) {
    for (int i = 0; i < immediate; i++) pop_obj_ref();
}

void pushr_instruction(void) {
    if (vm.rv)
        push_obj_ref(vm.rv);
    else
        fatalError("Error: no value in return value register");
}

void popr_instruction(void) {
    vm.rv = pop_obj_ref();
}

void dup_instruction(void) {
    bip.op1 = pop_obj_ref();
    push_obj_ref(bip.op1);
    push_obj_ref(bip.op1);
}

void new_instruction(Immediate immediate) {
    bip.op1 = new_composite_object(immediate);
    push_obj_ref(bip.op1);
}

void getf_instruction(Immediate immediate) {
    bip.op1 = pop_obj_ref();
    bip.op2 = GET_REFS_PTR(bip.op1)[immediate];
    unsigned int size = GET_ELEMENT_COUNT(bip.op1);
    if (!((0 <= immediate) && (immediate < size))) fatalError("Error: index out of bound");
    push_obj_ref(bip.op2);
}

void putf_instruction(Immediate immediate) {
    bip.op1 = pop_obj_ref();
    bip.op2 = GET_REFS_PTR(bip.op1)[immediate];
    unsigned int size = GET_ELEMENT_COUNT(bip.op1);
    if (!((0 <= immediate) && (immediate < size))) fatalError("Error: index out of bound");
    GET_REFS_PTR(bip.op2)[immediate] = bip.op1;
}

void newa_instruction(void) {
    bip.op1 = pop_obj_ref();
    bip.op1 = new_composite_object(bigToInt());
    push_obj_ref(bip.op1);
}

void getfa_instruction(void) {
    bip.op1 = pop_obj_ref();
    Immediate index = bigToInt();
    bip.op1 = pop_obj_ref();
    unsigned int size = GET_ELEMENT_COUNT(bip.op1);
    if (!((0 <= index ) && (index < size))) fatalError("Error: index out of bound");
    bip.op2 = GET_REFS_PTR(bip.op1)[index];
    push_obj_ref(bip.op2);
}

void putfa_instruction(void) {
    bip.op2 = pop_obj_ref(); // value
    bip.op1 = pop_obj_ref();
    Immediate index = bigToInt();
    bip.op1 = pop_obj_ref();
    unsigned int size = GET_ELEMENT_COUNT(bip.op1);
    if (!((0 <= index ) && (index < size))) fatalError("Error: index out of bound");
    GET_REFS_PTR(bip.op1)
    [index] = bip.op2;
}

void getsz_instruction(void) {
    bip.op1 = pop_obj_ref();
    if (IS_PRIMITIVE(bip.op1)) {
        bigFromInt(-1);
        push_obj_ref(bip.res);
    } else {
        bigFromInt(GET_ELEMENT_COUNT(bip.op1));
        push_obj_ref(bip.res);
    }
}

void pushn_instruction(void) {
    push_obj_ref(NULL);
}

void refeq_instruction(void) {
    bip.op1 = pop_obj_ref();
    bip.op2 = pop_obj_ref();
    if (bip.op1 == bip.op2) {
        bigFromInt(1);
        push_obj_ref(bip.res);
    } else {
        bigFromInt(0);
        push_obj_ref(bip.res);
    }
}

void refne_instruction(void) {
    bip.op1 = pop_obj_ref();
    bip.op2 = pop_obj_ref();
    if (bip.op1 != bip.op2) {
        bigFromInt(1);
        push_obj_ref(bip.res);
    } else {
        bigFromInt(0);
        push_obj_ref(bip.res);
    }
}
