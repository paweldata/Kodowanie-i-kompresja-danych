#include "Encoder.h"

#include <utility>
#include <bitset>
#include <cmath>

Encoder::Encoder(TGAImage image) {
    this->image = std::move(image);
}

void Encoder::createFilters() {
    std::vector<Pixel> pixels = image.getImage();
    int size = pixels.size();

    this->redLowPassFilter = std::vector<int>(size / 2);
    this->redHighPassFilter = std::vector<int>(size / 2);

    this->greenLowPassFilter = std::vector<int>(size / 2);
    this->greenHighPassFilter = std::vector<int>(size / 2);

    this->blueLowPassFilter = std::vector<int>(size / 2);
    this->blueHighPassFilter = std::vector<int>(size / 2);

    for (int i = 1, j = 0; i < size; i += 2, j++) {
        this->redLowPassFilter[j] = (pixels[i].red + pixels[i - 1].red) / 2;
        this->redHighPassFilter[j] = (pixels[i].red - pixels[i - 1].red) / 2;

        this->greenLowPassFilter[j] = (pixels[i].green + pixels[i - 1].green) / 2;
        this->greenHighPassFilter[j] = (pixels[i].green - pixels[i - 1].green) / 2;

        this->blueLowPassFilter[j] = (pixels[i].blue + pixels[i - 1].blue) / 2;
        this->blueHighPassFilter[j] = (pixels[i].blue - pixels[i - 1].blue) / 2;
    }
}

void Encoder::createDictionaries(int codeSize) {
    this->redLowPassDict = DictionaryTree(this->redLowPassFilter, codeSize);
    this->redHighPassDict = DictionaryTree(this->redHighPassFilter, codeSize);

    this->greenLowPassDict = DictionaryTree(this->greenLowPassFilter, codeSize);
    this->greenHighPassDict = DictionaryTree(this->greenHighPassFilter, codeSize);

    this->blueLowPassDict = DictionaryTree(this->blueLowPassFilter, codeSize);
    this->blueHighPassDict = DictionaryTree(this->blueHighPassFilter, codeSize);
}

void Encoder::writeDictionaryToFile(std::ofstream &file, uint8_t size) {
    file << size;
    int maxValue = (int)pow(2, size);
    int currValue;

    for (int i = 0; i < maxValue; i++) {
        std::string code = std::bitset<8>(i).to_string();
        code = code.substr(8-size);

        currValue = this->redLowPassDict.getValue(code);
        file.write((char*)&currValue, sizeof(int));
        currValue = this->redHighPassDict.getValue(code);
        file.write((char*)&currValue, sizeof(int));

        currValue = this->greenLowPassDict.getValue(code);
        file.write((char*)&currValue, sizeof(int));
        currValue = this->greenHighPassDict.getValue(code);
        file.write((char*)&currValue, sizeof(int));

        currValue = this->blueLowPassDict.getValue(code);
        file.write((char*)&currValue, sizeof(int));
        currValue = this->blueHighPassDict.getValue(code);
        file.write((char*)&currValue, sizeof(int));
    }
}

void Encoder::writeHeaderToFile(std::ofstream &file) {
    file.write((char*)&this->image.getHeader(), sizeof(this->image.getHeader()));
}

void Encoder::writeCodeToFile(std::ofstream &file) {
    std::string code;
    int size = this->redLowPassFilter.size();

    for (int i = 0; i < size; i++) {
        code.append(this->redLowPassDict.getCode(this->redLowPassFilter[i]));
        code.append(this->redHighPassDict.getCode(this->redHighPassFilter[i]));

        code.append(this->greenLowPassDict.getCode(this->greenLowPassFilter[i]));
        code.append(this->greenHighPassDict.getCode(this->greenHighPassFilter[i]));

        code.append(this->blueLowPassDict.getCode(this->blueLowPassFilter[i]));
        code.append(this->blueHighPassDict.getCode(this->blueHighPassFilter[i]));
    }

    int codeSize = code.size();

    while (codeSize % 8 != 0) {
        code.append("0");
        codeSize++;
    }

    for (int i = 0; i < codeSize; i += 8) {
        uint8_t value = std::bitset<8>(code.substr(i, 8)).to_ulong();
        file << value;
    }
}

const TGAImage &Encoder::getImage() const {
    return this->image;
}
