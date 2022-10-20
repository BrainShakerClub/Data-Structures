INCLUDE = ./headers
SRC = ./source
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -O0 -I$(INCLUDE)
EXEC = giorgis 

OBJS = main.o \
	$(SRC)/Lists/Lists.o \
	$(SRC)/Arrays/Arrays.o \
	$(SRC)/Queues/Queues.o \
	$(SRC)/Stacks/Stacks.o \
	$(SRC)/BinaryTrees/BinaryTrees.o \
	$(SRC)/RedBlackTrees/RedBlackTrees.o \
	$(SRC)/PriorityQueues/PriorityQueues.o \
	$(SRC)/DirectedGraphs/DirectedGraphs.o \
	$(SRC)/UndirectedGraphs/UndirectedGraphs.o \
	$(SRC)/HashTables/HashTable.o

%.o: %.c
	@$(CC) -c -o $@ $< $(CFLAGS)

$(EXEC): $(OBJS)
	@$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

run: $(EXEC)
	@./$(EXEC)
clean: 
	@$(RM) $(EXEC) $(OBJS)