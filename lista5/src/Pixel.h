#ifndef PIXEL_H
#define PIXEL_H

#include <cstdint>

struct Pixel {
    uint8_t red;
    uint8_t green;
    uint8_t blue;

    bool theSameValues(Pixel p) {
        return this->red == p.red && this->green == p.green && this->blue == p.blue;
    }
};

#endif //PIXEL_H
