#ifndef NOCODING_H
#define NOCODING_H


#include "JPEG_LS.h"

class Original : public JPEG_LS {
public:
    explicit Original(std::string name) : JPEG_LS(name) {};
    void calculateEntropy(std::vector<std::vector<Pixel>> &image) override;
};


#endif //NOCODING_H
