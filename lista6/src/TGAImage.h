#ifndef TGAIMAGE_H
#define TGAIMAGE_H


#include <fstream>
#include <vector>

#include "TGAHeader.h"
#include "Pixel.h"
#include "DictionaryTree.h"

class TGAImage {
public:
    TGAImage() {}
    explicit TGAImage(std::ifstream &file);

    const std::vector<Pixel> &getImage() const;
    const TGAHeader &getHeader() const;

private:
    std::vector<Pixel> image;
    TGAHeader header;
};


#endif //TGAIMAGE_H
