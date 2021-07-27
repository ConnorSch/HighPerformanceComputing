#!/bin/bash
 
. verify-opts.bash
 
for DEFS in "${ALLDEFS[@]}"; do
    for OPTS in "${ALLOPTS[@]}"; do
	make clean

	echo make norm_test.exe  DEFS="${DEFS}" OPTS="${OPTS}"
	make norm_test.exe       DEFS="${DEFS}" OPTS="${OPTS}"
	./norm_test.exe

    done
done





