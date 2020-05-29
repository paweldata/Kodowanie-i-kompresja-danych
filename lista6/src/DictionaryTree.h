#ifndef DICTIONARYTREE_H
#define DICTIONARYTREE_H


#include <string>
#include <vector>

struct Node;

class DictionaryTree {
public:
    DictionaryTree() {}
    DictionaryTree(std::vector<int>& values, int size);
    std::string getCode(int value);
    int getValue(const std::string& code);

private:
    void createNode(const std::vector<int>& values, Node* node);
    static void setAverageDistance(Node* node, std::vector<int>& values);

    Node* root;
    int height;
};


#endif //DICTIONARYTREE_H