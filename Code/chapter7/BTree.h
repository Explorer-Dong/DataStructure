//
// Created by 董文杰 on 2023-11-02.
//

#include <bits/stdc++.h>

using namespace std;

#ifndef INC_3__DATASTRUCTURES_BTREE_H
#define INC_3__DATASTRUCTURES_BTREE_H

template<class T>
struct BtNode {
	T data;
	BtNode* lchild;
	BtNode* rchild;
	BtNode(T x) : data(x), lchild(nullptr), rchild(nullptr) {}
};


template<class T>
class BTree {
private:
	BtNode<T>* CreateWithPre(const string& pre_of_tag, int& i);
	void PreOutput(BtNode<T>* now);

public:
	BtNode<T>* root;
	BTree() : root(nullptr) {};
	BTree(const string& pre_with_tag);
	BTree(const string& pre, const string& mid);
//	~BTree();

	void PreOutput();
	void MidOutput();
	void PostOutput();
	void LevelOutput();

	int CountLeaf();
	int CountOneBranch();
	int CountTwoBranch();

	int Height();
	void SwapChild();
	vector<vector<T>> PathOfRootToLeaf();
};


template<class T>
BtNode<T>* BTree<T>::CreateWithPre(const string& pre_of_tag, int& i) {
	T e = pre_of_tag[i++];
	if (e == '#') {
		return nullptr;
	}
	BtNode<T>* now = new BtNode<T>(e);
	now->lchild = CreateWithPre(pre_of_tag, i);
	now->rchild = CreateWithPre(pre_of_tag, i);
	return now;
}

template<class T>
void BTree<T>::PreOutput(BtNode<T>* now) {
	if (!now) {
		return;
	}
	cout << now->data;
	PreOutput(now->lchild);
	PreOutput(now->rchild);
}

// -------------------------以下为用户可调用函数--------------------------

template<class T>
BTree<T>::BTree(const string& pre_with_tag) {
	int* p = new int(0); // 未知疑问 TODO
	root = CreateWithPre(pre_with_tag, *p);
}

template<class T>
BTree<T>::BTree(const string& pre, const string& mid) {

}

template<class T>
void BTree<T>::PreOutput() {
	PreOutput(root);
}

#endif //INC_3__DATASTRUCTURES_BTREE_H















