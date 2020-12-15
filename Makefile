# Makefile for ex1-q1 winter 2019A
CFLAGS = -Wall
LDFLAGS = -lm # not really needed for this exercise
CC = gcc -std=c99
ECHO = echo "going to compile for target $@"
PROG = ex1_q1
all: $(PROG) test

ex1_q1.o: ex1_q1.c ex1_q1.h
	echo going to compile ex1_q1.c...
	gcc -Wall -c ex1_q1.c

ex1_q1_given.o: ex1_q1_given.c ex1_q1.h
	echo going to compile ex1_q1_given.c... 
	gcc -Wall -c ex1_q1_given.c

$(PROG): ex1_q1_given.o ex1_q1.o
	echo 'going to build (link) ex1_q1...'
	gcc -Wall -o $(PROG) ex1_q1_given.o ex1_q1.o -lm
	
clean:
	rm -vf *.o $(PROG) *.log

test:
	@echo going to run test...
	# make sure you have input file in.txt.
	# so the following command works
	./$(PROG) < in.txt > out.log