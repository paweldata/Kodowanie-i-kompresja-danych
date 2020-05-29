#ifndef DECODER_H
#define DECODER_H


#include <fstream>
#include <vector>
#include <map>

#include "Pixel.h"

class Decoder {
public:
    Decoder();
    void getDictionary(std::ifstream& file);
    void writeHeaderToFile(std::ifstream& inFile, std::ofstream& outFile);
    void writePixelsToFile(std::ifstream& inFile, std::ofstream& outFile);

private:
    std::map<std::string, int> redLowPassDict;
    std::map<std::string, int> redHighPassDict;

    std::map<std::string, int> greenLowPassDict;
    std::map<std::string, int> greenHighPassDict;

    std::map<std::string, int> blueLowPassDict;
    std::map<std::string, int> blueHighPassDict;

    int width;
    int height;
    uint8_t size;

    std::vector<Pixel> getImage(std::ifstream& file);
    static std::string decToBin(int value, uint8_t size);
};


#endif //DECODER_H
