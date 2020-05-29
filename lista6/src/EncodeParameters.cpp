#include <cstring>

#include "EncodeParameters.h"

EncodeParameters::EncodeParameters(int argc, char **argv) {
    for (int i = 0; i < argc - 1; i++) {
        if (strcmp(argv[i], "-in") == 0) {
            this->input = std::ifstream(argv[++i]);
        } else if (strcmp(argv[i], "-out") == 0) {
            this->output = std::ofstream(argv[++i]);
        } else if (strcmp(argv[i], "-k") == 0) {
            this->bitsNumber = strtol(argv[++i], nullptr, 10);
        }
    }
}

bool EncodeParameters::ifCorrect() {
    return (this->input.is_open()
    && this->output.is_open()
    && this->bitsNumber >= 1
    && this->bitsNumber <= 7);
}

void EncodeParameters::showError() {
    printf("Give parameters:\n"
           "./encode -in inputFile -out outputFile -k bitsNumber\n"
           "where 1 <= bitsNumber <= 7\n");
}

uint8_t EncodeParameters::getBitsNumber() const {
    return this->bitsNumber;
}
