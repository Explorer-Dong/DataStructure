#include <vector>
#include <string>

using namespace std;

#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

struct HuffmanNode {
    char data;
    int weight;
    int parent, lchild, rchild;
    int idx; // the index in the tree
    
    HuffmanNode()
            : data(0), weight(0), parent(-1), lchild(-1), rchild(-1), idx(0) {}
    
    HuffmanNode(char d, double w, int p, int l, int r, int idx)
            : data(d), weight(w), parent(p), lchild(l), rchild(r), idx(idx) {}
    
    bool operator<(const HuffmanNode& t) const {
        return weight > t.weight;
    }
};

class HuffmanTree {
private:
    vector<HuffmanNode> tree;
    int n;

public:
    HuffmanTree() : n(0) {}
    
    HuffmanTree(string& s);
    pair<unordered_map<char, string>, string> encode(string& source);
    string decode(string& secret);
};

#endif //HUFFMANTREE_H