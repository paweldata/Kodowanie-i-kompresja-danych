#include <bitset>

#include "src/ParametersTwoFiles.h"

uint8_t getCode(uint8_t byte, int& twoErrorsCounter);

int main(int argc, char** argv) {
    ParametersTwoFiles param(argc, argv);

    if (!param.ifCorrect()) {
        ParametersTwoFiles::showError();
        return 1;
    }

    uint8_t byte1;
    uint8_t byte2;
    int twoErrorsCounter = 0;

    while (param.input >> std::noskipws >> byte1 && param.input >> std::noskipws >> byte2) {
        uint8_t result = getCode(byte1, twoErrorsCounter) + 16 * getCode(byte2, twoErrorsCounter);
        param.output << result;
    }

    printf("Two errors number = %d\n", twoErrorsCounter);

    param.input.close();
    param.output.close();

    return 0;
}

uint8_t getCode(uint8_t byte, int& twoErrorsCounter) {
    int x[4][8] = {{1, 0, 1, 0, 1, 0, 1, 0},
                   {0, 1, 1, 0, 0, 1, 1, 0},
                   {0, 0, 0, 1, 1, 1, 1, 0},
                   {1, 1, 1, 1, 1, 1, 1, 1}};
    std::bitset<8> value(byte);
    std::bitset<4> product;

    for (int i = 0; i < 4; i++) {
        uint8_t sum = 0;
        for (int j = 0; j < 8; j++)
            sum += x[i][j] * value[j];
        (sum % 2 == 0) ? product.reset(i) : product.set(i);
    }

    // check parity bit
    if (value.count() % 2 == 0) {
        // parity bit is correct
        if (product.to_ulong() % 8 != 0)
            // parity bit is correct, other number show error, double bit error
            twoErrorsCounter++;
    } else {
        // parity bit is incorrect
        uint8_t index = product.to_ulong() % 8;
        if (index > 0) {
            // other number show error, fix it
            value.flip(index - 1);
        }
    }

    return value.test(2) * 1 + value.test(4) * 2 + value.test(5) * 4 + value.test(6) * 8;
}
