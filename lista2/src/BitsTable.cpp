#include <iostream>
#include "BitsTable.h"

BitsTable::BitsTable(int a) {
    if (a) {
        this->bits.set();
    } else {
        this->bits.reset();
    }
}

void BitsTable::set(uint64_t a) {
    this->bits.reset();
    for (int i = 0; a > 0; i++) {
        this->bits[i] = a % 2;
        a /= 2;
    }
}

void BitsTable::set(int index, int value) {
    this->bits[index] = value;
}

uint64_t BitsTable::getValue() {
    uint64_t answer = 0;

    for (int i = BitsTable::size - 1; i >= 0; i--) {
        answer *= 2;
        answer += this->bits[i];
    }

    return answer;
}

int BitsTable::getSize() {
    return BitsTable::size;
}

bool BitsTable::checkBit(int index) {
    return this->bits.test(index);
}

void BitsTable::moveBits(int newValue) {
    for (int i = BitsTable::size - 1; i > 0; i--)
        this->bits[i] = this->bits[i - 1];

    this->bits[0] = newValue;
}
