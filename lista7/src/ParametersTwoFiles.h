#ifndef PARAMETERSTWOFILES_H
#define PARAMETERSTWOFILES_H


#include <fstream>

class ParametersTwoFiles {
public:
    std::ifstream input;
    std::ofstream output;

    ParametersTwoFiles(int argc, char** argv);
    bool ifCorrect();
    static void showError();
};


#endif //PARAMETERSTWOFILES_H
