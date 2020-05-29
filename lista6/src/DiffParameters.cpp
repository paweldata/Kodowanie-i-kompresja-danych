#include <cstring>

#include "DiffParameters.h"

DiffParameters::DiffParameters(int argc, char **argv) {
    for (int i = 0; i < argc - 1; i++) {
        if (strcmp(argv[i], "-original") == 0) {
            this->original = std::ifstream(argv[++i]);
        } else if (strcmp(argv[i], "-copy") == 0) {
            this->copy = std::ifstream(argv[++i]);
        }
    }
}

bool DiffParameters::ifCorrect() {
    return (this->original.is_open() && this->copy.is_open());
}

void DiffParameters::showError() {
    printf("Give parameters:\n"
           "./diff -original originalFile -copy copyFile\n");
}
