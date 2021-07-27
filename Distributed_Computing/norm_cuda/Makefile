#
# This file is part of the course materials for AMATH483/583 at the University of Washington,
# Spring 2020
#
# Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
# https://creativecommons.org/licenses/by-nc-sa/4.0/
#
# Author: Andrew Lumsdaine
#


CUTARGETS	:= norm_thrust.exe 

CUTESTS		:= 

TARGETS		:= norm_parfor.exe norm_seq.exe
TESTS		:= 

norm_parfor.exe: norm_parfor.o 
		  $(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

norm_seq.exe: norm_seq.o 
		  $(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)


include ../include/Make_cu.inc  # DRY -- logic moved to include file



# The following 4 (yes 4) lines must be in all the subdirectory makefiles
#-----------------------------------------------------------------
# DO NOT DELETE THIS LINE -- make depend uses it
# DEPENDENCIES MUST END AT END OF FILE
norm_parfor.o: norm_parfor.cpp ../include/norm_utils.hpp \
 ../include/Timer.hpp ../include/Vector.hpp ../include/amath583.hpp \
 ../include/util.hpp ../include/Matrix.hpp ../include/norms.hpp
norm_seq.o: norm_seq.cpp ../include/norms.hpp ../include/Timer.hpp \
 ../include/Vector.hpp ../include/amath583.hpp ../include/util.hpp \
 ../include/Matrix.hpp ../include/norm_utils.hpp
norm_thrust.o: norm_thrust.cu ../include/Timer.hpp ../include/Vector.hpp \
 ../include/amath583.hpp ../include/util.hpp ../include/Matrix.hpp \
 ../include/Vector.hpp
# DEPENDENCIES MUST END AT END OF FILE
# IF YOU PUT STUFF HERE IT WILL GO AWAY
# see make depend above
