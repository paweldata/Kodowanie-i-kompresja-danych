#include "JPEG_LS2.h"

void JPEG_LS2::calculateEntropy(std::vector<std::vector<Pixel>>& image) {
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

            uint8_t red = currPixel.red - north.red;
            uint8_t green = currPixel.green - north.green;
            uint8_t blue = currPixel.blue - north.blue;

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
