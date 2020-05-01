#ifndef JPEG_LS5_H
#define JPEG_LS5_H


#include "JPEG_LS.h"

class JPEG_LS5 : public JPEG_LS {
public:
    explicit JPEG_LS5(std::string name) : JPEG_LS(name) {};
    void calculateEntropy(std::vector<std::vector<Pixel>> &image) override;
};


#endif //JPEG_LS5_H
