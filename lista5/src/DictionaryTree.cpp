#include "DictionaryTree.h"

#include <cmath>
#include <algorithm>
#include <random>

struct Node {
    std::string code;
    Pixel pixel;
    Node* left;
    Node* right;
};

DictionaryTree::DictionaryTree(std::vector<std::vector<Pixel>>& image, int size) {
    this->root = new Node{.code = "", .pixel = Pixel(), .left = nullptr, .right = nullptr};
    this->height = size;

    std::vector<Pixel> pixels(image.size() * image[0].size());

    int heightImage = image.size();
    int widthImage = image[0].size();

    for (int i = 0; i < heightImage; i++) {
        for (int j = 0; j < widthImage; j++) {
            pixels[i * widthImage + j] = image[i][j];
        }
    }

    this->setAverageDistance(this->root, pixels);
    this->createNode(pixels, this->root);
}

Pixel DictionaryTree::getNewPixel(Pixel pixel) {
    Node* node = this->root;

    while (node->left != nullptr) {
        if (DictionaryTree::distance(pixel, node->left->pixel) < DictionaryTree::distance(pixel, node->right->pixel)) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    return node->pixel;
}

int DictionaryTree::distance(Pixel p1, Pixel p2) {
    return abs(p1.red - p2.red) + abs(p1.green - p2.green) + abs(p1.blue - p2.blue);
}

void DictionaryTree::createNode(const std::vector<Pixel>& pixels, Node* node) {
    if (node->code.size() == this->height)
        return;

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> randInt(-2, 2);

    node->left = new Node{.code = node->code + "0", .pixel = node->pixel, .left = nullptr, .right = nullptr};
    node->right = new Node{.code = node->code + "1", .pixel = node->pixel, .left = nullptr, .right = nullptr};

    do {
        node->right->pixel.red = std::max(0, std::min(255, (int) node->right->pixel.red + randInt(generator)));
        node->right->pixel.green = std::max(0, std::min(255, (int) node->right->pixel.green + randInt(generator)));
        node->right->pixel.blue = std::max(0, std::min(255, (int) node->right->pixel.blue + randInt(generator)));
    } while (node->left->pixel.red == node->right->pixel.red
    && node->left->pixel.green == node->right->pixel.green
    && node->left->pixel.blue == node->right->pixel.blue);

    std::vector<Pixel> pixelsLeft;
    std::vector<Pixel> pixelsRight;

    Pixel pixelLeftPrev;
    Pixel pixelRightPrev;

    do {
        pixelLeftPrev = node->left->pixel;
        pixelRightPrev = node->right->pixel;

        pixelsLeft.clear();
        pixelsRight.clear();

        for (Pixel pixel : pixels) {
            if (DictionaryTree::distance(pixel, node->left->pixel) <
                DictionaryTree::distance(pixel, node->right->pixel)) {
                pixelsLeft.push_back(pixel);
            } else {
                pixelsRight.push_back(pixel);
            }
        }

        DictionaryTree::setAverageDistance(node->left, pixelsLeft);
        DictionaryTree::setAverageDistance(node->right, pixelsRight);
    } while (!node->left->pixel.theSameValues(pixelLeftPrev) || !node->right->pixel.theSameValues(pixelRightPrev));

    this->createNode(pixelsLeft, node->left);
    this->createNode(pixelsRight, node->right);
}

void DictionaryTree::setAverageDistance(Node* node, std::vector<Pixel> &pixels) {
    uint64_t red = 0;
    uint64_t green = 0;
    uint64_t blue = 0;
    int pixelAmount = pixels.size();

    for (Pixel p : pixels) {
        red += p.red;
        green += p.green;
        blue += p.blue;
    }

    if (pixelAmount > 0) {
        node->pixel.red = red / pixelAmount;
        node->pixel.green = green / pixelAmount;
        node->pixel.blue = blue / pixelAmount;
    }
}
