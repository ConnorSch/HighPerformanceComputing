#!/bin/bash
 
. verify-opts.bash
 
for DEFS in "${ALLDEFS[@]}"; do
    for OPTS in "${ALLOPTS[@]}"; do
	make clean
	make norm_test.exe  DEFS="${DEFS}" OPTS="${OPTS}"
	make norm_order.exe  DEFS="${DEFS}" OPTS="${OPTS}"
    done
done
