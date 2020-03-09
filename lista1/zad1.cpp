//by Paweł Data
#include <cstdio>
#include <fstream>
#include <map>
#include <cmath>

double calculateEntropy(std::map<char, int>&map, int size) {
    std::map<char, int>::iterator it;
    double answer = 0;

    for (it = map.begin(); it != map.end(); it++)
        answer += it->second * log2(it->second);

    return - (answer / size - log2(size));
}

double calculateConditionalEntropy(std::map<char, int>&singleChars, std::map<std::string, int>&doubleChars, int size) {
    std::map<std::string, int>::iterator it;
    double answer = 0;

    for (it = doubleChars.begin(); it != doubleChars.end(); it++)
        if (singleChars[it->first[0]] != 0)
            answer += it->second *( log2(it->second) - log2(singleChars[it->first[0]]));

    return - (answer / size);
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Give filename as argument");
        return 0;
    }

    std::ifstream file;
    file.open(argv[1]);

    if (!file) {
        printf("Error while opening the file %s", argv[1]);
        return 0;
    }

    std::map<char, int> randomVariables;
    std::map<std::string, int> conditionalRandomVariables;

    char currentChar = 0;
    char previousChar = 0;
    std::string doubleChar = "aa";
    int size = 0;

    while (file >> std::noskipws >> currentChar) {
        randomVariables[currentChar]++;

        doubleChar[0] = previousChar;
        doubleChar[1] = currentChar;
        conditionalRandomVariables[doubleChar]++;

        previousChar = currentChar;
        size++;
    }

    double entropy = calculateEntropy(randomVariables, size);
    double conditionalEntropy = calculateConditionalEntropy(randomVariables, conditionalRandomVariables, size);

    printf("Entropy : %f\n", entropy);
    printf("Conditional entropy : %f\n", conditionalEntropy);
    printf("Difference : %f\n", entropy - conditionalEntropy);

    file.close();
    return 0;
}
