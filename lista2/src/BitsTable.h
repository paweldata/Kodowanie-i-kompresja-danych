#ifndef BITSTABLE_H
#define BITSTABLE_H

#include <vector>
#include <bitset>

class BitsTable {
private:
    static const int size = 40;
    std::bitset<size> bits;

public:
    explicit BitsTable(int a);
    void set(uint64_t a);
    void set(int index, int value);
    uint64_t getValue();
    static int getSize();
    bool checkBit(int index);
    void moveBits(int newValue);
};

#endif //BITSTABLE_H
