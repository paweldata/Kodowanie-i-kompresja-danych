#include <cstdio>
#include <fstream>
#include <vector>

#include "src/JPEG_LS.h"
#include "src/JPEG_LS1.h"
#include "src/JPEG_LS2.h"
#include "src/JPEG_LS3.h"
#include "src/JPEG_LS4.h"
#include "src/JPEG_LS5.h"
#include "src/JPEG_LS6.h"
#include "src/JPEG_LS7.h"
#include "src/JPEG_LSNew.h"

std::vector<std::vector<Pixel> > getImage(std::ifstream& dataFile);
std::vector<JPEG_LS*> createJpegVector();
void showResult(std::vector<std::vector<Pixel> > image, std::vector<JPEG_LS*> jpegLsList);

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Give filename as argument\n");
        return 0;
    }

    std::ifstream dataFile(argv[1]);

    if (!dataFile.is_open()) {
        printf("Error while opening the file %s\n", argv[1]);
        return 0;
    }

    std::vector<std::vector<Pixel> > image = getImage(dataFile);
    std::vector<JPEG_LS*> jpegLsList = createJpegVector();
    showResult(image, jpegLsList);

    return 0;
}

std::vector<std::vector<Pixel> > getImage(std::ifstream& dataFile) {
    std::vector<uint8_t> header(18);
    uint8_t currChar;

    // get header
    for (int i = 0; i < 18; i++) {
        dataFile >> std::noskipws >> currChar;
        header[i] = currChar;
    }

    // skip imageId and color map data
    int lengthToSkip = header[0] + header[7] * (header[6] * 256 + header[5]) / 8;
    for (int i = 0; i < lengthToSkip; i++)
        dataFile >> std::noskipws >> currChar;

    int width = header[12] + header[13] * 256;
    int height = header[14] + header[15] * 256;
    std::vector<std::vector<Pixel> > image(height, std::vector<Pixel>(width));

    //main loop
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            dataFile >> std::noskipws >> currChar;
            image[i][j].red = currChar;
            dataFile >> std::noskipws >> currChar;
            image[i][j].green = currChar;
            dataFile >> std::noskipws >> currChar;
            image[i][j].blue = currChar;
        }
    }

    return image;
}

std::vector<JPEG_LS*> createJpegVector() {
    std::vector<JPEG_LS*> jpegLsList(8);

    JPEG_LS1* jpegLs1 = new JPEG_LS1("JPEG_LS1");
    jpegLsList[0] = jpegLs1;
    JPEG_LS2* jpegLs2 = new JPEG_LS2("JPEG_LS2");
    jpegLsList[1] = jpegLs2;
    JPEG_LS3* jpegLs3 = new JPEG_LS3("JPEG_LS3");
    jpegLsList[2] = jpegLs3;
    JPEG_LS4* jpegLs4 = new JPEG_LS4("JPEG_LS4");
    jpegLsList[3] = jpegLs4;
    JPEG_LS5* jpegLs5 = new JPEG_LS5("JPEG_LS5");
    jpegLsList[4] = jpegLs5;
    JPEG_LS6* jpegLs6 = new JPEG_LS6("JPEG_LS6");
    jpegLsList[5] = jpegLs6;
    JPEG_LS7* jpegLs7 = new JPEG_LS7("JPEG_LS7");
    jpegLsList[6] = jpegLs7;
    JPEG_LSNew* jpegLsNew = new JPEG_LSNew("JPEG_LSNew");
    jpegLsList[7] = jpegLsNew;

    return jpegLsList;
}

void showResult(std::vector<std::vector<Pixel> > image, std::vector<JPEG_LS*> jpegLsList) {
    JPEG_LS* bestAllColors = jpegLsList[0];
    JPEG_LS* bestRed = jpegLsList[0];
    JPEG_LS* bestGreen = jpegLsList[0];
    JPEG_LS* bestBlue = jpegLsList[0];

    printf("name\t\tall\t\tred\t\tgreen\t\tblue\n");

    for (JPEG_LS* jpeg : jpegLsList) {
        jpeg->calculateEntropy(image);

        if (jpeg->getAllColorsEntropy() < bestAllColors->getAllColorsEntropy())
            bestAllColors = jpeg;

        if (jpeg->getRedEntropy() < bestRed->getRedEntropy())
            bestRed = jpeg;

        if (jpeg->getGreenEntropy() < bestGreen->getGreenEntropy())
            bestGreen = jpeg;

        if (jpeg->getBlueEntropy() < bestBlue->getBlueEntropy())
            bestBlue = jpeg;

        printf("%s\t%f\t%f\t%f\t%f\n", jpeg->getName().c_str(), jpeg->getAllColorsEntropy(),
               jpeg->getRedEntropy(), jpeg->getGreenEntropy(), jpeg->getBlueEntropy());
    }

    printf("Best in all colors : %s\n", bestAllColors->getName().c_str());
    printf("Best in red : %s\n", bestRed->getName().c_str());
    printf("Best in green : %s\n", bestGreen->getName().c_str());
    printf("Best in blue : %s\n", bestBlue->getName().c_str());
}
