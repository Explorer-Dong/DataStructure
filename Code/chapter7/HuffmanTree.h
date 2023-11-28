//
// Created by 董文杰 on 2023-11-27.
//

#include <bits/stdc++.h>
#include "HuffmanNode.h"
using namespace std;

#ifndef INC_3__DATASTRUCTURES_HUFFMANTREE_H
#define INC_3__DATASTRUCTURES_HUFFMANTREE_H

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

#endif //INC_3__DATASTRUCTURES_HUFFMANTREE_H
