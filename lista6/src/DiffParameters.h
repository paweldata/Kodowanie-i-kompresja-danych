#ifndef DIFFPARAMETERS_H
#define DIFFPARAMETERS_H


#include <fstream>

class DiffParameters {
public:
    DiffParameters(int argc, char** argv);
    bool ifCorrect();
    static void showError();

    std::ifstream original;
    std::ifstream copy;
};


#endif //DIFFPARAMETERS_H
