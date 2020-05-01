#ifndef JPEG_LS_H
#define JPEG_LS_H

#include <vector>
#include <map>

#include "Pixel.h"

class JPEG_LS {
public:
    explicit JPEG_LS(std::string name);
    virtual void calculateEntropy(std::vector<std::vector<Pixel> >& image) = 0;
    double getAllColorsEntropy();
    double getRedEntropy();
    double getGreenEntropy();
    double getBlueEntropy();
    std::string getName();

protected:
    const Pixel frame{0, 0, 0};

    double getEntropy(std::map<uint8_t, uint32_t > map);
    double getEntropy(std::map<std::vector<uint8_t>, uint32_t > map);
    std::string name;
    double allColorsEntropy;
    double redEntropy;
    double greenEntropy;
    double blueEntropy;
};

#endif //JPEG_LS_H
