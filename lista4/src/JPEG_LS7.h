#ifndef JPEG_LS7_H
#define JPEG_LS7_H


#include "JPEG_LS.h"

class JPEG_LS7 : public JPEG_LS {
public:
    explicit JPEG_LS7(std::string name) : JPEG_LS(name) {};
    void calculateEntropy(std::vector<std::vector<Pixel>> &image) override;
};


#endif //JPEG_LS7_H
