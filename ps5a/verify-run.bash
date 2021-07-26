#!/bin/bash
 
. verify-opts.bash
 
for DEFS in "${ALLDEFS[@]}"; do
    make clean
    make DEFS="${DEFS}" norm_order.exe norm_test.exe
    ./norm_test.exe
    ./norm_order.exe
done
