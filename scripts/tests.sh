#!/bin/sh

GREEN="\\033[0;32m"
RED="\\033[0;31m"
SET="\\033[0m"
VERSION="$(grep NINJA_BINARY_VERSION include/njvm.h | tail -c2)"
TEST_DIR="data/v$VERSION"
REFERENCE_NJVM="$TEST_DIR/njvm"
BUILD_NJVM="build/njvm"
FAIL_FLAG=false
LEAK_FLAG=false

red() {
    printf "$RED%s$SET" "$1"
}

green() {
    printf "$GREEN%s$SET" "$1"
}

for bin in "$TEST_DIR"/*.bin; do
    printf "Testing %s " "$bin"
    TEST=$(echo "$bin" | awk -F '.' '{print $1}')
    STDIN="$(cat "$TEST".in)"
    VALGRIND_LOG_FILE="$TEST.valgrind.out"
    echo > "$VALGRIND_LOG_FILE"
    VALGRIND="valgrind --leak-check=full --show-leak-kinds=all -s --log-file=$VALGRIND_LOG_FILE"
    EXEC_BUILD="$VALGRIND $BUILD_NJVM $bin"
    EXEC_REFERENCE="$REFERENCE_NJVM $bin"
    BUILD="$(echo "$STDIN" | $EXEC_BUILD)"
    REFERENCE="$(echo "$STDIN" | $EXEC_REFERENCE)"
    BUILD_OUT="$TEST.build.out"
    REFERENCE_OUT="$TEST.target.out"
    echo "$BUILD" > "$BUILD_OUT"
    echo "$REFERENCE" > "$REFERENCE_OUT"
    if diff "$BUILD_OUT" "$REFERENCE_OUT"
    then
        printf "["
        green "OK" 
        printf "]"
        grep -q "All heap blocks were freed" "$VALGRIND_LOG_FILE" ||
            { red " LEAKS MEMORY!" && LEAK_FLAG=true; }
        printf "\\n"
    else
        FAIL_FLAG=true
        printf "["
        red "FAILED" 
        printf "]\\n"
    fi
done

if [ $FAIL_FLAG = true ] || [ $LEAK_FLAG = true ]
then
    exit 1
fi
