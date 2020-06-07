#include <bitset>

#include "src/ParametersTwoFiles.h"

std::bitset<16> getCode(std::bitset<8> byte);

int main(int argc, char** argv) {
    ParametersTwoFiles param(argc, argv);

    if (!param.ifCorrect()) {
        ParametersTwoFiles::showError();
        return 1;
    }

    uint8_t byte;

    while (param.input >> std::noskipws >> byte) {
        std::bitset<16> newTwoBytes(getCode(std::bitset<8>(byte)));
        param.output.write((char*)&newTwoBytes, 2);
    }

    param.input.close();
    param.output.close();

    return 0;
}

std::bitset<16> getCode(std::bitset<8> byte) {
    int x[4][8] = {{1, 1, 1, 0, 0, 0, 0, 1},
                   {1, 0, 0, 1, 1, 0, 0, 1},
                   {0, 1, 0, 1, 0, 1, 0, 1},
                   {1, 1, 0, 1, 0, 0, 1, 0}};
    std::bitset<16> result;

    for (int i = 0; i < 16; i++) {
        uint8_t move = (i >= 8) ? 4 : 0;
        uint8_t sum = 0;
        for (int j = 0; j < 4; j++)
            sum += x[j][i % 8] * byte[move + j];
        (sum % 2 == 0) ? result.reset(i) : result.set(i);
    }

    return result;
}
