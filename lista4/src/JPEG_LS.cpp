#include <cmath>

#include "JPEG_LS.h"

JPEG_LS::JPEG_LS(std::string name) {
    this->name = name;
}

double JPEG_LS::getAllColorsEntropy() {
    return this->allColorsEntropy;
}

double JPEG_LS::getRedEntropy() {
    return this->redEntropy;
}

double JPEG_LS::getGreenEntropy() {
    return this->greenEntropy;
}

double JPEG_LS::getBlueEntropy() {
    return this->blueEntropy;
}

std::string JPEG_LS::getName() {
    return this->name;
}

double JPEG_LS::getEntropy(std::map<uint8_t, uint32_t > map) {
    std::map<uint8_t , uint32_t>::iterator it;
    double answer = 0;
    int sum = 0;

    for (it = map.begin(); it != map.end(); it++) {
        answer += it->second * log2(it->second);
        sum += it->second;
    }

    return - (answer / sum - log2(sum));
}

double JPEG_LS::getEntropy(std::map<std::vector<uint8_t>, uint32_t > map) {
    std::map<std::vector<uint8_t> , uint32_t>::iterator it;
    double answer = 0;
    int sum = 0;

    for (it = map.begin(); it != map.end(); it++) {
        answer += it->second * log2(it->second);
        sum += it->second;
    }

    return - (answer / sum - log2(sum));
}
