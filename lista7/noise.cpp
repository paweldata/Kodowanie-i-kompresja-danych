#include <bitset>
#include <random>

#include "src/ParametersNoise.h"

int main(int argc, char** argv) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> randFrom0To1(0.0, 1.0);
    ParametersNoise param(argc, argv);

    if (!param.ifCorrect()) {
        ParametersNoise::showError();
        return 1;
    }

    uint8_t byte;

    while (param.input >> std::noskipws >> byte) {
        std::bitset<8> currBite(byte);

        for (int i = 0; i < 8; i++) {
            if (param.probability >= randFrom0To1(generator))
                currBite.flip(i);
        }

        uint8_t newByte = currBite.to_ulong();
        param.output << newByte;
    }

    param.input.close();
    param.output.close();

    return 0;
}