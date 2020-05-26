#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cmath>

#include "src/Parameters.h"
#include "src/TGAHeader.h"
#include "src/DictionaryTree.h"

void wrongParameters();
std::vector<std::vector<Pixel> > getImage(Parameters* parameters, TGAHeader tgaHeader);

int main(int argc, char** argv) {
    if (argc < 4) {
        wrongParameters();
        return 1;
    }

    auto* parameters = new Parameters{.dataFile = std::ifstream(argv[1]),
                                      .answerFile = std::ofstream(argv[2]),
                                      .colorNumber = (int)strtol(argv[3], nullptr, 10)};

    if (!parameters->ifCorrect()) {
        wrongParameters();
        return 1;
    }

    TGAHeader header{};
    parameters->dataFile.read(reinterpret_cast<char *>(&header), sizeof(TGAHeader));

    std::vector<std::vector<Pixel> > image = getImage(parameters, header);
    DictionaryTree dict(image, parameters->colorNumber);

    parameters->answerFile.write((char*)&header, sizeof(TGAHeader));
    uint64_t valueToMse = 0;
    uint64_t valueToSnr = 0;

    for (int i = 0; i < header.height; i++) {
        for (int j = 0; j < header.width; j++) {
            Pixel pixel = dict.getNewPixel(image[i][j]);
            parameters->answerFile << pixel.red;
            parameters->answerFile << pixel.green;
            parameters->answerFile << pixel.blue;
            valueToMse += DictionaryTree::distance(image[i][j], pixel);
            valueToSnr += pixel.red * pixel.red + pixel.green * pixel.green + pixel.blue * pixel.blue;
        }
    }

    parameters->dataFile.close();
    parameters->answerFile.close();

    double mse = double(valueToMse) / (header.height * header.width);
    double snr = (double(valueToSnr) / ((header.height * header.width))) / mse;
    printf("MSE = %f\n", mse);
    printf("SNR = %f (%fdB)\n", snr, 10 * log10(snr));
}

void wrongParameters() {
    printf("Give parameters:\n"
           "./main dataFile answerFile colorNumber\n"
           "0 <= colorNumber <= 24\n");
}

std::vector<std::vector<Pixel> > getImage(Parameters* parameters, TGAHeader tgaHeader) {
    std::vector<std::vector<Pixel> > image(tgaHeader.height, std::vector<Pixel>(tgaHeader.width));

    for (int i = 0; i < tgaHeader.height; i++) {
        for (int j = 0; j < tgaHeader.width; j++) {
            parameters->dataFile >> std::noskipws >> image[i][j].red;
            parameters->dataFile >> std::noskipws >> image[i][j].green;
            parameters->dataFile >> std::noskipws >> image[i][j].blue;
        }
    }

    return image;
}
