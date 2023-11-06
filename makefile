CFLAGS = -Wall -ansi -pedantic -Werror -g
OBJS = terminal.o maze.o printAndMove.o linkedlist.o
CC = gcc
EXEC = maze

$(EXEC) : $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) 

maze.o : maze.c printAndMove.h terminal.h maze.h LinkedList.h
	$(CC) $(CFLAGS) -c maze.c

terminal.o : terminal.c terminal.h
	$(CC) $(CFLAGS) -c terminal.c

printAndMove.o : printAndMove.c printAndMove.h 
	$(CC) $(CFLAGS) -c printAndMove.c

linkedlist.o : linkedlist.c LinkedList.h
	$(CC) $(CFLAGS) -c linkedlist.c

clean:
	rm -f $(OBJS) $(EXEC)