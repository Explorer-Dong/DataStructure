//
// Created by Wenjie Dong on 2023-11-28.
//

#include "HuffmanTree.h"

HuffmanTree::HuffmanTree(string& s) {
    // 哈希计算字符出现频率
    unordered_map<char, double> a;
    for (auto& c: s) {
        a[c]++;
    }
    double sum = 0;         // 总权值
    n = a.size();           // 子结点个数
    for (auto& it: a) {
        sum += it.second;
    }
    
    // 初始化n个子结点
    priority_queue<HuffmanNode> q;
    tree.resize(2 * n - 1);
    int idx = 0;
    for (auto& it: a) {
        tree[idx].data = it.first;
        tree[idx].weight = it.second / sum;
        tree[idx].parent = -1;
        tree[idx].lchild = -1;
        tree[idx].rchild = -1;
        q.push(tree[idx++]);
    }
    
    // 根据字符寻找在森林中的下标
    auto find_idx = [&](HuffmanNode& node) {
        for (int i = 0; i < 2 * n - 1; i++)
            if (tree[i].weight == node.weight)
                return i;
        cerr << "not found target leaf!\n";
        exit(1);
    };
    
    // 构建n-1个分支
    for (int i = n; i < 2 * n - 1; i++) {
        HuffmanNode x = q.top();
        q.pop();
        HuffmanNode y = q.top();
        q.pop();
        int ix = find_idx(x), iy = find_idx(y);
        tree[ix].parent = i, tree[iy].parent = i;
        tree[i].lchild = ix, tree[i].rchild = iy;
        tree[i].parent = -1;
        tree[i].weight = x.weight + y.weight;
        q.push(tree[i]);
    }
}

string HuffmanTree::EnCode(string& source) {
    // 获得编码列表
    unordered_map<char, string> a;
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
        
        a[tree[i].data] = code;
    }

//	cout << "每一个字符的编码：\n";
//	for (auto& it: a) {
//		cout << it.first << ": " << it.second << "\n";
//	}
    
    // 编码并返回
    string res;
    for (auto& c: source) {
        res += a[c];
    }
    return res;
}

string HuffmanTree::DeCode(string& secret) {
    string res;
    
    int root = tree.size() - 1;
    
    int i = 0;
    while (i < secret.size()) {
        int now = root;
        while (tree[now].lchild != -1 && tree[now].rchild != -1) {
            if (secret[i] == '1') {
                now = tree[now].rchild;
            } else {
                now = tree[now].lchild;
            }
            i++;
        }
        res += tree[now].data;
    }
    
    return res;
}