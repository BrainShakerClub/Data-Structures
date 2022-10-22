# paths
SRC = ../source
INCLUDE = ../headers

# compiler
CC = gcc

# compiler options
CFLAGS = -Wall -Werror -Wextra -I$(INCLUDE)

# library
LIB = BSdatastructs.a

# object files
OBJS = $(SRC)/Lists/Lists.o \
	$(SRC)/Arrays/Arrays.o \
	$(SRC)/Queues/Queues.o \
	$(SRC)/Stacks/Stacks.o \
	$(SRC)/BinaryTrees/BinaryTrees.o \
	$(SRC)/RedBlackTrees/RedBlackTrees.o \
	$(SRC)/PriorityQueues/PriorityQueues.o \
	$(SRC)/DirectedGraphs/DirectedGraphs.o \
	$(SRC)/UndirectedGraphs/UndirectedGraphs.o \
	$(SRC)/HashTables/HashTable.o

# create the library
lib: $(OBJS)
	ar rcs $(LIB) $(OBJS)
	@$(RM) $(OBJS)

# destroy library
.PHONY: clean
clean:
	@$(RM) $(LIB)