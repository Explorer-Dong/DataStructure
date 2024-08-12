//
// Created by Wenjie Dong on 2023-11-28.
//

#ifndef HUFFMANNODE_H
#define HUFFMANNODE_H

struct HuffmanNode {
    char data;
    double weight;
    int parent, lchild, rchild;
    bool operator<(const HuffmanNode& t) const {
        return weight > t.weight;
    }
};

#endif //HUFFMANNODE_H