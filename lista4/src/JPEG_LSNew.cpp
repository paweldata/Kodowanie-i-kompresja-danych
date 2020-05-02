#include "JPEG_LSNew.h"

void JPEG_LSNew::calculateEntropy(std::vector<std::vector<Pixel>> &image) {
    std::map<std::vector<uint8_t>, uint32_t> allColorsMap;
    std::map<uint8_t, uint32_t> redMap;
    std::map<uint8_t, uint32_t> greenMap;
    std::map<uint8_t, uint32_t> blueMap;

    int height = image.size();
    int width = image[0].size();

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Pixel currPixel = image[i][j];
            Pixel north = (i == 0) ? this->frame : image[i - 1][j];
            Pixel west = (j == 0) ? this->frame : image[i][j - 1];
            Pixel northwest = (i == 0 || j == 0) ? this->frame : image[i - 1][j - 1];

            uint8_t red = currPixel.red;
            uint8_t green = currPixel.green;
            uint8_t blue = currPixel.blue;

            if (northwest.red >= std::max(north.red, west.red)) {
                red -= std::max(north.red, west.red);
            } else if (northwest.red <= std::min(north.red, west.red)) {
                red -= std::min(north.red, west.red);
            } else {
                red -= north.red + west.red - northwest.red;
            }

            if (northwest.green >= std::max(north.green, west.green)) {
                green -= std::max(north.green, west.green);
            } else if (northwest.green <= std::min(north.green, west.green)) {
                green -= std::min(north.green, west.green);
            } else {
                green -= north.green + west.green - northwest.green;
            }

            if (northwest.blue >= std::max(north.blue, west.blue)) {
                blue -= std::max(north.blue, west.blue);
            } else if (northwest.blue <= std::min(north.blue, west.blue)) {
                blue -= std::min(north.blue, west.blue);
            } else {
                blue -= north.blue + west.blue - northwest.blue;
            }

            redMap[red]++;
            greenMap[green]++;
            blueMap[blue]++;
            allColorsMap[std::vector<uint8_t>{red, green, blue}]++;
        }
    }

    this->allColorsEntropy = this->getEntropy(allColorsMap);
    this->redEntropy = this->getEntropy(redMap);
    this->greenEntropy = this->getEntropy(greenMap);
    this->blueEntropy = this->getEntropy(blueMap);
}
