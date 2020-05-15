#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <fstream>

struct Parameters {
    std::ifstream dataFile;
    std::ofstream answerFile;
    int colorNumber;

    bool ifCorrect() {
        if (!this->dataFile.is_open() || !this->answerFile.is_open())
            return false;
        return this->colorNumber >= 0 && this->colorNumber <= 24;
    }
};

#endif //PARAMETERS_H
