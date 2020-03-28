//By Pawel Data
#include <fstream>
#include <map>

#include "src/BitsTable.h"
#include "src/codingAnalysis.h"

void setValue(BitsTable& upLimit, BitsTable& downLimit, uint64_t  sum, uint64_t  count, int currCharValue);
bool checkFirstBit(BitsTable& upLimit, BitsTable& downLimit);
bool checkSmallRange(BitsTable& upLimit, BitsTable& downLimit);
void updateLimitsAndSendCode(BitsTable& upLimit, BitsTable& downLimit, std::bitset<8>& answer,
                             int& answerIndex, std::ofstream& answerFile, int size, int& scale);
void trySendCode(std::bitset<8>& answer,int& answerIndex, std::ofstream& answerFile);
void sendLastCode(BitsTable downLimit, std::bitset<8> answer, int& answerIndex, std::ofstream& file, int scale);

void setValue(BitsTable& upLimit, BitsTable& downLimit, uint64_t  sum, uint64_t  count, int currCharValue) {
    uint64_t value = 0;
    uint64_t downLimitValue = downLimit.getValue();

    value = downLimitValue + ( (upLimit.getValue() - downLimitValue + 1) * count  ) / sum;
    downLimit.set(value);
    value = downLimitValue + ( (upLimit.getValue() - downLimitValue + 1) * (count + currCharValue)  ) / sum - 1;
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

void updateLimitsAndSendCode(BitsTable& upLimit, BitsTable& downLimit, std::bitset<8>& answer,
        int& answerIndex, std::ofstream& answerFile, int size, int& scale) {
    while (checkFirstBit(upLimit, downLimit) || checkSmallRange(upLimit, downLimit)) {
        if (checkFirstBit(upLimit, downLimit)) {

            answer.set(answerIndex++, upLimit.checkBit(size - 1));
            trySendCode(answer, answerIndex, answerFile);

            while (scale > 0) {
                answer.set(answerIndex++, 1 - upLimit.checkBit(size - 1));
                trySendCode(answer, answerIndex, answerFile);
                scale--;
            }

            upLimit.moveBits(1);
            downLimit.moveBits(0);
        }

        if (checkSmallRange(upLimit, downLimit)) {
            upLimit.moveBits(1);
            downLimit.moveBits(0);

            upLimit.set(size - 1, 1);
            downLimit.set(size - 1, 0);

            scale++;
        }
    }
}

void trySendCode(std::bitset<8>& answer,int& answerIndex, std::ofstream& answerFile) {
    if (answerIndex == 8) {
        std::uint8_t a = answer.to_ulong();
        answerFile << a;
        answerIndex = 0;
    }
}

void sendLastCode(BitsTable downLimit, std::bitset<8> answer, int& answerIndex, std::ofstream& file, int scale) {
    int size = BitsTable::getSize();

    answer.set(answerIndex++, downLimit.checkBit(size - 1));
    trySendCode(answer, answerIndex, file);

    while (scale > 0) {
        answer.set(answerIndex++, 1 - downLimit.checkBit(size - 1));
        trySendCode(answer, answerIndex, file);
        scale--;
    }

    for (int i = size - 2; i >= 0; i--) {
        answer.set(answerIndex++, downLimit.checkBit(i));
        trySendCode(answer, answerIndex, file);
    }

    if (answerIndex > 0) {
        while (answerIndex < 8)
            answer.set(answerIndex++, false);
        trySendCode(answer, answerIndex, file);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Give filenames as argument\n"
               "./encode file_to_encode result\n");
        return 0;
    }

    std::ifstream dataFile;
    dataFile.open(argv[1]);

    if (!dataFile) {
        printf("Error while opening the file %s", argv[1]);
        return 0;
    }

    std::ofstream answerFile;
    answerFile.open(argv[2], std::ios::out | std::ios::binary);

    std::map<char, int> charMap;
    std::map<char, int>::iterator it;
    for (int i = 0; i < 257; i++)
        charMap[i]++;

    BitsTable upLimit(1);
    BitsTable downLimit(0);

    char currentChar = 0;
    uint64_t count = 0;
    uint64_t sum = 256;
    int scale = 0;
    int size = BitsTable::getSize();
    int answerIndex = 0;
    std::bitset<8> answer;

    //main loop
    while (dataFile >> std::noskipws >> currentChar) {
        count = 0;
        it = charMap.begin();

        while (it->first != currentChar) {
            count += it->second;
            it++;
        }

        setValue(upLimit, downLimit, sum, count, charMap[currentChar]);
        updateLimitsAndSendCode(upLimit, downLimit, answer, answerIndex, answerFile, size, scale);

        charMap[it->first]++;
        sum++;
    }

    //file ends, send char(256) (end char)
    it = charMap.begin();
    count = 0;
    while (it->first != char(256)) {
        count += it->second;
        it++;
    }

    setValue(upLimit, downLimit, sum, count, charMap[char(256)]);
    updateLimitsAndSendCode(upLimit, downLimit, answer, answerIndex, answerFile, size, scale);

    //send downLimit
    sendLastCode(downLimit, answer, answerIndex, answerFile, scale);

    dataFile.close();
    answerFile.close();

    printf("Entropy : %f\n",codingAnalysis::getEntropy(charMap, sum));
    double compressionRate = codingAnalysis::getCompressionRate(argv[1], argv[2]);
    printf("Average codeword length : %f\n", 8.0 / compressionRate);
    printf("Compression Rate : %f\n", compressionRate);

    return 0;
}
