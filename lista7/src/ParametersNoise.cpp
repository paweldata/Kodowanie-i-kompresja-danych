#include <cstring>

#include "ParametersNoise.h"

ParametersNoise::ParametersNoise(int argc, char **argv) {
    for (int i = 0; i < argc - 1; i++) {
        if (strcmp(argv[i], "-in") == 0) {
            this->input = std::ifstream(argv[++i]);
        } else if (strcmp(argv[i], "-out") == 0) {
            this->output = std::ofstream(argv[++i]);
        } else if (strcmp(argv[i], "-p") == 0) {
            this->probability = std::stod(argv[++i]);
        }
    }
}

bool ParametersNoise::ifCorrect() {
    return (this->input.is_open() && this->output.is_open() && probability >= 0 && probability <= 1);
}

void ParametersNoise::showError() {
    printf("Give parameters:\n"
           "./encode -in inputFile -out outputFile -p probability\n"
           "where 0 <= probability <= 1\n");
}
