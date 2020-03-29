#include <iostream>
#include <fstream>
#include <map>

#include "src/BitsTable.h"
#include "src/codingAnalysis.h"

void setValue(BitsTable& upLimit, BitsTable& downLimit, uint64_t sum, uint64_t count, uint16_t currCharValue) {
    uint64_t value = 0;
    uint64_t downLimitValue = downLimit.getValue();

    value = downLimitValue +  ( (upLimit.getValue() - downLimitValue + 1) * (count - currCharValue)  ) / sum;
    downLimit.set(value);
    value = downLimitValue +  ( (upLimit.getValue() - downLimitValue + 1) * count  ) / sum - 1;
    upLimit.set(value);
}

bool checkFirstBit(BitsTable& upLimit, BitsTable& downLimit) {
    return upLimit.checkBit(BitsTable::getSize() - 1) == downLimit.checkBit(BitsTable::getSize() - 1);
}

bool checkSmallRange(BitsTable& upLimit, BitsTable& downLimit) {
    int size = BitsTable::getSize();

    return (upLimit.checkBit(size - 1) != upLimit.checkBit(size - 2)
            && downLimit.checkBit(size - 1) != downLimit.checkBit(size - 2)
            && upLimit.checkBit(size - 1) != downLimit.checkBit(size - 1));
}

void updateBitsCode(BitsTable& bitsTable, std::ifstream& file, std::bitset<8>& code, int& codeIndex) {
    if (codeIndex == 8) {
        std::uint8_t newChar;
        file >> std::noskipws >> newChar;
        code = std::bitset<8>(newChar);
        codeIndex = 0;
    }

    bitsTable.moveBits(code.test(codeIndex++));
}

void initializeCode(BitsTable& bitsTable, std::ifstream& file, std::bitset<8>& code, int& codeIndex) {
    for (int i = BitsTable::getSize() - 1 ; i >= 0; i--) {
        if (codeIndex == 8) {
            std::uint8_t newChar;
            file >> std::noskipws >> newChar;
            code = std::bitset<8>(newChar);
            codeIndex = 0;
        }

        bitsTable.set(i, code.test(codeIndex++));
    }
}

int main(int argc, char *argv[]) {
    if (argc  < 3) {
        printf("Give filenames as argument\n"
               "./encode file_to_decode result\n");
        return 0;
    }

    std::ifstream dataFile;
    dataFile.open(argv[1]);

    if (!dataFile) {
        printf("Error while opening the file %s\n", argv[1]);
        return 0;
    }

    std::ofstream answerFile;
    answerFile.open(argv[2]);

    std::map<uint16_t, int> charMap;
    std::map<uint16_t, int>::iterator it;
    for (int i = 0; i < 257; i++)
        charMap[i]++;

    BitsTable upLimit(1);
    BitsTable downLimit(0);
    BitsTable bitsCode(0);

    uint64_t count = 0;
    uint64_t sum = 257;
    uint64_t actualValue = 0;
    int codeIndex = 8;
    std::bitset<8> code;

    initializeCode(bitsCode, dataFile, code, codeIndex);

    //main loop
    while (!dataFile.eof()) {
        it = charMap.begin();
        count = it->second;

        actualValue = ( (bitsCode.getValue() - downLimit.getValue() + 1) * sum - 1 )
                / (upLimit.getValue() - downLimit.getValue() + 1);

        while (actualValue >= count) {
            it++;
            count += it->second;
        }

        if (it->first == 256)
            //end of code, stop program
            return 0;

        answerFile << char(it->first);

        setValue(upLimit, downLimit, sum, count, it->second);

        while (checkFirstBit(upLimit, downLimit) || checkSmallRange(upLimit, downLimit)) {
            if (checkFirstBit(upLimit, downLimit)) {
                upLimit.moveBits(1);
                downLimit.moveBits(0);

                updateBitsCode(bitsCode, dataFile, code, codeIndex);
            }

            if (checkSmallRange(upLimit, downLimit)) {
                upLimit.moveBits(1);
                downLimit.moveBits(0);

                updateBitsCode(bitsCode, dataFile, code, codeIndex);

                upLimit.set(BitsTable::getSize() - 1, 1);
                downLimit.set(BitsTable::getSize() - 1, 0);
                bitsCode.set(BitsTable::getSize() - 1, 1 - bitsCode.checkBit(BitsTable::getSize() - 1));
            }
        }

        charMap[it->first]++;
        sum++;
    }

    return 0;
}
