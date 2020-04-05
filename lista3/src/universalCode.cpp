#include "universalCode.h"

namespace universalCode {
    std::string decToBin(int n) {
        std::string result;

        while(n > 0) {
            result.insert(0, (n % 2 == 0) ? "0" : "1");
            n /= 2;
        }

        return result;
    }

    int binToDec(std::string number) {
        int result = 0;
        int size = number.size();

        for (int i = 0 ;i < size; i++) {
            result *= 2;
            result += int(number[i]) - 48;
        }

        return result;
    }

    std::string encodeOmega(int number) {
        std::string code = "0";
        std::string newPart;

        while (number > 1) {
            newPart = decToBin(number);
            code.insert(0, newPart);
            number = int(newPart.size()) - 1;
        }

        return code;
    }

    std::vector<int> decodeOmega(std::string code) {
        std::vector<int> result;
        int size = code.size();
        int number;
        int i = 0;

        while (i < size) {
            number = 1;

            while (i < size && code[i] != '0') {
                i += number + 1;
                number = std::stoi(code.substr(i - number - 1, number + 1), nullptr, 2);
            }

            if (i <= size) {
                result.push_back(number);
                i++;
            }
        }

        return result;
    }

    std::string encodeGamma(int number) {
        std::string result = decToBin(number);
        result.insert(0, std::string(result.size() - 1, '0'));
        return result;
    }

    std::vector<int> decodeGamma(std::string code) {
        std::vector<int> result;
        int size = code.size();
        int zeroCount;
        int i = 0;

        while (i < size) {
            zeroCount = 0;

            while (code[i] == '0') {
                zeroCount++;
                i++;
            }

            result.push_back(binToDec(code.substr(i, zeroCount + 1)));
            i += zeroCount + 1;
        }

        return result;
    }

    std::string encodeDelta(int number) {
        std::string result = decToBin(number);
        result.erase(0, 1);
        result.insert(0, encodeGamma(int(result.size()) + 1));
        return result;
    }

    std::vector<int> decodeDelta(std::string code) {
        std::vector<int> result;
        int size = code.size();
        int zeroCount;
        int i = 0;

        while (i < size) {
            zeroCount = 0;

            while (code[i] == '0') {
                zeroCount++;
                i++;
            }

            int currSize = binToDec(code.substr(i, zeroCount + 1));
            i += zeroCount + 1;
            if (i + currSize - 1 < size)
                result.push_back(binToDec("1" + code.substr(i, currSize - 1)));
            i += currSize - 1;
        }

        return result;
    }

    std::string encodeFib(int number) {
        std::string result;
        int currFib = 1;
        int prevFib = 1;
        int temp;

        while (currFib <= number) {
            temp = currFib;
            currFib += prevFib;
            prevFib = temp;
        }

        temp = prevFib;
        prevFib = currFib - prevFib;
        currFib = temp;

        while (prevFib > 0) {
            if (currFib <= number) {
                result.insert(0,"1");
                number -= currFib;
            } else {
                result.insert(0,"0");
            }

            temp = prevFib;
            prevFib = currFib - prevFib;
            currFib = temp;
        }

        return result + "1";
    }

    std::vector<int> decodeFib(std::string code) {
        std::vector<int> result;
        int size = code.size();
        int i = 0;
        int number = 0;
        int curr = 1;
        int prev = 1;
        int temp;

        while (code[size - 1] == '0') {
            code.pop_back();
            size--;
        }

        while (i < size) {
            number = 0;
            prev = 1;
            curr = 1;

            while (code[i] == '0' || code[i + 1] == '0') {
                if (code[i] == '1')
                    number += curr;

                temp = curr;
                curr += prev;
                prev = temp;
                i++;
            }

            result.push_back(number + curr);
            i += 2;
        }

        return result;
    }
}
