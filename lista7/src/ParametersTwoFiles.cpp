#include <cstring>

#include "ParametersTwoFiles.h"

ParametersTwoFiles::ParametersTwoFiles(int argc, char **argv) {
    for (int i = 0; i < argc - 1; i++) {
        if (strcmp(argv[i], "-in") == 0) {
            this->input = std::ifstream(argv[++i]);
        } else if (strcmp(argv[i], "-out") == 0) {
            this->output = std::ofstream(argv[++i]);
        }
    }
}

bool ParametersTwoFiles::ifCorrect() {
    return (this->input.is_open() && this->output.is_open());
}

void ParametersTwoFiles::showError() {
    printf("Give parameters:\n"
           "./encode -in inputFile -out outputFile\n");
}
