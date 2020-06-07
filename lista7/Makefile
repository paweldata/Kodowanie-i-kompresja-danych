# Makefile

all: encode noise decode check clean

encode: encode.o ParametersTwoFiles.o
	g++ -o encode encode.o ParametersTwoFiles.o

encode.o: encode.cpp
	g++ -c encode.cpp

ParametersTwoFiles.o: src/ParametersTwoFiles.cpp src/ParametersTwoFiles.h
	g++ -c src/ParametersTwoFiles.cpp -o ParametersTwoFiles.o

noise: noise.o ParametersNoise.o
	g++ -o noise noise.o ParametersNoise.o

noise.o: noise.cpp
	g++ -c noise.cpp

ParametersNoise.o: src/ParametersNoise.cpp src/ParametersNoise.h
	g++ -c src/ParametersNoise.cpp -o ParametersNoise.o

decode: decode.o ParametersTwoFiles.o
	g++ -o decode decode.o ParametersTwoFiles.o

decode.o: decode.cpp
	g++ -c decode.cpp

check: check.o ParametersTwoInputFiles.o
	g++ -o check check.o ParametersTwoInputFiles.o

check.o: check.cpp
	g++ -c check.cpp

ParametersTwoInputFiles.o: src/ParametersTwoInputFiles.cpp src/ParametersTwoInputFiles.h
	g++ -c src/ParametersTwoInputFiles.cpp -o ParametersTwoInputFiles.o

clean:
	rm -f *.o
