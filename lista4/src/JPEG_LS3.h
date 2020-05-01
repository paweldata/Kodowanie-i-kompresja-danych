#ifndef JPEG_LS3_H
#define JPEG_LS3_H


#include "JPEG_LS.h"

class JPEG_LS3 : public JPEG_LS {
public:
    explicit JPEG_LS3(std::string name) : JPEG_LS(name) {};
    void calculateEntropy(std::vector<std::vector<Pixel>> &image) override;
};


#endif //JPEG_LS3_H
