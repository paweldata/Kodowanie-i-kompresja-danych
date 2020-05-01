# Makefile

all: main clean

main: main.o JPEG_LS.o JPEG_LS1.o JPEG_LS2.o JPEG_LS3.o JPEG_LS4.o JPEG_LS5.o JPEG_LS6.o JPEG_LS7.o JPEG_LSNew.o Original.o
	g++ -o main main.o JPEG_LS.o JPEG_LS1.o JPEG_LS2.o JPEG_LS3.o JPEG_LS4.o JPEG_LS5.o JPEG_LS6.o JPEG_LS7.o JPEG_LSNew.o Original.o

main.o: main.cpp
	g++ -c main.cpp

JPEG_LS.o: src/JPEG_LS.cpp src/JPEG_LS.h
	g++ -c src/JPEG_LS.cpp -o JPEG_LS.o

JPEG_LS1.o: src/JPEG_LS1.cpp src/JPEG_LS1.h
	g++ -c src/JPEG_LS1.cpp -o JPEG_LS1.o

JPEG_LS2.o: src/JPEG_LS2.cpp src/JPEG_LS2.h
	g++ -c src/JPEG_LS2.cpp -o JPEG_LS2.o

JPEG_LS3.o: src/JPEG_LS3.cpp src/JPEG_LS3.h
	g++ -c src/JPEG_LS3.cpp -o JPEG_LS3.o

JPEG_LS4.o: src/JPEG_LS4.cpp src/JPEG_LS4.h
	g++ -c src/JPEG_LS4.cpp -o JPEG_LS4.o

JPEG_LS5.o: src/JPEG_LS5.cpp src/JPEG_LS5.h
	g++ -c src/JPEG_LS5.cpp -o JPEG_LS5.o

JPEG_LS6.o: src/JPEG_LS6.cpp src/JPEG_LS6.h
	g++ -c src/JPEG_LS6.cpp -o JPEG_LS6.o

JPEG_LS7.o: src/JPEG_LS7.cpp src/JPEG_LS7.h
	g++ -c src/JPEG_LS7.cpp -o JPEG_LS7.o

JPEG_LSNew.o: src/JPEG_LSNew.cpp src/JPEG_LSNew.h
	g++ -c src/JPEG_LSNew.cpp -o JPEG_LSNew.o

Original.o: src/Original.cpp src/Original.h
	g++ -c src/Original.cpp -o Original.o

clean:
	rm -f *.o
