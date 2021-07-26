#
# This file is part of the course materials for AMATH483/583 at the University of Washington,
# Spring 2020
#
# Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
# https://creativecommons.org/licenses/by-nc-sa/4.0/
#
# Author: Andrew Lumsdaine
#



TARGETS		:= 
TESTS		:= matmat_test.exe pmatmat_test.exe matvec_test.exe norms_test.exe pmatvec_test.exe pagerank_test.exe

include ../include/Make.inc  # DRY -- logic moved to include file


# The following 4 (yes 4) lines must be in all the subdirectory makefiles
#-----------------------------------------------------------------
# DO NOT DELETE THIS LINE -- make depend uses it
# DEPENDENCIES MUST END AT END OF FILE
matmat_test.o: matmat_test.cpp ../include/catch.hpp \
 ../include/COOMatrix.hpp ../include/Matrix.hpp ../include/Vector.hpp \
 ../include/CSCMatrix.hpp ../include/CSRMatrix.hpp ../include/Vector.hpp \
 ../include/amath583.hpp ../include/util.hpp ../include/amath583IO.hpp \
 ../include/amath583IO.hpp ../include/COOMatrix.hpp \
 ../include/CSRMatrix.hpp ../include/AOSMatrix.hpp \
 ../include/CSCMatrix.hpp
pmatmat_test.o: pmatmat_test.cpp ../include/catch.hpp \
 ../include/COOMatrix.hpp ../include/Matrix.hpp ../include/Vector.hpp \
 ../include/CSCMatrix.hpp ../include/CSRMatrix.hpp ../include/Vector.hpp \
 ../include/amath583.hpp ../include/util.hpp ../include/amath583IO.hpp \
 ../include/amath583IO.hpp ../include/COOMatrix.hpp \
 ../include/CSRMatrix.hpp ../include/AOSMatrix.hpp \
 ../include/CSCMatrix.hpp
matvec_test.o: matvec_test.cpp ../include/catch.hpp \
 ../include/COOMatrix.hpp ../include/Matrix.hpp ../include/Vector.hpp \
 ../include/CSCMatrix.hpp ../include/CSRMatrix.hpp ../include/Vector.hpp \
 ../include/amath583.hpp ../include/util.hpp ../include/amath583IO.hpp \
 ../include/amath583IO.hpp ../include/COOMatrix.hpp \
 ../include/CSRMatrix.hpp ../include/AOSMatrix.hpp \
 ../include/CSCMatrix.hpp
norms_test.o: norms_test.cpp ../include/catch.hpp ../include/norms.hpp \
 ../include/Timer.hpp ../include/Vector.hpp ../include/amath583.hpp \
 ../include/util.hpp ../include/Matrix.hpp
pmatvec_test.o: pmatvec_test.cpp ../include/catch.hpp \
 ../include/COOMatrix.hpp ../include/Matrix.hpp ../include/Vector.hpp \
 ../include/CSCMatrix.hpp ../include/CSRMatrix.hpp ../include/Vector.hpp \
 ../include/amath583.hpp ../include/util.hpp ../include/amath583IO.hpp \
 ../include/amath583IO.hpp ../include/COOMatrix.hpp \
 ../include/CSRMatrix.hpp ../include/AOSMatrix.hpp \
 ../include/CSCMatrix.hpp
pagerank_test.o: pagerank_test.cpp ../include/pagerank.hpp \
 ../include/COOMatrix.hpp ../include/Matrix.hpp ../include/Vector.hpp \
 ../include/CSCMatrix.hpp ../include/CSRMatrix.hpp ../include/Timer.hpp \
 ../include/amath583.hpp ../include/util.hpp ../include/amath583IO.hpp \
 ../include/AOSMatrix.hpp ../include/catch.hpp
# DEPENDENCIES MUST END AT END OF FILE
# IF YOU PUT STUFF HERE IT WILL GO AWAY
# see make depend above
