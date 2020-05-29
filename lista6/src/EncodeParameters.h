#ifndef ENCODEPARAMETERS_H
#define ENCODEPARAMETERS_H


#include <fstream>

class EncodeParameters {
public:
    EncodeParameters(int argc, char** argv);
    bool ifCorrect();
    static void showError();

    uint8_t getBitsNumber() const;
    std::ifstream input;
    std::ofstream output;

private:
    uint8_t bitsNumber;
};


#endif //ENCODEPARAMETERS_H
