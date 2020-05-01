#ifndef JPEG_LS2_H
#define JPEG_LS2_H


#include "JPEG_LS.h"

class JPEG_LS2 : public JPEG_LS {
public:
    explicit JPEG_LS2(std::string name) : JPEG_LS(name) {};
    void calculateEntropy(std::vector<std::vector<Pixel>> &image) override;
};


#endif //JPEG_LS2_H