# Makefile

all: encode decode different clean

encode: encode.o EncodeParameters.o TGAImage.o Encoder.o DictionaryTree.o
	g++ -o encode encode.o EncodeParameters.o TGAImage.o Encoder.o DictionaryTree.o

decode: decode.o Decoder.o DecodeParameters.o
	g++ -o decode decode.o Decoder.o DecodeParameters.o

different: different.o Encoder.o TGAImage.o DiffParameters.o DictionaryTree.o
	g++ -o different different.o Encoder.o TGAImage.o DiffParameters.o DictionaryTree.o

encode.o: encode.cpp
	g++ -c encode.cpp

decode.o: decode.cpp
	g++ -c decode.cpp

different.o: different.cpp
	g++ -c different.cpp

EncodeParameters.o: src/EncodeParameters.cpp src/EncodeParameters.h
	g++ -c src/EncodeParameters.cpp -o EncodeParameters.o

TGAImage.o: src/TGAImage.cpp src/TGAImage.h
	g++ -c src/TGAImage.cpp -o TGAImage.o

Encoder.o: src/Encoder.cpp src/Encoder.h
	g++ -c src/Encoder.cpp -o Encoder.o

DictionaryTree.o: src/DictionaryTree.cpp src/DictionaryTree.h
	g++ -c src/DictionaryTree.cpp -o DictionaryTree.o

Decoder.o: src/Decoder.cpp src/Decoder.h
	g++ -c src/Decoder.cpp -o Decoder.o

DecodeParameters.o: src/DecodeParameters.cpp src/DecodeParameters.h
	g++ -c src/DecodeParameters.cpp -o DecodeParameters.o

DiffParameters.o: src/DiffParameters.cpp src/DiffParameters.h
	g++ -c src/DiffParameters.cpp -o DiffParameters.o

clean:
	rm -f *.o
