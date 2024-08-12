#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

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
    BinaryTreeNode<T>* createWithPreTagged(string& pre_of_tag, int& i);
    BinaryTreeNode<T>* createWithPostTagged(string& post_of_tag, int& i);
    BinaryTreeNode<T>* createWithPreMid(string pre, string mid);
    BinaryTreeNode<T>* createWithMidPost(string mid, string post);
    void decreate(BinaryTreeNode<T>* now);
    void prePrint(BinaryTreeNode<T>* now);
    void midPrint(BinaryTreeNode<T>* now);
    void postPrint(BinaryTreeNode<T>* now);
    int hight(BinaryTreeNode<T>* now, vector<pair<T, int>>& res);
    int hight(BinaryTreeNode<T>* now);
    void dfs(BinaryTreeNode<T>* now, int depth, unordered_map<int, int>& f);
    void dfs(BinaryTreeNode<T>* now, vector<T>& path, vector<vector<T>>& res);
    void dfs(BinaryTreeNode<T>* now, vector<T>& path, vector<T>& res, T target);
    void dfs(BinaryTreeNode<T>* now, BinaryTreeNode<T>*& pre, BinaryTreeNode<T>*& head);
    void dfs(BinaryTreeNode<T>* now);

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
    T getLowestCommonAncestor(T a, T b);
    vector<T> getPathFromRootToNode(T target);
    bool isCompleteBinaryTree();
    int width();
    int hight();
    BinaryTreeNode<T>* linkLeaf();
    void swapChild();
};

template<class T>
BinaryTreeNode<T>* BinaryTree<T>::createWithPreTagged(string& pre_of_tag, int& i) {
    T e = pre_of_tag[i++];
    if (e == '#') {
        return nullptr;
    }
    BinaryTreeNode<T>* now = new BinaryTreeNode<T>(e);
    now->lchild = createWithPreTagged(pre_of_tag, i);
    now->rchild = createWithPreTagged(pre_of_tag, i);
    return now;
}

template<class T>
BinaryTreeNode<T>* BinaryTree<T>::createWithPostTagged(string& post_of_tag, int& i) {
    T e = post_of_tag[i--];
    if (e == '#') {
        return nullptr;
    }
    BinaryTreeNode<T>* now = new BinaryTreeNode<T>(e);
    now->rchild = createWithPostTagged(post_of_tag, i);
    now->lchild = createWithPostTagged(post_of_tag, i);
    return now;
}

template<class T>
BinaryTreeNode<T>* BinaryTree<T>::createWithPreMid(string pre, string mid) {
    if (pre.size() == 0) {
        return nullptr;
    }
    BinaryTreeNode<T>* now_root = new BinaryTreeNode<T>(pre[0]);
    string mid_left, mid_right;
    for (int i = 0; i < mid.size(); i++) {
        if (mid[i] == pre[0]) {
            mid_left = mid.substr(0, i);
            mid_right = mid.substr(i + 1);
            break;
        }
    }
    int len_left = mid_left.size();
    string pre_left = pre.substr(1, len_left);
    string pre_right = pre.substr(len_left + 1);
    now_root->lchild = createWithPreMid(pre_left, mid_left);
    now_root->rchild = createWithPreMid(pre_right, mid_right);
    return now_root;
}

