#ifndef CODINGANALYSIS_H
#define CODINGANALYSIS_H

#include <map>

namespace codingAnalysis {
    double getEntropy(std::map<char, int>&map, int sum);
    double getCompressionRate(const std::string& plaintext, const std::string& ciphertext);
}

#endif //CODINGANALYSIS_H
