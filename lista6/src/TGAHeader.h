#ifndef TGAHEADER_H
#define TGAHEADER_H

#pragma pack(push, 1)

#include <cstdint>

struct TGAHeader {
    uint8_t idLength;
    uint8_t colorMapType;
    uint8_t imageType;

    uint16_t colorMapEntryIndex;
    uint16_t colorMapLength;
    uint8_t colorMapSize;

    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
    uint8_t pixelBits;
    uint8_t descriptor;
};
#pragma pack(pop)

#endif //TGAHEADER_H
