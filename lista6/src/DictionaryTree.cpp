#include "DictionaryTree.h"

#include <cmath>
#include <algorithm>
#include <random>

struct Node {
    std::string code;
    int value;
    Node* left;
    Node* right;
};

DictionaryTree::DictionaryTree(std::vector<int> &values, int size) {
    this->root = new Node{.code = "", .value = 127, .left = nullptr, .right = nullptr};
    this->height = size;

    this->setAverageDistance(this->root, values);
    this->createNode(values, this->root);
}

std::string DictionaryTree::getCode(int value) {
    Node* node = this->root;

    while (node->left != nullptr) {
        if (abs(value - node->left->value) < abs(value - node->right->value)) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    return node->code;
}

void DictionaryTree::createNode(const std::vector<int>& values, Node* node) {
    if (node->code.size() == this->height)
        return;

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> randInt(-2, 2);

    node->left = new Node{.code = node->code + "0", .value = node->value, .left = nullptr, .right = nullptr};
    node->right = new Node{.code = node->code + "1", .value = node->value, .left = nullptr, .right = nullptr};

    do {
        node->right->value += randInt(generator);
    } while (node->left->value == node->right->value);

    std::vector<int> valuesLeft;
    std::vector<int> valuesRight;

    int valueLeftPrev;
    int valueRightPrev;

    do {
        valueLeftPrev = node->left->value;
        valueRightPrev = node->right->value;

        valuesLeft.clear();
        valuesRight.clear();

        for (int value : values) {
            if (abs(value - node->left->value) < abs(value - node->right->value)) {
                valuesLeft.push_back(value);
            } else {
                valuesRight.push_back(value);
            }
        }

        DictionaryTree::setAverageDistance(node->left, valuesLeft);
        DictionaryTree::setAverageDistance(node->right, valuesRight);
    } while (node->left->value != valueLeftPrev || node->right->value != valueRightPrev);

    this->createNode(valuesLeft, node->left);
    this->createNode(valuesRight, node->right);
}

void DictionaryTree::setAverageDistance(Node* node, std::vector<int> &values) {
    int value = 0;
    int size = values.size();

    for (int v : values)
        value += v;

    if (size > 0)
        node->value = value / size;
}

int DictionaryTree::getValue(const std::string& code) {
    Node* node = this->root;

    for (int i = 0; node->left != nullptr; i++)
        node = (node->left->code[i] == code[i]) ? node->left : node->right;

    return node->value;
}
