CFLAGS=-Wall -g -DNDEBUG

all: splayTreeTest

splayTreeTest: splayTree.o

clean:
	rm -f splayTree.o splayTreeTest
