#include "Original.h"

void Original::calculateEntropy(std::vector<std::vector<Pixel>> &image) {
    std::map<std::vector<uint8_t>, uint32_t> allColorsMap;
    std::map<uint8_t, uint32_t> redMap;
    std::map<uint8_t, uint32_t> greenMap;
    std::map<uint8_t, uint32_t> blueMap;

    int height = image.size();
    int width = image[0].size();

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Pixel currPixel = image[i][j];

            redMap[currPixel.red]++;
            greenMap[currPixel.green]++;
            blueMap[currPixel.blue]++;
            allColorsMap[std::vector<uint8_t>{currPixel.red, currPixel.green, currPixel.blue}]++;
        }
    }

    this->allColorsEntropy = this->getEntropy(allColorsMap);
    this->redEntropy = this->getEntropy(redMap);
    this->greenEntropy = this->getEntropy(greenMap);
    this->blueEntropy = this->getEntropy(blueMap);
}
