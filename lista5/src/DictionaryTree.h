#ifndef DICTIONARYTREE_H
#define DICTIONARYTREE_H


#include <string>
#include <vector>
#include "Pixel.h"

struct Node;

class DictionaryTree {
public:
    DictionaryTree(std::vector<std::vector<Pixel>>& image, int size);
    Pixel getNewPixel(Pixel pixel);
    static int distance(Pixel p1, Pixel p2);

private:
    void createNode(const std::vector<Pixel>& pixels, Node* node);
    void setAverageDistance(Node* node, std::vector<Pixel>& pixels);

    Node* root;
    int height;
};


#endif //DICTIONARYTREE_H
