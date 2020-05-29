#include <cmath>

#include "src/DiffParameters.h"
#include "src/TGAImage.h"
#include "src/Encoder.h"

int main(int argc, char** argv) {
    DiffParameters param = DiffParameters(argc, argv);

    if (!param.ifCorrect()) {
        DiffParameters::showError();
        return 1;
    }

    Encoder original = Encoder(TGAImage(param.original));
    Encoder copy = Encoder(TGAImage(param.copy));

    const std::vector<Pixel>& originalImage = original.getImage().getImage();
    const std::vector<Pixel>& newImage = copy.getImage().getImage();
    int size = originalImage.size();
    uint64_t valueToRedMse = 0;
    uint64_t valueToGreenMse = 0;
    uint64_t valueToBlueMse = 0;
    uint64_t valueToSnr = 0;

    for (int i = 0; i < size; i++) {
         valueToRedMse += pow(originalImage[i].red - newImage[i].red, 2);
        valueToGreenMse += pow(originalImage[i].green - newImage[i].green, 2);
        valueToBlueMse += pow(originalImage[i].blue - newImage[i].blue, 2);

        valueToSnr += originalImage[i].red * newImage[i].red +
                originalImage[i].green * newImage[i].green +
                originalImage[i].blue * newImage[i].blue;
    }

    double mseRed = double(valueToRedMse) / (size);
    double mseGreen = double(valueToGreenMse) / (size);
    double mseBlue = double(valueToBlueMse) / (size);
    double mse = (mseRed + mseGreen + mseBlue) / 3;
    double snr = (double(valueToSnr) / (size * 3)) / mse;

    printf("MSE = %f\n", mse);
    printf("MSE (r) = %f\n", mseRed);
    printf("MSE (g) = %f\n", mseGreen);
    printf("MSE (b) = %f\n", mseBlue);
    printf("SNR = %f (%fdB)\n", snr, 10 * log10(snr));

    param.original.close();
    param.copy.close();

    return 0;
}
