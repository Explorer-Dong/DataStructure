//
// Created by Wenjie Dong on 2023-11-26.
//

#include <bits/stdc++.h>
using namespace std;

#ifndef INC_3__DATASTRUCTURES_CSTREE_H
#define INC_3__DATASTRUCTURES_CSTREE_H

template<class T>
struct CSNode {
	T data;
	int degree;
	CSNode* firstchild, * nextsibling;
	CSNode() : degree(0), firstchild(nullptr), nextsibling(nullptr) {};
	CSNode(T _data) : degree(0), data(_data), firstchild(nullptr), nextsibling(nullptr) {};
};

// ----------------------------------------------------------------------

template<class T>
class CSTree {
private:
	CSNode<T>* root;
	void Free(CSNode<T>* now);
	void add(pair<T, T>& edge); // 添加一条从edge.first到edge.second的边
	CSNode<T>* Find(CSNode<T>* now, T e); // 寻找e的父结点
	void PreOutput(CSNode<T>* now);
	void PostOutput(CSNode<T>* now);
	void CountDegree(CSNode<T>* now);
	void Height(CSNode<T>* now, int dep, int& resv);
	int Height_(CSNode<T>* now);

public:
	CSTree() : root(nullptr) {};
	CSTree(vector<pair<T, T>>& a); // 用边集a构造树
	~CSTree();

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
CSTree<T>::CSTree(vector<pair<T, T>>& a) {
	if (a.empty()) {
		root = nullptr;
		return;
	}

	root = new CSNode<T>(a[0].first);

	for (auto& edge: a) {
		add(edge);
	}
}

template<class T>
CSTree<T>::~CSTree() {
	Free(root);
}

// -------------------------以下为私有函数--------------------------

template<class T>
void CSTree<T>::Free(CSNode<T>* now) {
	if (!now) {
		return;
	}
	Free(now->firstchild);
	Free(now->nextsibling);
	delete now;
}

template<class T>
void CSTree<T>::add(pair<T, T>& edge) {
	// 创建子结点
	CSNode<T>* child = new CSNode<T>(edge.second);

	// 连接父结点
	CSNode<T>* fa = Find(root, edge.first);
	if (!fa->firstchild) {
		fa->firstchild = child;
	} else {
		fa = fa->firstchild;
		while (fa->nextsibling) {
			fa = fa->nextsibling;
		}
		fa->nextsibling = child;
	}
}

template<class T>
CSNode<T>* CSTree<T>::Find(CSNode<T>* now, T e) {
	if (!now) {
		return nullptr;
	}

	if (now->data == e) {
		return now;
	}

	CSNode<T>* l = Find(now->firstchild, e);

	if (l) {
		return l;
	} else {
		return Find(now->nextsibling, e);
	}
}

template<class T>
void CSTree<T>::PreOutput(CSNode<T>* now) {
	if (!now) {
		return;
	}
	cout << now->data << ": " << now->degree << "  ";
	PreOutput(now->firstchild);
	PreOutput(now->nextsibling);
}

template<class T>
void CSTree<T>::PostOutput(CSNode<T>* now) {
	if (!now) {
		return;
	}
	PostOutput(now->firstchild);
	cout << now->data << " ";
	PostOutput(now->nextsibling);
}

template<class T>
void CSTree<T>::CountDegree(CSNode<T>* now) {
	if (!now) {
		return;
	}

	if (now->firstchild) {
		now->degree++;
		CSNode<T>* t = now->firstchild;
		while (t->nextsibling) {
			now->degree++;
			t = t->nextsibling;
		}
	} else {
		now->degree = 0;
	}

	CountDegree(now->firstchild);
	CountDegree(now->nextsibling);
}

template<class T>
void CSTree<T>::Height(CSNode<T>* now, int dep, int& res) {
	if (!now) {
		return;
	}

	res = max(res, dep);
	Height(now->firstchild, dep + 1, res);
	Height(now->nextsibling, dep, res);
}

template<class T>
int CSTree<T>::Height_(CSNode<T>* now) {
	if (!now) {
		return 0;
	}

	int max_Height = 0;

	// 计算子树中的最大高度
	for (CSNode<T>* p = now->firstchild; p; p = p->nextsibling) {
		max_Height = max(max_Height, Height_(p));
	}

	return max_Height + 1;
}

template<class T>
vector<vector<T>> CSTree<T>::Path2Leaf() {
	vector<vector<T>> paths;
	vector<T> path;

	function<void(CSNode<T>*)> dfs = [&](CSNode<T>* now) {
		if (!now) {
			return;
		}

		path.push_back(now->data);

		if (!now->firstchild) {
			paths.push_back(path);
		}

		dfs(now->firstchild);
		path.pop_back();
		dfs(now->nextsibling);
	};

	dfs(root);
	return paths;
}
#endif //INC_3__DATASTRUCTURES_CSTREE_H
