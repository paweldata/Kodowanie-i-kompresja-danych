#ifndef JPEG_LS4_H
#define JPEG_LS4_H


#include "JPEG_LS.h"

class JPEG_LS4 : public JPEG_LS {
public:
    explicit JPEG_LS4(std::string name) : JPEG_LS(name) {};
    void calculateEntropy(std::vector<std::vector<Pixel>> &image) override;
};


#endif //JPEG_LS4_H
