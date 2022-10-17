INCLUDE = ./headers
SRC = ./source
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -O0 -I$(INCLUDE)
EXEC = giorgis 

OBJS = main.c $(SRC)/Lists/Lists.o $(SRC)/Arrays/Arrays.o $(SRC)/Queues/Queues.o $(SRC)/Stacks/Stacks.o 


$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)