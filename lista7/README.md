# Kodowanie-i-kompresja-danych
## Lista 7

#### Rozszerzony kod Hamminga

Program encode koduje plik rozrzerzonym kodem Hamminga  
Program noise z prawdopodobieństwem p zamienia na przeciwny każdy bit w pliku  
Program decode dekoduje plik zakodowany rozrzerzonym kodem Hamminga  
Program check sprawdza ile 4-bitowych bloków w obu plikach nie jest identycznych


```Shell
$ make
$ ./encode -in inputFile -out outputFile
$ ./noise -in inputFile -out outputFile -p probability
$ ./decode -in inputFile -out outputFile
$ ./check -in1 inputFile -in2 inputFile
```

#### Przykład

```Shell
$ make
$ ./encode -in text.txt -out code.bin
$ ./noise -in code.bin -out newCode.bin -p 0.05
$ ./decode -in newCode.bin -out newText.txt
$ ./check -in1 text.txt -in2 newText.txt
```
