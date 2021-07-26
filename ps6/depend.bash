#!/bin/bash

find . -name \*~ -exec rm {} \;

for SUBDIR in hello_omp matvec norm pagerank test; do
 cd ${SUBDIR}
 make clean
 make depend CXX=g++-9
 make clean
 cd ..
done


