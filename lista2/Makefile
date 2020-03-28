# Makefile

all: encode decode clean

encode: encode.o BitsTable.o codingAnalysis.o
	g++ -o encode encode.o BitsTable.o codingAnalysis.o

decode: decode.o BitsTable.o
	g++ -o decode decode.o BitsTable.o

encode.o: encode.cpp
	g++ -c encode.cpp

decode.o: decode.cpp
	g++ -c decode.cpp

BitsTable.o: src/BitsTable.cpp src/BitsTable.h
	g++ -c src/BitsTable.cpp -o BitsTable.o

codingAnalysis.o: src/codingAnalysis.cpp src/codingAnalysis.h
	g++ -c src/codingAnalysis.cpp -o codingAnalysis.o -std=c++17

clean:
	rm -f *.o
