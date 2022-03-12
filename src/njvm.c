#include "njvm.h"

NinjaVM vm;

NinjaVM default_ir(NinjaVM vm) {
    vm.ir.size = vm.ir.pc = 0;
    vm.ir.data = NULL;
    return vm;
}

NinjaVM default_rv(NinjaVM vm) {
    vm.rv = NULL;
    return vm;
}

NinjaVM default_stack(NinjaVM vm) {
    vm.stack.size = vm.stack.sp = vm.stack.fp = 0;
    vm.stack.memory = 64;
    vm.stack.bytes = vm.stack.memory * 1024;
    vm.stack.max_items = vm.stack.bytes / sizeof(StackSlot);
    vm.stack.data = NULL;
    return vm;
}

NinjaVM default_sda(NinjaVM vm) {
    vm.sda.size = 0;
    vm.sda.data = NULL;
    return vm;
}

NinjaVM default_heap(NinjaVM vm) {
    vm.heap.size = vm.heap.used = 0;
    vm.heap.memory = 8192;
    vm.heap.bytes = vm.heap.memory * 1024;
    vm.heap.available = vm.heap.bytes / 2;
    vm.heap.next = vm.heap.begin = vm.heap.active = vm.heap.passive = NULL;
    return vm;
}

NinjaVM default_gc(NinjaVM vm) {
    vm.gc.purge_flag = vm.gc.stats_flag = false;
    vm.gc.copied_objects = vm.gc.copied_bytes = 0;
    return vm;
}

NinjaVM default_debugger(NinjaVM vm) {
    vm.debugger.activated = false;
    return vm;
}

NinjaVM default_bp(NinjaVM vm) {
    vm.bp = NULL;
    return vm;
}

NinjaVM default_vm(void) {
    bip.op1 = bip.op2 = bip.res = bip.rem = NULL;
    if (vm.heap.begin) {
        free(vm.heap.begin);
    }
    if (vm.stack.data) {
        free(vm.stack.data);
    }
    if (vm.rv) {
        free(vm.rv);
    }
    if (vm.bp) {
        free(vm.bp);
    }
    if (vm.ir.data) {
        free(vm.ir.data);
    }
    if (vm.sda.data) {
        free(vm.sda.data);
    }
    vm = default_ir(vm);
    vm = default_rv(vm);
    vm = default_stack(vm);
    vm = default_sda(vm);
    vm = default_heap(vm);
    vm = default_gc(vm);
    vm = default_debugger(vm);
    vm = default_bp(vm);
    return vm;
}

int njvm(int argc, char *argv[]) {
    vm = default_vm();
    bool code_flag = false;
    char *code_file = NULL;
    for (int i = 1; i <= argc; i++) {
        if (i == argc) {
            if (!code_flag) {
                fatalError("Error: no code file specified");
            }
            init(code_file);
        }
        if (!strcmp(argv[i], "--debug")) {
            vm.debugger.activated = true;
            continue;
        }
        if (!strcmp(argv[i], "--help")) {
            printf("usage: ./njvm [options] <code file>\n");
            printf("Options:\n");
            printf("  --stack <n>\t   set stack size to n KBytes (default: n = 64)\n");
            printf("  --heap <n>\t   set heap size to n KBytes (default: n = 8192)\n");
            printf("  --gcstats\t   show garbage collection stats\n");
            printf("  --gcpurge\t   purge old objects after collection\n");
            printf("  --debug\t   start virtual machine in debug mode\n");
            printf("  --version\t   show version and exit\n");
            printf("  --help\t   show this help and exit\n");
            exit(0);
        }
        if (!strcmp(argv[i], "--version")) {
            printf("Ninja Virtual Machine version %d (compiled %s, %s)\n", NINJA_BINARY_VERSION, __DATE__, __TIME__);
            exit(0);
        }
        if (!strcmp(argv[i], "--stack")) {
            if (i >= argc - 1) {
                continue;
            }
            int memory = strtol(argv[++i], (char **)NULL, 10);
            if (memory <= 0) {
                continue;
            }
            vm.stack.memory = memory;
            continue;
        }
        if (!strcmp(argv[i], "--heap")) {
            if (i >= argc - 1) {
                continue;
            }
            int memory = strtol(argv[++i], (char **)NULL, 10);
            if (memory <= 0) {
                continue;
            }
            vm.heap.memory = memory;
            continue;
        }
        if (!strcmp(argv[i], "--gcstats")) {
            vm.gc.stats_flag = true;
            continue;
        }
        if (!strcmp(argv[i], "--gcpurge")) {
            vm.gc.purge_flag = true;
            continue;
        }
        if (!strncmp("-", argv[i], strlen("-"))) {
            printf("unknown command line argument '%s', try '%s --help'\n", argv[i], argv[0]);
            exit(1);
        }
        if (code_flag) {
            fatalError("Error: more than one code file specified");
        }
        code_file = argv[i];
        code_flag = true;
        if (i < argc - 1) {
            continue;
        }
        init(code_file);
    }
    return 0;
}
