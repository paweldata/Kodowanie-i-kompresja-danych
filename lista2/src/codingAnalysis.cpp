#include <cmath>
#include <filesystem>
#include "codingAnalysis.h"

namespace codingAnalysis {
    double getEntropy(std::map<char, int>&map, int sum) {
        std::map<char, int>::iterator it;
        double answer = 0;

        for (it = map.begin(); it != map.end(); it++)
            answer += it->second * log2(it->second);

        return - (answer / sum - log2(sum));
    }

    double getCompressionRate(const std::string& plaintext, const std::string& ciphertext) {
        return double(std::filesystem::file_size(plaintext)) / std::filesystem::file_size(ciphertext);
    }
}
