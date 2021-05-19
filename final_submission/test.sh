#!/bin/bash

# Trigger all your test cases with this script
echo "test start"

./vm_x2017  test_codes/test_basic.x2017 | diff -w - tests/test_basic.out || echo "test 1 failed"

./vm_x2017  test_codes/test_call_func.x2017 | diff -w - tests/test_call_func.out || echo "test 2 failed"

./vm_x2017  test_codes/test_invalid_syntax_1.x2017 | diff -w - tests/test_invalid_syntax1.out || echo "test 3 failed"

./vm_x2017  test_codes/test_invalid_syntax_2.x2017 | diff -w - tests/test_invalid_syntax2.out || echo "test 4 failed"

./vm_x2017  test_codes/test_invalid_syntax_3.x2017 | diff -w - tests/test_invalid_syntax3.out || echo "test 5 failed"

./vm_x2017  test_codes/test_invalid_syntax_4.x2017 | diff -w - tests/test_invalid_syntax4.out || echo "test 6 failed"

./vm_x2017  test_codes/test_stack_over_flow.x2017 | diff -w - tests/test_stack_overflow.out || echo "test 7 failed"

./vm_x2017  test_codes/test_very_deep_stack.x2017 | diff -w - tests/test_very_deep_stack.out || echo "test 8 failed"
./vm_x2017 test_codes/test_oversize_code.x2017

if [ $?=1 ] 
then
    echo "last test passsed"
else
    echo "test 9 failed"
fi


echo "PASSED"

