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

	void Insert(pair<T, T>& p); // 约定：对于<ai, aj>，在插入aj时，ai已经存在于树结构中

public:
	BtNode<T>* root;

	BTree() : root(nullptr) {};

	BTree(string& s, int flag);

	BTree(string& s, string& t, int flag);

	BTree(vector<pair<T, T>>& v);

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


template<class T>
void BTree<T>::Insert(pair<T, T>& p) {
	// 1. 寻找父结点 p.first
	function<BtNode<T>*> findtar = [&](BtNode<T>* now, T tar) {
		if (!now) return nullptr;
		if (now->data == tar) return now;
		auto l = findtar(now->lchild, tar);
		return l ? l : findtar(now->rchild, tar);
	};

	BtNode<T>* fa = findtar(p.first);

	// 2. 插入子结点 p.second
	if (!fa->lchild) {
		// 左孩子不存在，则直接赋值
		fa->lchild = new BtNode<T>(p.second);
	} else {
		// 左孩子已经存在了，则fa的孩子就需要插入左孩子的非空右孩子上，循环寻找非空右孩子
		fa = fa->lchild;
		while (fa->rchild) fa = fa->rchild;
		fa = new BtNode<T>(p.second);
	}
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
		// 用中序和后序进行构造 TODO
		int n = s.size();
		root = CreateWithMidPost(s, t, 0, 0, n);
	}
}


template<class T>
BTree<T>::BTree(vector<pair<T, T>>& v) {
	if (!v.size()) {
		root = nullptr;
		return;
	}

	root = new BtNode<T>(v[0].first);

	for (auto& edge: v) {
		Insert(edge);
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
