INCLUDE = ./headers
SRC = ./source
LIB = ./library
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -O0 -I$(INCLUDE) 
EXEC = executable 


$(EXEC): main.o
	@$(CC) -o $(EXEC) main.o -L. $(LIB)/BSdatastructs.a $(CFLAGS)

run: $(EXEC)
	@./$(EXEC)
clean: 
	@$(RM) $(EXEC) 