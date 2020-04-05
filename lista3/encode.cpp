//By Pawel Data
#include <fstream>

#include "src/universalCode.h"
#include "src/codingAnalysis.h"

uint8_t binToDec(std::string number);
void sendCode(std::string& buffer, std::ofstream& answerFile, std::map<int, int>&map);

int main(int argc, char *argv[]) {
    std::string answerFileName;
    std::string dataFileName;
    std::ifstream dataFile;
    std::ofstream answerFile;
    std::string(*encode)(int) = &universalCode::encodeOmega;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            switch (argv[i][1]) {
                case 'o': encode = &universalCode::encodeOmega; break;
                case 'g': encode = &universalCode::encodeGamma; break;
                case 'd': encode = &universalCode::encodeDelta; break;
                case 'f': encode = &universalCode::encodeFib; break;
            }
        } else if (!dataFile.is_open()) {
            dataFileName = argv[i];
            dataFile.open(argv[i]);
        } else if (!answerFile.is_open()) {
            answerFileName = argv[i];
            answerFile.open(argv[i]);
        }
    }

    if (!dataFile.is_open() || !answerFile.is_open()) {
        printf("Give filenames as argument\n"
               "./encode file_to_encode result\n"
               "optional parameters: -o (omega) -g (gamma) -d (delta) -f (fibonacci), default omega\n");
        return 0;
    }

    std::vector<std::string>dict(257);
    dict[0] = "";
    for (int i = 0; i < 256; i++)
        dict[i + 1] = char(i);

    std::map<int, int> dataFileMap;
    std::map<int, int> answerFileMap;

    char currChar = 0;
    std::string currString;
    std::string prevString;
    std::string buffer;
    int dictSize = 257;
    int prevStringIndex = 0;
    bool ifExists;
    int sum = 0;

    //main loop
    while (dataFile >> std::noskipws >> currChar) {
        dataFileMap[currChar]++;
        currString.append(1, currChar);
        ifExists = false;

        for (int i = 0; i < dictSize; i++) {
            if (dict[i] == currString) {
                ifExists = true;
                i = dictSize;
            } else if (dict[i] == prevString) {
                prevStringIndex = i;
            }
        }

        if (!ifExists) {
            buffer.append(encode(prevStringIndex));
            dict.push_back(currString);
            currString = currString[currString.size() - 1];
            dictSize++;
        }

        prevString = currString;
        sum++;
    }

    //if we haven't send all code yet
    if (currString.size() > 1) {
        for (int i = 0; i < dictSize; i++) {
            if (dict[i] == currString) {
                buffer.append(encode(i));
                i = dictSize;
            }
        }
    }

    buffer.append(encode(dictSize + 1));
    sendCode(buffer, answerFile, answerFileMap);

    dataFile.close();
    answerFile.close();

    printf("Encoded file length : %d\n", sum);
    printf("Code length : %lu\n", buffer.size() / 8);
    printf("Compression rate : %f\n", codingAnalysis::getCompressionRate(dataFileName, answerFileName));
    printf("Encoded file entropy : %f\n", codingAnalysis::getEntropy(dataFileMap));
    printf("Code entropy : %f\n", codingAnalysis::getEntropy(answerFileMap));

    return 0;
}

uint8_t binToDec(std::string number) {
    uint8_t result = 0;

    for (int i = 0 ;i < 8; i++) {
        result *= 2;
        result += int(number[i]) - 48;
    }

    return result;
}

void sendCode(std::string& buffer, std::ofstream& answerFile, std::map<int, int>&map) {
    int size = buffer.size();
    uint8_t value;

    if (size % 8 != 0) {
        buffer.append(8 - (size % 8), '0');
        size += 8 - size % 8;
    }

    for (int i = 0; i < size; i += 8) {
        value = binToDec(buffer.substr(i, 8));
        answerFile << value;
        map[value]++;
    }
}
