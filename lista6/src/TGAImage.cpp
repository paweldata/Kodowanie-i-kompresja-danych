#include "TGAImage.h"

TGAImage::TGAImage(std::ifstream &file) {
    this->header = TGAHeader();
    file.read(reinterpret_cast<char*>(&header), sizeof(header));

    int size = this->header.height * this->header.width;
    this->image = std::vector<Pixel>(size);

    for (int i = 0; i < size; i++) {
        file >> std::noskipws >> this->image[i].red;
        file >> std::noskipws >> this->image[i].green;
        file >> std::noskipws >> this->image[i].blue;
    }
}

const std::vector<Pixel> &TGAImage::getImage() const {
    return this->image;
}

const TGAHeader &TGAImage::getHeader() const {
    return this->header;
}
