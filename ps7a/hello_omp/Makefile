#
# This file is part of the course materials for AMATH483/583 at the University of Washington,
# Spring 2020
#
# Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
# https://creativecommons.org/licenses/by-nc-sa/4.0/
#
# Author: Andrew Lumsdaine
#


TARGETS		= getenv.exe ompi_info.exe hello_omp_parallel.exe hello_omp_critical.exe  \
                  hello_omp_2_threads.exe hello_omp_num_threads.exe hello_omp_parallel_critical.exe 

TESTS		= 

include ../include/Make.inc  # DRY -- logic moved to include file

# The following 4 (yes 4) lines must be in all the subdirectory makefiles
#-----------------------------------------------------------------
# DO NOT DELETE THIS LINE -- make depend uses it
# DEPENDENCIES MUST END AT END OF FILE
getenv.o: getenv.cpp ../include/getenv.hpp
ompi_info.o: ompi_info.cpp ../include/getenv.hpp
hello_omp_parallel.o: hello_omp_parallel.cpp ../include/getenv.hpp
hello_omp_critical.o: hello_omp_critical.cpp ../include/getenv.hpp
hello_omp_2_threads.o: hello_omp_2_threads.cpp ../include/getenv.hpp
hello_omp_num_threads.o: hello_omp_num_threads.cpp ../include/getenv.hpp
hello_omp_parallel_critical.o: hello_omp_parallel_critical.cpp \
 ../include/getenv.hpp
# DEPENDENCIES MUST END AT END OF FILE
# IF YOU PUT STUFF HERE IT WILL GO AWAY
# see make depend above
