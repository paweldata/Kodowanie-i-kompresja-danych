# Makefile

all: encode decode clean

encode: encode.o universalCode.o codingAnalysis.o
	g++ -o encode encode.o universalCode.o codingAnalysis.o

decode: decode.o universalCode.o
	g++ -o decode decode.o universalCode.o

encode.o: encode.cpp
	g++ -c encode.cpp

decode.o: decode.cpp
	g++ -c decode.cpp

universalCode.o: src/universalCode.cpp src/universalCode.h
	g++ -c src/universalCode.cpp -o universalCode.o

codingAnalysis.o: src/codingAnalysis.cpp src/codingAnalysis.h
	g++ -c src/codingAnalysis.cpp -o codingAnalysis.o -std=c++17

clean:
	rm -f *.o
