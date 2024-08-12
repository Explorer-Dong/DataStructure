//
// Created by Wenjie Dong on 2023-11-27.
//

#include <bits/stdc++.h>
#include "HuffmanNode.h"

using namespace std;

#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

class HuffmanTree {
private:
    vector<HuffmanNode> tree;
    int n;

public:
    HuffmanTree() : n(0) {}
    HuffmanTree(string& s);
    string EnCode(string& source);
    string DeCode(string& secret);
};

#endif //HUFFMANTREE_H