#
GCC = g++
GCCFLAGS = -Wall -Werror -std=c++0x

OBJ = main.o parser.o
OUT = parser.out

all : program

program : $(OBJ)
  &(GCC) $(GCCFLAGS) -o $(OUT) $(OBJ)
  
main.o : Source.cpp Parser.h
  &(GCC) $(GCCFLAGS) -c Source.cpp
  
parser.o : Parser.cpp Parser.h
  &(GCC) $(GCCFLAGS) -c Parser.cpp
  
clean :
  rm *.o
  
uninstall : 
  rm *.out
