#include <bitset>

#include "src/ParametersTwoInputFiles.h"

int checkDifference(uint8_t b1, uint8_t b2);

int main(int argc, char** argv) {
    ParametersTwoInputFiles param(argc, argv);

    if (!param.ifCorrect()) {
        ParametersTwoInputFiles::showError();
        return 1;
    }

    uint8_t byte1;
    uint8_t byte2;
    int differenceCounter = 0;

    while (param.input1 >> std::noskipws >> byte1 && param.input2 >> std::noskipws >> byte2)
        differenceCounter += checkDifference(byte1, byte2);

    printf("Difference counter = %d\n", differenceCounter);

    param.input1.close();
    param.input2.close();

    return 0;
}

int checkDifference(uint8_t b1, uint8_t b2) {
    std::string byte1 = std::bitset<8>(b1).to_string();
    std::string byte2 = std::bitset<8>(b2).to_string();
    int counter = 0;

    for (int i = 0; i < 8; i+= 4) {
        if (byte1.substr(i, 4) != byte2.substr(i, 4))
            counter++;
    }

    return counter;
}
