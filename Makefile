CC = gcc
CFLAGS = -Wall -std=c18 -ggdb
LDLIBS = -lm

test : root
	./root 121
	./root 2
	./root 1.53e19
	./root -10
	./root 7.41e-13

gdb : root
	gdb --args ./root 2

clean: 
	-rm root