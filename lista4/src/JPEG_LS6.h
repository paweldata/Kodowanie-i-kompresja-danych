#ifndef JPEG_LS6_H
#define JPEG_LS6_H


#include "JPEG_LS.h"

class JPEG_LS6 : public JPEG_LS {
public:
    explicit JPEG_LS6(std::string name) : JPEG_LS(name) {};
    void calculateEntropy(std::vector<std::vector<Pixel>> &image) override;
};


#endif //JPEG_LS6_H
