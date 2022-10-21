INCLUDE = ./headers
SRC = ./source
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -O0 -I$(INCLUDE) -L ./BSdatatypes.a
EXEC = giorgis 


$(EXEC): main.o
	@$(CC) $(CFLAGS) -o $(EXEC) main.o

run: $(EXEC)
	@./$(EXEC)
clean: 
	@$(RM) $(EXEC) 