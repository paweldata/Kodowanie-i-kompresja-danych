#ifndef DECODEPARAMETERS_H
#define DECODEPARAMETERS_H


#include <fstream>

class DecodeParameters {
public:
    DecodeParameters(int argc, char** argv);
    bool ifCorrect();
    static void showError();

    std::ifstream input;
    std::ofstream output;
};


#endif //DECODEPARAMETERS_H
