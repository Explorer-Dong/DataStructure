//
// Created by Wenjie Dong on 2023-11-02.
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


// ----------------------------------------------------------------------


template<class T>
class BTree {
private:
	BtNode<T>* CreateWithPre(string& pre_of_tag, int& i);
	BtNode<T>* CreateWithPost(string& post_of_tag, int& i);
	BtNode<T>* CreateWithPreMid(string& pre, string& mid, int ipre, int imid, int n);
	BtNode<T>* CreateWithMidPost(string& mid, string& post, int imid, int ipost, int n);
	void Free(BtNode<T>* now);

	void PreOutput(BtNode<T>* now);
	void MidOutput(BtNode<T>* now);
	void PostOutput(BtNode<T>* now);

public:
	BtNode<T>* root;
	BTree() : root(nullptr) {};
	BTree(string& s, int flag);
	BTree(string& s, string& t, int flag);
	~BTree();

	void PreOutput();
	void MidOutput();
	void PostOutput();
	void LevelOutput();
};


// -------------------------以下为私有函数--------------------------


template<class T>
BtNode<T>* BTree<T>::CreateWithPre(string& pre_of_tag, int& i) {
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
BtNode<T>* BTree<T>::CreateWithPost(string& post_of_tag, int& i) {
	T e = post_of_tag[i--];
	if (e == '#') {
		return nullptr;
	}
	BtNode<T>* now = new BtNode<T>(e);
	now->rchild = CreateWithPost(post_of_tag, i);
	now->lchild = CreateWithPost(post_of_tag, i);
	return now;
}


template<class T>
BtNode<T>* BTree<T>::CreateWithPreMid(string& pre, string& mid, int ipre, int imid, int n) {
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
	BtNode<T>* now = new BtNode<T>(e);
	int i = imid;
	while (i < imid + n && mid[i] != e) i++;
	int llen = i - imid;
	int rlen = n - llen - 1;
	now->lchild = CreateWithPreMid(pre, mid, ipre + 1, imid, llen);
	now->rchild = CreateWithPreMid(pre, mid, ipre + llen + 1, imid + llen + 1, rlen);
	return now;
}


template<class T>
BtNode<T>* BTree<T>::CreateWithMidPost(string& mid, string& post, int imid, int ipost, int n) {
	if (!n) {
		return nullptr;
	}
	T e = post[ipost + n - 1];
	BtNode<T>* now = new BtNode<T>(e);
	int i = imid;
	while (i < imid + n && mid[i] != e) i++;
	int llen = i - imid;
	int rlen = n - llen - 1;
	now->lchild = CreateWithMidPost(mid, post, imid, ipost, llen);
	now->rchild = CreateWithMidPost(mid, post, imid + llen + 1, ipost + llen, rlen);
	return now;
}


template<class T>
void BTree<T>::Free(BtNode<T>* now) {
	if (!now) return;
	Free(now->lchild);
	Free(now->rchild);
	delete now;
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


template<class T>
void BTree<T>::MidOutput(BtNode<T>* now) {
	if (!now) {
		return;
	}
	MidOutput(now->lchild);
	cout << now->data;
	MidOutput(now->rchild);
}


template<class T>
void BTree<T>::PostOutput(BtNode<T>* now) {
	if (!now) {
		return;
	}
	PostOutput(now->lchild);
	PostOutput(now->rchild);
	cout << now->data;
}


// -------------------------以下为构造与析构函数--------------------------


template<class T>
BTree<T>::BTree(string& s, int flag) {
	if (flag == 1) {
		// 用含标记的先序遍历序列进行构造
		int p = 0;
		root = CreateWithPre(s, p);
	} else {
		// 用含标记的后序遍历序列进行构造
		int p = s.size() - 1;
		root = CreateWithPost(s, p);
	}
}


template<class T>
BTree<T>::BTree(string& s, string& t, int flag) {
	if (flag == 1) {
		// 用先序和中序进行构造 TODO
		int n = s.size();
		root = CreateWithPreMid(s, t, 0, 0, n);
	} else {
		// 用中序和后序进行构造 TODO*
		int n = s.size();
		root = CreateWithMidPost(s, t, 0, 0, n);
	}
}


template<class T>
BTree<T>::~BTree() {
	Free(root);
}


// -------------------------以下为用户可调用函数--------------------------


template<class T>
void BTree<T>::PreOutput() {
	PreOutput(root);
}


template<class T>
void BTree<T>::MidOutput() {
	MidOutput(root);
}


template<class T>
void BTree<T>::PostOutput() {
	PostOutput(root);
}


template<class T>
void BTree<T>::LevelOutput() {
	queue<BtNode<T>*> q;
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

#endif //INC_3__DATASTRUCTURES_BTREE_H
