# Kodowanie-i-kompresja-danych
## Lista 6

#### Kodowanie różnicowe

Program koduje różnicowo obraz wejściowy o formacie TGA dla podanej ilości bitów na kolor.

```Shell
$ make
$ ./encode -in inputFile -out outputFile -k bitsNumber
$ ./decode -in inputFile -out outputFile
$ ./different -original oryginalFile -copy copyFile
```
1 <= bitsNumber <= 7, liczba bitów na kolor (domyślnie 8 w formacie TGA)

#### Przykład

```Shell
$ make
$ ./encode -in example.tga -out code.bin -k 3
$ ./decode -in code.bin -out exampleCopy.tga
$ ./different -original example.tga -copy exampleCopy.tga
```
