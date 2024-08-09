//
// Created by Wenjie Dong on 2023-11-02.
//

#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

#ifndef BINARYTREE_H
#define BINARYTREE_H

template<class T>
struct BinaryTreeNode {
    T data;
    BinaryTreeNode* lchild;
    BinaryTreeNode* rchild;
    BinaryTreeNode(T x) : data(x), lchild(nullptr), rchild(nullptr) {}
};

template<class T>
class BinaryTree {
private:
    BinaryTreeNode<T>* root;
    BinaryTreeNode<T>* createWithPreTaged(string& pre_of_tag, int& i);
    BinaryTreeNode<T>* createWithPostTaged(string& post_of_tag, int& i);
    BinaryTreeNode<T>* createWithPreMid(string& pre, string& mid, int ipre, int imid, int n);
    BinaryTreeNode<T>* createWithMidPost(string& mid, string& post, int imid, int ipost, int n);
    void decreate(BinaryTreeNode<T>* now);
    
    void prePrint(BinaryTreeNode<T>* now);
    void midPrint(BinaryTreeNode<T>* now);
    void postPrint(BinaryTreeNode<T>* now);

public:
    BinaryTree() : root(nullptr) {};
    BinaryTree(string& s, bool is_pre);
    BinaryTree(string& s, string& t, bool is_pre_and_mid);
    ~BinaryTree();
    
    void prePrint();
    void midPrint();
    void postPrint();
    void levelPrint();
    int countDoubleBranchNode();
    int countSingleBranchNode();
    int countLeafNode();
    vector<pair<T, int>> calcHightSub();
    int countKthLevelNode(int k);
    vector<vector<T>> getPathFromRootToLeaf();
    T getLowestCommonAcestor(T a, T b);
    vector<T> getPathFromRootToNode(T target);
    bool isCompleteBinaryTree();
    int width();
    int height();
    BinaryTreeNode<T>* linkLeaf();
    void swapChild();
};

template<class T>
BinaryTreeNode<T>* BinaryTree<T>::createWithPreTaged(string& pre_of_tag, int& i) {
    T e = pre_of_tag[i++];
    if (e == '#') {
        return nullptr;
    }
    BinaryTreeNode<T>* now = new BinaryTreeNode<T>(e);
    now->lchild = createWithPreTaged(pre_of_tag, i);
    now->rchild = createWithPreTaged(pre_of_tag, i);
    return now;
}

template<class T>
BinaryTreeNode<T>* BinaryTree<T>::createWithPostTaged(string& post_of_tag, int& i) {
    T e = post_of_tag[i--];
    if (e == '#') {
        return nullptr;
    }
    BinaryTreeNode<T>* now = new BinaryTreeNode<T>(e);
    now->rchild = createWithPostTaged(post_of_tag, i);
    now->lchild = createWithPostTaged(post_of_tag, i);
    return now;
}

template<class T>
BinaryTreeNode<T>* BinaryTree<T>::createWithPreMid(string& pre, string& mid, int ipre, int imid, int n) {
    /**
     * 用先序和中序进行构造
     * @param pre 先序序列
     * @param mid 中序序列
     * @param ipre 先序序列的起始位置
     * @param imid 中序序列的起始位置
     * @param n 以当前节点为根节点的子树的节点个数
     * @note 用先序序列的第一个元素作为根节点，然后在中序序列中找到该元素，将中序序列分为左右两部分，左边为左子树，右边为右子树
     * @note 然后在先序序列中，根据左右子树的节点个数，将先序序列分为左右两部分，左边为左子树，右边为右子树
     * @note 递归构造左右子树
     * @note 递归终止条件：节点个数为0
     */
    if (!n) {
        return nullptr;
    }
    T e = pre[ipre];
    BinaryTreeNode<T>* now = new BinaryTreeNode<T>(e);
    int i = imid;
    while (i < imid + n && mid[i] != e) i++;
    int llen = i - imid;
    int rlen = n - llen - 1;
    now->lchild = createWithPreMid(pre, mid, ipre + 1, imid, llen);
    now->rchild = createWithPreMid(pre, mid, ipre + llen + 1, imid + llen + 1, rlen);
    return now;
}

