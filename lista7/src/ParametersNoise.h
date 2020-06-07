#ifndef PARAMETERSNOISE_H
#define PARAMETERSNOISE_H


#include <fstream>

class ParametersNoise {
public:
    std::ifstream input;
    std::ofstream output;
    double probability;

    ParametersNoise(int argc, char** argv);
    bool ifCorrect();
    static void showError();
};


#endif //PARAMETERSNOISE_H
