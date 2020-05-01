#ifndef JPEG_LSNEW_H
#define JPEG_LSNEW_H


#include "JPEG_LS.h"

class JPEG_LSNew : public JPEG_LS {
public:
    explicit JPEG_LSNew(std::string name) : JPEG_LS(name) {};
    void calculateEntropy(std::vector<std::vector<Pixel>> &image) override;
};


#endif //JPEG_LSNEW_H