template<class T>
BinaryTreeNode<T>* BinaryTree<T>::createWithMidPost(string& mid, string& post, int imid, int ipost, int n) {
    if (!n) {
        return nullptr;
    }
    T e = post[ipost + n - 1];
    BinaryTreeNode<T>* now = new BinaryTreeNode<T>(e);
    int i = imid;
    while (i < imid + n && mid[i] != e) i++;
    int llen = i - imid;
    int rlen = n - llen - 1;
    now->lchild = createWithMidPost(mid, post, imid, ipost, llen);
    now->rchild = createWithMidPost(mid, post, imid + llen + 1, ipost + llen, rlen);
    return now;
}

template<class T>
void BinaryTree<T>::decreate(BinaryTreeNode<T>* now) {
    if (!now) return;
    decreate(now->lchild);
    decreate(now->rchild);
    delete now;
}

template<class T>
void BinaryTree<T>::prePrint(BinaryTreeNode<T>* now) {
    if (!now) {
        return;
    }
    cout << now->data;
    prePrint(now->lchild);
    prePrint(now->rchild);
}

template<class T>
void BinaryTree<T>::midPrint(BinaryTreeNode<T>* now) {
    if (!now) {
        return;
    }
    midPrint(now->lchild);
    cout << now->data;
    midPrint(now->rchild);
}

template<class T>
void BinaryTree<T>::postPrint(BinaryTreeNode<T>* now) {
    if (!now) {
        return;
    }
    postPrint(now->lchild);
    postPrint(now->rchild);
    cout << now->data;
}

template<class T>
BinaryTree<T>::BinaryTree(string& s, bool is_pre) {
    if (is_pre) {
        // create with pre(taged) sequence
        int p = 0;
        root = createWithPreTaged(s, p);
    } else {
        // create with post(taged) sequence
        int p = s.size() - 1;
        root = createWithPostTaged(s, p);
    }
}

template<class T>
BinaryTree<T>::BinaryTree(string& s, string& t, bool is_pre_and_mid) {
    if (is_pre_and_mid) {
        // create with pre and mid sequence
        int n = s.size();
        root = createWithPreMid(s, t, 0, 0, n);
    } else {
        // create with mid and post sequence
        int n = s.size();
        root = createWithMidPost(s, t, 0, 0, n);
    }
}

template<class T>
BinaryTree<T>::~BinaryTree() {
    decreate(root);
}

template<class T>
void BinaryTree<T>::prePrint() {
    prePrint(root);
}

template<class T>
void BinaryTree<T>::midPrint() {
    midPrint(root);
}

template<class T>
void BinaryTree<T>::postPrint() {
    postPrint(root);
}

template<class T>
void BinaryTree<T>::levelPrint() {
    queue<BinaryTreeNode<T>*> q;
    q.push(root);
    
    while (q.size()) {
        auto h = q.front();
        q.pop();
        if (h) {
            cout << h->data;
            q.push(h->lchild);
            q.push(h->rchild);
        }
    }
}

template<class T>
int BinaryTree<T>::countDoubleBranchNode() {
    int cnt = 0;
    queue<BinaryTreeNode<T>*> q;
    q.push(root);
    while (q.size()) {
        auto now = q.front();
        q.pop();
        cnt += now->lchild != nullptr && now->rchild != nullptr;
        if (now->lchild) {
            q.push(now->lchild);
        }
        if (now->rchild) {
            q.push(now->rchild);
        }
    }
    return cnt;
}

template<class T>
int BinaryTree<T>::countSingleBranchNode() {
    int cnt = 0;
    queue<BinaryTreeNode<T>*> q;
    q.push(root);
    while (q.size()) {
        auto now = q.front();
        q.pop();
        cnt += now->lchild != nullptr && now->rchild == nullptr ||
               now->lchild == nullptr && now->rchild != nullptr;
        if (now->lchild) {
            q.push(now->lchild);
        }
        if (now->rchild) {
            q.push(now->rchild);
        }
    }
    return cnt;
}

template<class T>
int BinaryTree<T>::countLeafNode() {
    int cnt = 0;
    queue<BinaryTreeNode<T>*> q;
    q.push(root);
    while (q.size()) {
        auto now = q.front();
        q.pop();
        cnt += now->lchild == nullptr && now->rchild == nullptr;
        if (now->lchild) {
            q.push(now->lchild);
        }
        if (now->rchild) {
            q.push(now->rchild);
        }
    }
    return cnt;
}

#endif //BINARYTREE_H