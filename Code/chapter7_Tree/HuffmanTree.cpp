#include <iostream>
#include <queue>
#include <unordered_map>
#include "HuffmanTree.h"

HuffmanTree::HuffmanTree(string& info) {
    // store the frequency of each character
    unordered_map<char, int> dict;
    for (auto c: info) {
        dict[c]++;
    }
    n = dict.size();
    tree.resize(2 * n - 1);
    
    // init the forest of n trees
    priority_queue<HuffmanNode> q;
    int idx = 0;
    for (auto [c, freq]: dict) {
        tree[idx] = HuffmanNode(c, freq, -1, -1, -1, idx);
        q.push(tree[idx++]);
    }
    
    // create n-1 internal nodes
    for (int i = n; i < 2 * n - 1; i++) {
        HuffmanNode l_node = q.top();
        q.pop();
        HuffmanNode r_node = q.top();
        q.pop();
        tree[l_node.idx].parent = tree[r_node.idx].parent = i;
        tree[i] = HuffmanNode(' ', l_node.weight + r_node.weight,
                              -1, l_node.idx, r_node.idx, i);
        q.push(tree[i]);
    }
}

pair<unordered_map<char, string>, string> HuffmanTree::encode(string& source) {
    // traverse the tree to get the code of each character
    unordered_map<char, string> dict;
    for (int i = 0; i < n; i++) {
        string code;
        int now = i;
        int pa = tree[i].parent;
        while (pa != -1) {
            if (tree[pa].lchild == now) {
                code = "0" + code;
            } else {
                code = "1" + code;
            }
            now = pa;
            pa = tree[pa].parent;
        }
        dict[tree[i].data] = code;
    }
    
    // encode the source
    string res;
    for (auto c: source) {
        if (dict.find(c) == dict.end()) {
            dict[c] = "|unknown character|";
        }
        res += dict[c];
    }
    
    return {dict, res};
}

string HuffmanTree::decode(string& secret) {
    string res;
    int root = tree.size() - 1;
    int i = 0;
    while (i < secret.size()) {
        int now = root;
        while (tree[now].lchild != -1 && tree[now].rchild != -1) {
            if (secret[i] == '1') {
                now = tree[now].rchild;
            } else if (secret[i] == '0') {
                now = tree[now].lchild;
            } else {
                return "|invalid secret|";
            }
            i++;
        }
        res += tree[now].data;
    }
    return res;
}