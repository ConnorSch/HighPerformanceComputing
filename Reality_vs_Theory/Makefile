#
# This file is part of the course materials for AMATH483/583 at the University of Washington,
# Spring 2020
#
# Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
# https://creativecommons.org/licenses/by-nc-sa/4.0/
#
# Author: Andrew Lumsdaine
#

CXX             := c++

OPTS            := -Ofast -march=native -DNDEBUG
#DEBUG		:= -g -O0 -fno-omit-frame-pointer # -fsanitize=address
PROFILE		:= 
LANG            := -std=c++11
PICKY           := -Wall

OS              := $(shell uname -s)
ifeq ($(OS),Linux)
        LIBS    += -lpthread
endif

CXXFLAGS	+= $(LANG) $(DEFS) $(OPTS) $(DEBUG) $(PROFILE) $(PICKY)

TESTS		:= norm_test.exe 
TARGETS		:= bonnie_and_clyde.exe bonnie_and_clyde_function_object.exe norm_order.exe 
SOURCES		:= $(TARGETS:.exe=.cpp) $(TESTS:.exe=.cpp) amath583.cpp 
HEADERS		:= $(SOURCES:.cpp=.hpp)
OBJECTS		:= $(SOURCES:.cpp=.o)
PCHS		:= $(HEADERS:=.gch)

LSRC		:= amath583.cpp 
LOBJ		:= $(LSRC:.cpp=.o)


.PHONY		: defreport optreport clean depend all

all		: $(TARGETS)

%.exe        	: %.o
		  $(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

%.o 		: %.cpp
		  $(CXX) -c $(CXXFLAGS) $< -o $@

%.s 		: %.cpp
		  $(CXX) -S $(CXXFLAGS) $<

norm_test.exe	: norm_test.o $(LOBJ)
norm_order.exe	: norm_order.o $(LOBJ)
pagerank.exe	: pagerank.o $(LOBJ)
pnorm.exe       : pnorm.o  $(LOBJ)


defreport	:
		  $(CXX) -dM -E -x c++ /dev/null

optreport	:
		  echo 'int;' | $(CXX) -xc++ $(CXXFLAGS) - -o /dev/null -\#\#\#

clean		:
		  /bin/rm -f $(TESTS) $(TARGETS) $(OBJECTS) $(PCHS) Matrix.s a.out *~ Makefile.bak

depend		: 
	@ $(CXX) -MM $(LANG) $(INCLUDES) $(SOURCES) > makedep
	@ echo '/^# DO NOT DELETE THIS LINE/+2,$$d' >eddep
	@ echo '$$r makedep' >>eddep
	@ echo 'w' >>eddep
	@ cp Makefile Makefile.bak
	@ ed - Makefile < eddep
	@ /bin/rm eddep makedep
	@ echo '# DEPENDENCIES MUST END AT END OF FILE' >> Makefile
	@ echo '# IF YOU PUT STUFF HERE IT WILL GO AWAY' >> Makefile
	@ echo '# see make depend above' >> Makefile

# The following 4 (yes 4) lines must be in all the subdirectory makefiles
#-----------------------------------------------------------------
# DO NOT DELETE THIS LINE -- make depend uses it
# DEPENDENCIES MUST END AT END OF FILE
bonnie_and_clyde.o: bonnie_and_clyde.cpp
bonnie_and_clyde_function_object.o: bonnie_and_clyde_function_object.cpp
norm_order.o: norm_order.cpp Vector.hpp amath583.hpp Matrix.hpp
norm_test.o: norm_test.cpp catch.hpp Vector.hpp amath583.hpp Matrix.hpp
amath583.o: amath583.cpp amath583.hpp Matrix.hpp Vector.hpp
# DEPENDENCIES MUST END AT END OF FILE
# IF YOU PUT STUFF HERE IT WILL GO AWAY
# see make depend above
