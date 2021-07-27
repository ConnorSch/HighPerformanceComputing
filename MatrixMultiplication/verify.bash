#!/bin/bash 


function do_test() {
    echo "=== Testing $1 ==="
    $1
    if [ $? == 0 ] ; then
	echo "+++ $1 Passed +++"
    else
	echo "--- $1 Failed ---"
    fi
}

do_test "make clean"

do_test "make timing0.exe timing3.exe efficiency0.exe efficiency3.exe"
do_test "make float_vs_double0.exe float_vs_double3.exe"

do_test "make test_mult.exe"
do_test "./test_mult.exe"

do_test "make test_operator.exe"
do_test "./test_operator.exe"

do_test "make test_transpose.exe"
do_test "./test_transpose.exe"

do_test "make test_mult_trans.exe"
do_test "./test_mult_trans.exe"

do_test "make mmtime.exe"
do_test "./mmtime.exe 256"

do_test "make mnist.exe"
do_test "./mnist.exe train-images.idx3-ubyte 256"






    
