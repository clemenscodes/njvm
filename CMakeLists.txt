cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_C_COMPILER gcc)

set(CMAKE_C_STANDARD 99)

set(CMAKE_BUILD_TYPE Release)

set(BIGINT_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/lib/build/lib/libbigint.a)

project(njvm C)

include(cmake/FetchCMocka.cmake)

add_compile_options(-g -Wall -pedantic)

include_directories(include)

set(SOURCES 
    src/njvm.c 
    src/cpu/instruction.c 
    src/cpu/processor.c 
    src/cpu/debugger.c 
    src/cpu/opcode.c 
    src/cpu/immediate.c 
    src/cpu/gc.c 
    src/memory/ir.c 
    src/memory/stack.c
    src/memory/sda.c
    src/memory/heap.c
    src/utils/utils.c
    src/utils/support.c
)

set(TESTS
    tests/test.c
    tests/opcode_test.c 
    tests/instruction_test.c 
    tests/ir_test.c 
    tests/stack_test.c 
    tests/processor_test.c 
    tests/sda_test.c 
    tests/utils_test.c 
    tests/heap_test.c 
)

set(TEST_HEADERS
    tests/include/cmocka.h
    tests/include/test.h
    tests/include/opcode_test.h
    tests/include/instruction_test.h
    tests/include/ir_test.h
    tests/include/stack_test.h
    tests/include/processor_test.h
    tests/include/sda_test.h
    tests/include/utils_test.h
    tests/include/heap_test.h
)

add_custom_target(libbigint COMMAND make WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_library(njvm_lib STATIC ${SOURCES})

add_library(bigint STATIC IMPORTED)

set_property(TARGET bigint APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)

set_target_properties(bigint PROPERTIES IMPORTED_LOCATION_NOCONFIG ${BIGINT_LIBRARY})

add_dependencies(bigint libbigint)

add_dependencies(njvm_lib bigint)

target_link_libraries(njvm_lib bigint)

add_executable(njvm src/main.c)

target_link_libraries(njvm njvm_lib)

enable_testing()

add_executable(tests ${TESTS} ${TEST_HEADERS})

target_link_libraries(tests PRIVATE njvm_lib cmocka-static)

add_test(UnitTests tests)
