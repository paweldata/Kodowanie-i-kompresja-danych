//By Pawel Data
#include <fstream>
#include <bitset>

#include "src/universalCode.h"

int main(int argc, char *argv[]) {
    std::ifstream dataFile;
    std::ofstream answerFile;
    std::vector<int> (*decode)(std::string) = &universalCode::decodeOmega;

    //get parameters
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            switch (argv[i][1]) {
                case 'o': decode = &universalCode::decodeOmega; break;
                case 'g': decode = &universalCode::decodeGamma; break;
                case 'd': decode = &universalCode::decodeDelta; break;
                case 'f': decode = &universalCode::decodeFib; break;
            }
        } else if (!dataFile.is_open()) {
            dataFile.open(argv[i]);
        } else if (!answerFile.is_open()) {
            answerFile.open(argv[i]);
        }
    }

    if (!dataFile.is_open() || !answerFile.is_open()) {
        printf("Give filenames as argument\n"
               "./decode file_to_decode result\n"
               "optional parameters: -o (omega) -g (gamma) -d (delta) -f (fibonacci), default omega\n");
        return 0;
    }

    std::vector<std::string>dict(257);
    dict[0] = "";
    for (int i = 0; i < 256; i++)
        dict[i + 1] = char(i);

    char currChar = 0;
    std::string currString;
    std::string prevString;
    std::string buffer;
    int dictSize = 257;
    int prevNumber = -1;

    while (dataFile >> std::noskipws >> currChar)
        buffer.append(std::bitset<8>(uint8_t(currChar)).to_string());

    std::vector<int> numberArray = decode(buffer);

    //main loop
    for (int number : numberArray) {
        if (number < dictSize && prevNumber != -1) {
            dict.push_back(dict[prevNumber] + dict[number][0]);
            dictSize++;
        } else if (number == dictSize) {
            dict.push_back(dict[prevNumber] + dict[prevNumber][dict[prevNumber].size() - 1]);
            dictSize++;
        } else if (number > dictSize) {
            //end code
            break;
        }

        answerFile << dict[number];
        prevNumber = number;
    }

    dataFile.close();
    answerFile.close();

    return 0;
}
