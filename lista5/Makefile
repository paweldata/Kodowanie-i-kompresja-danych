# Makefile

all: main clean

main: main.o DictionaryTree.o
	g++ -o main main.o DictionaryTree.o

main.o: main.cpp
	g++ -c main.cpp

DictionaryTree.o: src/DictionaryTree.cpp src/DictionaryTree.h
	g++ -c src/DictionaryTree.cpp -o DictionaryTree.o

clean:
	rm -f *.o
