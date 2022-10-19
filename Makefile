EXEC = a.out
CC = g++
CFLAGS = -c -Wall -g -std=c++11

$(EXEC): tasks.o lexer.o inputbuf.o execute.o project2.o
	$(CC) -o $(EXEC) tasks.o lexer.o inputbuf.o execute.o project2.o

project2.o: project2.cc
	$(CC) $(CFLAGS) project2.cc

tasks.o: tasks.cc
	$(CC) $(CFLAGS) tasks.cc

lexer.o: lexer.cc
	$(CC) $(CFLAGS) lexer.cc

inputbuf.o: inputbuf.cc
	$(CC) $(CFLAGS) inputbuf.cc

execute.o: execute.cc
	$(CC) $(CFLAGS) execute.cc

clean:
	rm -f *.o $(EXEC)

