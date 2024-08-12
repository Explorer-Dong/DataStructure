#include <bits/stdc++.h>

using namespace std;
#ifndef CHILDSIBLINGTREE_H
#define CHILDSIBLINGTREE_H

template<class T>
struct ChildSiblingTreeNode {
    T data;
    int degree;
    ChildSiblingTreeNode* first_child, * next_sibling;
    
    ChildSiblingTreeNode() : degree(0), first_child(nullptr), next_sibling(nullptr) {};
    
    ChildSiblingTreeNode(T _data) : degree(0), data(_data), first_child(nullptr), next_sibling(nullptr) {};
};

template<class T>
class ChildSiblingTree {
private:
    ChildSiblingTreeNode<T>* root;
    void Free(ChildSiblingTreeNode<T>* now);
    void add(pair<T, T>& edge); // 添加一条从edge.first到edge.second的边
    ChildSiblingTreeNode<T>* Find(ChildSiblingTreeNode<T>* now, T e); // 寻找e的父结点
    void PreOutput(ChildSiblingTreeNode<T>* now);
    void PostOutput(ChildSiblingTreeNode<T>* now);
    void CountDegree(ChildSiblingTreeNode<T>* now);
    void Height(ChildSiblingTreeNode<T>* now, int dep, int& resv);
    int Height_(ChildSiblingTreeNode<T>* now);
public:
    ChildSiblingTree() : root(nullptr) {};
    ChildSiblingTree(vector<pair<T, T>>& a); // 用边集a构造树
    ~ChildSiblingTree();

// -------------------------以下为用户可调用函数--------------------------
    
    void PreOutput() {
        PreOutput(root);
        cout << endl;
    }
    
    void PostOutput() {
        PostOutput(root);
        cout << endl;
    }
    
    void CountDegree() {
        CountDegree(root);
    }
    
    int Height() {
        int res = 0;
        Height(root, 1, res);
        return res;
    }
    
    int Height_() {
        return Height_(root);
    }
    
    vector<vector<T>> Path2Leaf();
};

// -------------------------以下为构造与析构函数--------------------------

template<class T>
ChildSiblingTree<T>::ChildSiblingTree(vector<pair<T, T>>& a) {
    if (a.empty()) {
        root = nullptr;
        return;
    }
    root = new ChildSiblingTreeNode<T>(a[0].first);
    for (auto& edge: a) {
        add(edge);
    }
}

template<class T>
ChildSiblingTree<T>::~ChildSiblingTree() {
    Free(root);
}

// -------------------------以下为私有函数--------------------------

template<class T>
void ChildSiblingTree<T>::Free(ChildSiblingTreeNode<T>* now) {
    if (!now) {
        return;
    }
    Free(now->first_child);
    Free(now->next_sibling);
    delete now;
}

template<class T>
void ChildSiblingTree<T>::add(pair<T, T>& edge) {
    // 创建子结点
    ChildSiblingTreeNode<T>* child = new ChildSiblingTreeNode<T>(edge.second);
    
    // 连接父结点
    ChildSiblingTreeNode<T>* fa = Find(root, edge.first);
    if (!fa->first_child) {
        fa->first_child = child;
    } else {
        fa = fa->first_child;
        while (fa->next_sibling) {
            fa = fa->next_sibling;
        }
        fa->next_sibling = child;
    }
}

template<class T>
ChildSiblingTreeNode<T>* ChildSiblingTree<T>::Find(ChildSiblingTreeNode<T>* now, T e) {
    if (!now) {
        return nullptr;
    }
    if (now->data == e) {
        return now;
    }
    ChildSiblingTreeNode<T>* l = Find(now->first_child, e);
    if (l) {
        return l;
    } else {
        return Find(now->next_sibling, e);
    }
}

template<class T>
void ChildSiblingTree<T>::PreOutput(ChildSiblingTreeNode<T>* now) {
    if (!now) {
        return;
    }
    cout << now->data << ": " << now->degree << "  ";
    PreOutput(now->first_child);
    PreOutput(now->next_sibling);
}

template<class T>
void ChildSiblingTree<T>::PostOutput(ChildSiblingTreeNode<T>* now) {
    if (!now) {
        return;
    }
    PostOutput(now->first_child);
    cout << now->data << " ";
    PostOutput(now->next_sibling);
}

template<class T>
void ChildSiblingTree<T>::CountDegree(ChildSiblingTreeNode<T>* now) {
    if (!now) {
        return;
    }
    if (now->first_child) {
        now->degree++;
        ChildSiblingTreeNode<T>* t = now->first_child;
        while (t->next_sibling) {
            now->degree++;
            t = t->next_sibling;
        }
    } else {
        now->degree = 0;
    }
    CountDegree(now->first_child);
    CountDegree(now->next_sibling);
}

template<class T>
void ChildSiblingTree<T>::Height(ChildSiblingTreeNode<T>* now, int dep, int& res) {
    if (!now) {
        return;
    }
    res = max(res, dep);
    Height(now->first_child, dep + 1, res);
    Height(now->next_sibling, dep, res);
}

template<class T>
int ChildSiblingTree<T>::Height_(ChildSiblingTreeNode<T>* now) {
    if (!now) {
        return 0;
    }
    int max_Height = 0;
    
    // 计算子树中的最大高度
    for (ChildSiblingTreeNode<T>* p = now->first_child; p; p = p->next_sibling) {
        max_Height = max(max_Height, Height_(p));
    }
    return max_Height + 1;
}

template<class T>
vector<vector<T>> ChildSiblingTree<T>::Path2Leaf() {
    vector<vector<T>> paths;
    vector<T> path;
    function<void(ChildSiblingTreeNode<T>*)> dfs = [&](ChildSiblingTreeNode<T>* now) {
        if (!now) {
            return;
        }
        path.push_back(now->data);
        if (!now->first_child) {
            paths.push_back(path);
        }
        dfs(now->first_child);
        path.pop_back();
        dfs(now->next_sibling);
    };
    dfs(root);
    return paths;
}

#endif //CHILDSIBLINGTREE_H
