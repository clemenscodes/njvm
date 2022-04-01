#include "processor.h"

void init(void) {
    FILE *fp = open_code_file();
    check_ninja_binary_format(fp);
    check_ninja_version(fp);
    unsigned vc = check_ninja_variable_count(fp),
             ic = check_ninja_instruction_count(fp);
    initialize_sda(vc);
    initialize_ir(ic);
    fseek(fp, 16, SEEK_SET);
    unsigned read = fread(vm.ir.data, sizeof(Bytecode), ic, fp);
    if (read != ic) {
        fprintf(stderr, "Error: read [%u] of [%u] items.\n", read, ic);
        close_file(fp);
        exit(1);
    }
    close_file(fp);
    vm.debugger.activated ? debug() : execute();
    exit(0);
}

void execute(void) {
    printf("Ninja Virtual Machine started\n");
    Bytecode instruction = vm.ir.data[vm.ir.pc];
    Opcode opcode = decode_opcode(instruction);
    while (opcode != halt) {
        instruction = vm.ir.data[vm.ir.pc];
        opcode = decode_opcode(instruction);
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
            break;
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
            exit(1);
    }
}

void halt_instruction(void) {
    run_gc();
    free_stack();
    free_heap();
    free_ir();
    free_sda();
    printf("Ninja Virtual Machine stopped\n");
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
    if (!scanf("%c", &read_character)) {
        fatalError("failed to read character");
    }
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
    if ((vm.stack.size + immediate) >= vm.stack.max_items) {
        fatalError("stack overflow");
    }
    if (immediate < 0) {
        fatalError("cannot allocate stack frame with negative immediate");
    }
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
    if (!bigToInt()) {
        jump_instruction(immediate);
    }
}

void brt_instruction(Immediate immediate) {
    bip.op1 = pop_obj_ref();
    if (bigToInt() == 1) {
        jump_instruction(immediate);
    }
}

void call_instruction(Immediate immediate) {
    push(vm.ir.pc);
    vm.ir.pc = immediate;
}

void ret_instruction(void) {
    vm.ir.pc = pop();
}

void drop_instruction(Immediate immediate) {
    for (int i = 0; i < immediate; i++) {
        pop_obj_ref();
    }
}

void pushr_instruction(void) {
    vm.rv ? push_obj_ref(vm.rv)
          : fatalError("no value in return value register");
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
    ObjRef obj_ref = new_composite_object(immediate);
    push_obj_ref(obj_ref);
}

void getf_instruction(Immediate immediate) {
    ObjRef record = pop_obj_ref();
    if (!record) {
        fatalError("object is not defined");
    }
    if (IS_PRIMITIVE(record)) {
        fatalError("record is not a composite object");
    }
    unsigned size = GET_ELEMENT_COUNT(record);
    if (immediate < 0 || size <= immediate) {
        fatalError("record index out of bound");
    }
    ObjRef field = GET_REFS_PTR(record)[immediate];
    push_obj_ref(field);
}

void putf_instruction(Immediate immediate) {
    ObjRef new_field = pop_obj_ref();
    ObjRef record = pop_obj_ref();
    if (!record) {
        fatalError("record is not defined");
    }
    if (IS_PRIMITIVE(record)) {
        fatalError("record is not a composite object");
    }
    unsigned size = GET_ELEMENT_COUNT(record);
    if (immediate < 0 || size <= immediate) {
        fatalError("stack index out of bound");
    }
    ObjRef *fields = GET_REFS_PTR(record);
    fields[immediate] = new_field;
}

void newa_instruction(void) {
    bip.op1 = pop_obj_ref();
    if (!IS_PRIMITIVE(bip.op1)) {
        fatalError("object is not primitive");
    }
    unsigned size = bigToInt();
    ObjRef array = new_composite_object(size);
    push_obj_ref(array);
}

void getfa_instruction(void) {
    bip.op1 = pop_obj_ref();
    if (!IS_PRIMITIVE(bip.op1)) {
        fatalError("not a primitive object");
    }
    Immediate index = bigToInt();
    ObjRef array = pop_obj_ref();
    if (!array) {
        fatalError("array is not defined");
    }
    if (IS_PRIMITIVE(array)) {
        fatalError("array is not a composite object");
    }
    unsigned size = GET_ELEMENT_COUNT(array);
    if (index < 0 || size <= index) {
        fatalError("array index out of bound");
    }
    ObjRef field = GET_REFS_PTR(array)[index];
    push_obj_ref(field);
}

void putfa_instruction(void) {
    ObjRef new_field = pop_obj_ref();
    bip.op1 = pop_obj_ref();
    if (!IS_PRIMITIVE(bip.op1)) {
        fatalError("not a primitive object");
    }
    Immediate index = bigToInt();
    ObjRef array = pop_obj_ref();
    if (!array) {
        fatalError("array is not defined");
    }
    if (IS_PRIMITIVE(array)) {
        fatalError("array is not a composite object");
    }
    unsigned size = GET_ELEMENT_COUNT(array);
    if (index < 0 || size <= index) {
        fatalError("array index out of bound");
    }
    ObjRef *fields = GET_REFS_PTR(array);
    fields[index] = new_field;
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
