########################################################
# Makefile for CSCI 375
#   In many cases you will ONLY need to modify the
#   SRCS variable below
# Author: Gary M. Zoppetti, Ph.D.
########################################################

########################################################
# Variable definitions
########################################################
# C++ compiler
CXX := g++
#CXX := clang++

# Include directories, prefaced with "-I"
INCDIRS  := 

# C++ compiler flags
# Use the first for debugging, the second for release
CXXFLAGS := -g -Wall -std=c++14 $(INCDIRS)
#CXXFLAGS := -O3 -Wall -std=c++14 $(INCDIRS)

# Linker. For C++ should be $(CXX).
LINK := $(CXX)

# Linker flags. Usually none.
LDFLAGS := 

# Library paths, prefaced with "-L". Usually none.
LDPATHS := 

# Libraries used, prefaced with "-l".
LDLIBS := -lGLEW -lglfw -lGL 

# All source files, separated by spaces. Don't include header files. 
SRCS := Main.cpp Vector3.cpp ShaderProgram.cpp Mesh.cpp Camera.cpp KeyBuffer.cpp

# Extension for source files. Do NOT modify.
SOURCESUFFIX := cpp

# Determines object files based on SRCS.
OBJS := $(SRCS:.$(SOURCESUFFIX)=.o)

# Executable name. Defaults to basename of first name in SRCS.
EXEC := $(patsubst %.o, %, $(word 1, $(OBJS)))

# Command to generate dependency rules for make. 
MAKEDEPEND := $(CXX) $(CPPFLAGS) $(CXXFLAGS) -MM -MP

#############################################################

#############################################################
# Rules
#   Rules have the form
#   target : prerequisites
#   	  recipe
#############################################################

all : $(EXEC)

$(EXEC) : $(OBJS)
	$(LINK) $(LDFLAGS) $(LDPATHS) $^ -o $@ $(LDLIBS)

-include Makefile.deps

test : Vec3Test.o Vector3.o
	g++ Vec3Test.o Vector3.o -o Vec3Test
Vec3Test.o : Vec3Test.cpp
	g++ -Wall -std=c++14 -c Vec3Test.cpp
Vector3.o : Vector3.cpp Vector3.h
	g++ -Wall -std=c++14 -c Vector3.cpp

#############################################################

.PHONY : clean
clean :
	$(RM) $(EXEC) $(OBJS) a.out core
	$(RM) Makefile.deps *~
	$(RM) Vec3Test Vec3Test.o

.PHONY :  Makefile.deps
Makefile.deps :
	$(MAKEDEPEND) $(SRCS) > $@

#############################################################
#############################################################
