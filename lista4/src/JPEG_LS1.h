#ifndef JPEG_LS1_H
#define JPEG_LS1_H


#include "JPEG_LS.h"

class JPEG_LS1 : public JPEG_LS {
public:
    explicit JPEG_LS1(std::string name) : JPEG_LS(name) {};
    void calculateEntropy(std::vector<std::vector<Pixel>> &image) override;
};


#endif //JPEG_LS1_H
