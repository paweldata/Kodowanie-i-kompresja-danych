#ifndef UNIVERSALCODE_H
#define UNIVERSALCODE_H

#include <string>
#include <vector>

namespace universalCode {
    std::string decToBin(int n);
    int binToDec(std::string number);

    std::string encodeOmega(int number);
    std::vector<int> decodeOmega(std::string code);

    std::string encodeGamma(int number);
    std::vector<int> decodeGamma(std::string code);

    std::string encodeDelta(int number);
    std::vector<int> decodeDelta(std::string code);

    std::string encodeFib(int number);
    std::vector<int> decodeFib(std::string code);
}

#endif //UNIVERSALCODE_H
