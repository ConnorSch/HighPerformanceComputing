# -*- mode:Makefile -*-
#
# This file is part of the course materials for AMATH483/583 at the University of Washington,
# Spring 2020
#
# Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
# https://creativecommons.org/licenses/by-nc-sa/4.0/
#
# Author: Andrew Lumsdaine
#


CXX	    	:= g++-9

# Maximum optimization effort: -Ofast -march=native -DNDEBUG
OPTS        	:= -Ofast -march=native -DNDEBUG
DEBUG		:= # -g -O0 -fsanitize=address
PROFILE		:= 
LANG            := -std=c++14
PICKY       	:= -Wall
DIAG		:= # -Rpass=.*
INCLUDES	:= -I../include

VPATH		= ../include:../src

CXXFLAGS	+= $(DEFS) $(XDEFS) $(OPTS) $(DEBUG) $(PROFILE) $(LANG) $(PICKY) $(INCLUDES) $(DIAG)

ifeq (, $(shell which ${CXX}))
  CXX := c++
  ifeq (, $(shell which ${CXX}))
  CXX := g++
  ifeq (, $(shell which ${CXX}))
  CXX := g++-9
  ifeq (, $(shell which ${CXX}))
  $(error "No ${CXX} in $(PATH) -- set CXX to an appropriate compiler in Makefile")
  endif
  endif
  endif
endif

CXXVERSION 	:= $(shell ${CXX} --version | head -1)

ifeq 'g++' '$(findstring g++, $(CXXVERSION))'
  CXXFAM := gnu
endif

ifeq 'clang' '$(findstring clang, $(CXXVERSION))'
  CXXFAM := clang
endif

OS		:= $(shell uname -s)

ifeq ($(OS),Darwin)
ifeq ($(CXXFAM),clang)
  XDEFS         += -Xpreprocessor
  LIBS		+= -lpthread -lomp
endif
ifeq ($(CXXFAM),gnu)
  LIBS		+= -L/usr/local/lib -lomp
endif
endif

XDEFS		+= -fopenmp

ifeq ($(OS),Linux)
ifeq ($(CXXFAM),clang)
	LIBS	+= -lpthread
endif
endif

SOURCES		= $(TARGETS:.exe=.cpp) $(TESTS:.exe=.cpp) 
OBJECTS		= $(SOURCES:.cpp=.o)   
HEADERS		= $(SOURCES:.cpp=.hpp) $(LINC)
PCHS		= $(HEADERS:=.gch)

$SHELL		= bash

LINC		:= amath583.hpp amath583IO.hpp

.PHONY		: defreport optreport clean depend all verify %.test
.SUFFIXES	: .exe .test
.PRECIOUS   	: %.o

all		: $(TARGETS) $(TESTS)

ALLTESTS	:= $(TARGETS:.exe=.test) $(TESTS:.exe=.test)

verify		: $(ALLTESTS)

%.test		: %.exe
		  ./$^

%.exe   	: %.o 
		  $(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

%.o 		: %.cpp
		  $(CXX) -c $(CXXFLAGS) $< -o $@

%.s 		: %.cpp
		  $(CXX) -S $(CXXFLAGS) $<

defreport	:
		  $(CXX) -dM -E -x c++ /dev/null

optreport	:
		  echo 'int;' | $(CXX) -xc++ $(CXXFLAGS) - -o /dev/null -\#\#\#

clean		:
		  /bin/rm -f $(TARGETS) $(TESTS) $(OBJECTS) $(PCHS) Matrix.s a.out *~ Makefile.bak makedep

depend		: 
	@ $(CXX) -MM $(LANG) $(INCLUDES) $(SOURCES) $(XSRC) > makedep
	@ echo '/^# DO NOT DELETE THIS LINE/+2,$$d' >eddep
	@ echo '$$r makedep' >>eddep
	@ echo 'w' >>eddep
	@ cp Makefile Makefile.bak
	@ ed - Makefile < eddep
	@ /bin/rm eddep makedep
	@ echo '# DEPENDENCIES MUST END AT END OF FILE' >> Makefile
	@ echo '# IF YOU PUT STUFF HERE IT WILL GO AWAY' >> Makefile
	@ echo '# see make depend above' >> Makefile

