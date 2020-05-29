#include <cmath>
#include <bitset>

#include "Decoder.h"
#include "TGAHeader.h"

Decoder::Decoder() {
    this->redLowPassDict = std::map<std::string, int>();
    this->redHighPassDict = std::map<std::string, int>();

    this->greenLowPassDict = std::map<std::string, int>();
    this->greenHighPassDict = std::map<std::string, int>();

    this->blueLowPassDict = std::map<std::string, int>();
    this->blueHighPassDict = std::map<std::string, int>();
}

void Decoder::getDictionary(std::ifstream &file) {
    file >> std::noskipws >> this->size;
    int value;

    int maxValue = (int)pow(2, this->size);

    for (int i = 0; i < maxValue; i++) {
        std::string code = Decoder::decToBin(i, this->size);

        file.read((char*)&value, sizeof(value));
        this->redLowPassDict[code] = value;
        file.read((char*)&value, sizeof(value));
        this->redHighPassDict[code] = value;

        file.read((char*)&value, sizeof(value));
        this->greenLowPassDict[code] = value;
        file.read((char*)&value, sizeof(value));
        this->greenHighPassDict[code] = value;

        file.read((char*)&value, sizeof(value));
        this->blueLowPassDict[code] = value;
        file.read((char*)&value, sizeof(value));
        this->blueHighPassDict[code] = value;
    }
}

std::string Decoder::decToBin(int value, uint8_t size) {
    std::string result(size, '0');

    for (int i = size - 1; value > 0; i--) {
        result[i] = char((value % 2) + 48);
        value /= 2;
    }

    return result;
}

void Decoder::writeHeaderToFile(std::ifstream &inFile, std::ofstream &outFile) {
    TGAHeader header = TGAHeader();
    inFile.read(reinterpret_cast<char*>(&header), sizeof(header));

    this->height = header.height;
    this->width = header.width;

    outFile.write((char*)&header, sizeof(header));
}

void Decoder::writePixelsToFile(std::ifstream& inFile, std::ofstream& outFile) {
    std::vector<Pixel> pixels = this->getImage(inFile);
    int imageSize = pixels.size();

    for (int i = 0; i < imageSize; i++) {
        outFile << pixels[i].red;
        outFile << pixels[i].green;
        outFile << pixels[i].blue;
    }
}

std::vector<Pixel> Decoder::getImage(std::ifstream& file) {
    int imageSize = this->width * this->height;
    std::vector<Pixel> pixels(imageSize);

    std::string code;
    std::string currCode;

    int redLowValue;
    int redHighValue;
    int greenLowValue;
    int greenHighValue;
    int blueLowValue;
    int blueHighValue;

    uint8_t fileValue = 0;
    while (file >> std::noskipws >> fileValue)
        code.append(std::bitset<8>(fileValue).to_string());

    for (int i = 0, j = 0; i < imageSize; i += 2) {
        redLowValue = this->redLowPassDict[code.substr(j, this->size)];
        j += this->size;
        redHighValue = this->redHighPassDict[code.substr(j, this->size)];
        j += this->size;

        greenLowValue = this->greenLowPassDict[code.substr(j, this->size)];
        j += this->size;
        greenHighValue = this->greenHighPassDict[code.substr(j, this->size)];
        j += this->size;

        blueLowValue = this->blueLowPassDict[code.substr(j, this->size)];
        j += this->size;
        blueHighValue = this->blueHighPassDict[code.substr(j, this->size)];
        j += this->size;

        pixels[i].red = (uint8_t)(std::max(0, std::min(255, redLowValue - redHighValue)));
        pixels[i].green = (uint8_t)(std::max(0, std::min(255, greenLowValue - greenHighValue)));
        pixels[i].blue = (uint8_t)(std::max(0, std::min(255, blueLowValue - blueHighValue)));

        pixels[i + 1].red = (uint8_t)(std::max(0, std::min(255, redLowValue + redHighValue)));
        pixels[i + 1].green = (uint8_t)(std::max(0, std::min(255, greenLowValue + greenHighValue)));
        pixels[i + 1].blue = (uint8_t)(std::max(0, std::min(255, blueLowValue + blueHighValue)));
    }

    return pixels;
}