template<class T>
BinaryTreeNode<T>* BinaryTree<T>::createWithMidPost(string mid, string post) {
    if (post.size() == 0) {
        return nullptr;
    }
    BinaryTreeNode<T>* now_root = new BinaryTreeNode<T>(post.back());
    string mid_left, mid_right;
    for (int i = 0; i < mid.size(); i++) {
        if (mid[i] == post.back()) {
            mid_left = mid.substr(0, i);
            mid_right = mid.substr(i + 1);
            break;
        }
    }
    int len_left = mid_left.size();
    int len_right = mid_right.size();
    string post_left = post.substr(0, len_left);
    string post_right = post.substr(len_left, len_right);
    now_root->lchild = createWithMidPost(mid_left, post_left);
    now_root->rchild = createWithMidPost(mid_right, post_right);
    return now_root;
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
int BinaryTree<T>::hight(BinaryTreeNode<T>* now, vector<pair<T, int>>& res) {
    if (!now) {
        return 0;
    }
    int lh = hight(now->lchild, res);
    int rh = hight(now->rchild, res);
    res.push_back({now->data, abs(lh - rh)});
    return max(lh, rh) + 1;
}

template<class T>
int BinaryTree<T>::hight(BinaryTreeNode<T>* now) {
    if (!now) {
        return 0;
    }
    return max(hight(now->lchild), hight(now->rchild)) + 1;
}

template<class T>
void BinaryTree<T>::dfs(BinaryTreeNode<T>* now, int depth, unordered_map<int, int>& f) {
    if (!now) {
        return;
    }
    f[depth]++;
    dfs(now->lchild, depth + 1, f);
    dfs(now->rchild, depth + 1, f);
}

template<class T>
void BinaryTree<T>::dfs(BinaryTreeNode<T>* now, vector<T>& path, vector<vector<T>>& res) {
    if (!now) {
        return;
    }
    path.push_back(now->data);
    if (!now->lchild && !now->rchild) {
        res.push_back(path);
        path.pop_back();
        return;
    }
    dfs(now->lchild, path, res);
    dfs(now->rchild, path, res);
    path.pop_back();
}

template<class T>
void BinaryTree<T>::dfs(BinaryTreeNode<T>* now, vector<T>& path, vector<T>& res, T target) {
    if (!now) {
        return;
    }
    path.push_back(now->data);
    if (now->data == target) {
        res = path;
        path.pop_back();
        return;
    }
    dfs(now->lchild, path, res, target);
    dfs(now->rchild, path, res, target);
    path.pop_back();
}

template<class T>
void BinaryTree<T>::dfs(BinaryTreeNode<T>* now, BinaryTreeNode<T>*& pre, BinaryTreeNode<T>*& head) {
    if (!now) {
        return;
    }
    if (!now->lchild && !now->rchild) {
        if (!head) {
            head = pre = now;
        } else {
            pre->rchild = now;
            pre = now;
        }
        return;
    }
    dfs(now->lchild, pre, head);
    dfs(now->rchild, pre, head);
}

template<class T>
void BinaryTree<T>::dfs(BinaryTreeNode<T>* now) {
    if (!now) {
        return;
    }
    swap(now->lchild, now->rchild);
    dfs(now->lchild);
    dfs(now->rchild);
}

template<class T>
BinaryTree<T>::BinaryTree(string& s, bool is_pre) {
    if (is_pre) {
        // create with pre(tagged) sequence
        int p = 0;
        root = createWithPreTagged(s, p);
    } else {
        // create with post(tagged) sequence
        int p = s.size() - 1;
        root = createWithPostTagged(s, p);
    }
}

template<class T>
BinaryTree<T>::BinaryTree(string& s, string& t, bool is_pre_and_mid) {
    if (is_pre_and_mid) {
        // create with pre and mid sequence
        root = createWithPreMid(s, t);
    } else {
        // create with mid and post sequence
        root = createWithMidPost(s, t);
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

template<class T>
vector<pair<T, int>> BinaryTree<T>::calcHightSub() {
    vector<pair<T, int>> res;
    hight(root, res);
    return res;
}

template<class T>
int BinaryTree<T>::countKthLevelNode(int k) {
    unordered_map<int, int> f;
    dfs(root, 1, f);
    return f[k];
}

template<class T>
vector<vector<T>> BinaryTree<T>::getPathFromRootToLeaf() {
    vector<vector<T>> res;
    vector<T> path;
    dfs(root, path, res);
    return res;
}

template<class T>
T BinaryTree<T>::getLowestCommonAncestor(T a, T b) {
    vector<T> path_to_a = getPathFromRootToNode(a);
    vector<T> path_to_b = getPathFromRootToNode(b);
    T res;
    for (int i = 0; i < path_to_a.size(); i++) {
        if (path_to_a[i] == path_to_b[i]) {
            res = path_to_a[i];
        } else {
            break;
        }
    }
    return res;
}

template<class T>
vector<T> BinaryTree<T>::getPathFromRootToNode(T target) {
    vector<T> path, res;
    dfs(root, path, res, target);
    return res;
}

template<class T>
bool BinaryTree<T>::isCompleteBinaryTree() {
    queue<BinaryTreeNode<T>*> q;
    q.push(root);
    while (q.size()) {
        bool appear = false;// pre appear not double branch node
        vector<BinaryTreeNode<T>*> level;
        while (q.size()) {
            auto now = q.front();
            q.pop();
            if (!now) {
                continue;
            }
            level.push_back(now);
            if (!now->lchild || !now->rchild) {
                appear = true;
            }
            if (appear && (now->lchild || now->rchild)) {
                return false;
            }
        }
        for (auto node: level) {
            q.push(node->lchild);
            q.push(node->rchild);
        }
    }
    return true;
}

template<class T>
int BinaryTree<T>::width() {
    int res = 0;
    queue<BinaryTreeNode<T>*> q;
    q.push(root);
    while (q.size()) {
        vector<BinaryTreeNode<T>*> level;
        while (q.size()) {
            auto now = q.front();
            q.pop();
            if (!now) {
                continue;
            }
            level.push_back(now);
        }
        res = max(res, int(level.size()));
        for (auto node: level) {
            q.push(node->lchild);
            q.push(node->rchild);
        }
    }
    return res;
}

template<class T>
int BinaryTree<T>::hight() {
    return hight(root);
}

template<class T>
BinaryTreeNode<T>* BinaryTree<T>::linkLeaf() {
    BinaryTreeNode<T>* head = nullptr;
    BinaryTreeNode<T>* pre = nullptr;
    dfs(root, pre, head);
    return head;
}

template<class T>
void BinaryTree<T>::swapChild() {
    dfs(root);
}

#endif //BINARYTREE_H