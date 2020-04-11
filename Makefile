MAKE	:= make
CXX		:= g++
CC		:= gcc
                                                                                
#SRC_FILES 	:= $(wildcard *.cpp */*.cpp)
SRC_FILES	:= c_test.c
OBJ_FILES 	:= $(SRC_FILES:.c=.o)
#CXX_FLAGS      := -std=c++17 -IInclude -O3 -fsanitize=address
#LD_FLAGS       := -lpthread -fsanitize=address
CXX_FLAGS       := -std=c++17 -IInclude -O3
C_FLAGS       	:= -O0
LD_FLAGS        := -lpthread
PROGS		= c_test

all: $(PROGS)

c_test: $(OBJ_FILES)
	$(CC) -o c_test $(OBJ_FILES) $(LD_FLAGS)

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -c -g -o $@ $<
	
%.o: %.c
	$(CC) $(C_FLAGS) -c -g -o $@ $<
clean:
	rm -f *.o */*.o
	rm -f c_test