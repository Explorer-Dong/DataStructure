#include <iostream>
#include <vector>
#include <functional>

using namespace std;

#ifndef CHILDSIBLINGTREE_H
#define CHILDSIBLINGTREE_H

template<class T>
struct ChildSiblingTreeNode {
    T data;
    int degree;
    ChildSiblingTreeNode* first_child;
    ChildSiblingTreeNode* next_sibling;
    
    ChildSiblingTreeNode()
            : degree(0), first_child(nullptr), next_sibling(nullptr) {};
    
    ChildSiblingTreeNode(T data)
            : degree(0), data(data), first_child(nullptr), next_sibling(nullptr) {};
};

template<class T>
class ChildSiblingTree {
private:
    ChildSiblingTreeNode<T>* root;
    void decreate(ChildSiblingTreeNode<T>* now);
    ChildSiblingTreeNode<T>* find(ChildSiblingTreeNode<T>* now, T e); // find the parent of e
    void prePrint(ChildSiblingTreeNode<T>* now);
    void postPrint(ChildSiblingTreeNode<T>* now);
    void countDegree(ChildSiblingTreeNode<T>* now);
    int height(ChildSiblingTreeNode<T>* now, int depth);
    void getPathFromRootToLeaf(
            ChildSiblingTreeNode<T>* now, vector<T>& path,
            vector<vector<T>>& res);

public:
    ChildSiblingTree() : root(nullptr) {}
    
    ChildSiblingTree(vector<pair<T, T>>& edges); // create a tree from a vector of edges
    ~ChildSiblingTree();
    void prePrint();
    void postPrint();
    void countDegree();
    int height();
    vector<vector<T>> getPathFromRootToLeaf();
};

template<class T>
void ChildSiblingTree<T>::decreate(ChildSiblingTreeNode<T>* now) {
    if (!now) {
        return;
    }
    decreate(now->first_child);
    decreate(now->next_sibling);
    delete now;
}

template<class T>
ChildSiblingTreeNode<T>*
ChildSiblingTree<T>::find(ChildSiblingTreeNode<T>* now, T e) {
    if (!now) {
        return nullptr;
    }
    if (now->data == e) {
        return now;
    }
    ChildSiblingTreeNode<T>* l = find(now->first_child, e);
    if (l) {
        return l;
    } else {
        return find(now->next_sibling, e);
    }
}

template<class T>
void ChildSiblingTree<T>::prePrint(ChildSiblingTreeNode<T>* now) {
    if (!now) {
        return;
    }
    cout << "data: " << now->data << " degree: " << now->degree << "\n";
    prePrint(now->first_child);
    prePrint(now->next_sibling);
}

template<class T>
void ChildSiblingTree<T>::postPrint(ChildSiblingTreeNode<T>* now) {
    if (!now) {
        return;
    }
    postPrint(now->first_child);
    cout << "data: " << now->data << " degree: " << now->degree << "\n";
    postPrint(now->next_sibling);
}

template<class T>
void ChildSiblingTree<T>::countDegree(ChildSiblingTreeNode<T>* now) {
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
    countDegree(now->first_child);
    countDegree(now->next_sibling);
}

template<class T>
int ChildSiblingTree<T>::height(ChildSiblingTreeNode<T>* now, int depth) {
    if (!now) {
        return depth;
    }
    return max(height(now->first_child, depth + 1),
               height(now->next_sibling, depth));
}

template<class T>
void ChildSiblingTree<T>::getPathFromRootToLeaf(
        ChildSiblingTreeNode<T>* now, vector<T>& path,
        vector<vector<T>>& res) {
    if (!now) {
        return;
    }
    path.push_back(now->data);
    if (!now->first_child) {
        res.push_back(path);
    } else {
        getPathFromRootToLeaf(now->first_child, path, res);
    }
    path.pop_back();
    getPathFromRootToLeaf(now->next_sibling, path, res);
}

template<class T>
ChildSiblingTree<T>::ChildSiblingTree(vector<pair<T, T>>& edges) {
    if (edges.empty()) {
        root = nullptr;
        return;
    }
    root = new ChildSiblingTreeNode<T>(edges[0].first);
    for (auto [u, v]: edges) {
        ChildSiblingTreeNode<T>* child = new ChildSiblingTreeNode<T>(v);
        ChildSiblingTreeNode<T>* parent = find(root, u);
        if (!parent->first_child) {
            parent->first_child = child;
        } else {
            parent = parent->first_child;
            while (parent->next_sibling) {
                parent = parent->next_sibling;
            }
            parent->next_sibling = child;
        }
    }
}

template<class T>
ChildSiblingTree<T>::~ChildSiblingTree() {
    decreate(root);
}

template<class T>
void ChildSiblingTree<T>::prePrint() {
    prePrint(root);
    cout << endl;
}

template<class T>
void ChildSiblingTree<T>::postPrint() {
    postPrint(root);
    cout << endl;
}

template<class T>
void ChildSiblingTree<T>::countDegree() {
    countDegree(root);
}

template<class T>
int ChildSiblingTree<T>::height() {
    return height(root, 0);
}

template<class T>
vector<vector<T>> ChildSiblingTree<T>::getPathFromRootToLeaf() {
    vector<vector<T>> res;
    vector<T> path;
    getPathFromRootToLeaf(root, path, res);
    return res;
}

#endif //CHILDSIBLINGTREE_H