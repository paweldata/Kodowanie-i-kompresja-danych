#include <cstring>

#include "ParametersTwoInputFiles.h"

ParametersTwoInputFiles::ParametersTwoInputFiles(int argc, char **argv) {
    for (int i = 0; i < argc - 1; i++) {
        if (strcmp(argv[i], "-in1") == 0) {
            this->input1 = std::ifstream(argv[++i]);
        } else if (strcmp(argv[i], "-in2") == 0) {
            this->input2 = std::ifstream(argv[++i]);
        }
    }
}

bool ParametersTwoInputFiles::ifCorrect() {
    return (this->input1.is_open() && this->input2.is_open());
}

void ParametersTwoInputFiles::showError() {
    printf("Give parameters:\n"
           "./encode -in1 inputFile -in2 inputFile\n");
}
