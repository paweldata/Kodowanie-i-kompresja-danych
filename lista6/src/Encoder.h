#ifndef ENCODER_H
#define ENCODER_H


#include "TGAImage.h"
#include "DictionaryTree.h"

class Encoder {
public:
    explicit Encoder(TGAImage image);
    void createFilters();
    void createDictionaries(int codeSize);
    void writeDictionaryToFile(std::ofstream& file, uint8_t size);
    void writeHeaderToFile(std::ofstream& file);
    void writeCodeToFile(std::ofstream& file);

    const TGAImage &getImage() const;

private:
    TGAImage image;

    std::vector<int> redLowPassFilter;
    std::vector<int> redHighPassFilter;
    DictionaryTree redLowPassDict;
    DictionaryTree redHighPassDict;

    std::vector<int> greenLowPassFilter;
    std::vector<int> greenHighPassFilter;
    DictionaryTree greenLowPassDict;
    DictionaryTree greenHighPassDict;

    std::vector<int> blueLowPassFilter;
    std::vector<int> blueHighPassFilter;
    DictionaryTree blueLowPassDict;
    DictionaryTree blueHighPassDict;
};


#endif //ENCODER_H
