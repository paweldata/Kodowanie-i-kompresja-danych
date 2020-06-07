#ifndef PARAMETERSTWOINPUTFILES_H
#define PARAMETERSTWOINPUTFILES_H


#include <fstream>

class ParametersTwoInputFiles {
public:
    std::ifstream input1;
    std::ifstream input2;

    ParametersTwoInputFiles(int argc, char** argv);
    bool ifCorrect();
    static void showError();

};


#endif //PARAMETERSTWOINPUTFILES_H
