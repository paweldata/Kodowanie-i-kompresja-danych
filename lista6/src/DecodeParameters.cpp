#include <cstring>

#include "DecodeParameters.h"

DecodeParameters::DecodeParameters(int argc, char **argv) {
    for (int i = 0; i < argc - 1; i++) {
        if (strcmp(argv[i], "-in") == 0) {
            this->input = std::ifstream(argv[++i]);
        } else if (strcmp(argv[i], "-out") == 0) {
            this->output = std::ofstream(argv[++i]);
        }
    }
}

bool DecodeParameters::ifCorrect() {
    return (this->input.is_open() && this->output.is_open());
}

void DecodeParameters::showError() {
    printf("Give parameters:\n"
           "./decode -in inputFile -out outputFile\n");
}
