//
// Created by Wenjie Dong on 2023-11-28.
//

#include <bits/stdc++.h>
using namespace std;

#ifndef INC_3__DATASTRUCTURES_ALGRAPH_H
#define INC_3__DATASTRUCTURES_ALGRAPH_H

template<class T>
struct EdgeNode {   // 边点集
	int toid;			// 当前边所连接的下一个顶点的编号
	T w;				// 当前边的信息（以权重 w 为例）
	EdgeNode* next;		// 当前边的下一条边的地址
	EdgeNode(int _toid) : toid(_toid) {}
	EdgeNode(int _toid, T _w) : toid(_toid), w(_w) {}
};

template<class T>
struct VexNode {    // 顶点集
	int id;				// 当前顶点的编号
	EdgeNode<T>* next;	// 当前顶点所指的第一条边的地址
};

template<class T>
class ALGraph {
private:
	int n, e;
	vector<VexNode<T>> h;
	GraphType kind;
	void add(int u, int v);         // 图的加边函数
	void add(int u, int v, T w);    // 网的加边函数

public:
	ALGraph() : n(0), e(0) {}
	ALGraph(GraphType _kind, vector<int>& _vexs, vector<pair<int, int>>& _edges);         // 图
	ALGraph(GraphType _kind, vector<int>& _vexs, vector<tuple<int, int, T>>& _edges);     // 网
	~ALGraph();

	void dfs();
	void bfs();
	bool FindPathFromA2B(int a, int b);
	bool FindPathFromA2BLengthK(int a, int b, int k);
};


// -------------------------以下为构造与析构函数--------------------------


template<class T>
ALGraph<T>::ALGraph(GraphType _kind, vector<int>& _vexs, vector<pair<int, int>>& _edges) {
	n = _vexs.size();
	e = _edges.size();
	kind = _kind;
	h.resize(n + 1);        // 结点下标从1开始

	// 初始化表头
	for (int i = 1; i <= n; i++) {
		h[i].id = i;
		h[i].next = nullptr;
	}

	// 存边建图
	if (kind == undigraph) {
		for (auto& edge: _edges) {
			int u = edge.first, v = edge.second;
			add(u, v);
			add(v, u);
		}
	} else { // kind == digraph
		for (auto& edge: _edges) {
			int u = edge.first, v = edge.second;
			add(u, v);
		}
	}
}

template<class T>
ALGraph<T>::ALGraph(GraphType _kind, vector<int>& _vexs, vector<tuple<int, int, T>>& _edges) {
	n = _vexs.size();
	e = _edges.size();
	kind = _kind;
	h.resize(n + 1);        // 结点下标从1开始

	// 初始化表头
	for (int i = 1; i <= n; i++) {
		h[i].id = i;
		h[i].next = nullptr;
	}

	// 存边建图
	if (kind == undinetwork) {
		for (auto& edge: _edges) {
			int u = get<0>(edge), v = get<0>(edge);
			T w = get<2>(edge);
			add(u, v, w);
			add(v, u, w);
		}
	} else { // kind == dinetwork
		for (auto& edge: _edges) {
			int u = get<0>(edge), v = get<0>(edge);
			T w = get<2>(edge);
			add(u, v, w);
		}
	}
}

template<class T>
ALGraph<T>::~ALGraph() {
	for (int i = 1; i <= n; i++) {
		EdgeNode<T>* p = h[i].next;
		while (p) {
			EdgeNode<T>* now = p;
			p = p->next;
			delete now;
		}
	}
}


// -------------------------以下为私有函数--------------------------


template<class T>
void ALGraph<T>::add(int u, int v) {
	EdgeNode<T>* node = new EdgeNode<T>(v);
	node->next = h[u].next;
	h[u].next = node;
}

template<class T>
void ALGraph<T>::add(int u, int v, T w) {
	EdgeNode<T>* node = new EdgeNode<T>(v, w);
	node->next = h[u].next;
	h[u].next = node;
}


// -------------------------以下为用户可调用函数--------------------------


template<class T>
void ALGraph<T>::dfs() {
	// 辅助变量
	vector<bool> vis(n + 1, false);

	// 深搜函数
	function<void(int)> dfs = [&](int now) {
		cout << now << " ";
		vis[now] = true;
		for (EdgeNode<T>* p = h[now].next; p; p = p->next)
			if (!vis[p->toid])
				dfs(p->toid);
	};

	// 遍历连通分量
	for (int i = 1; i <= n; i++)
		if (!vis[i])
			dfs(i);
}

template<class T>
void ALGraph<T>::bfs() {
	vector<bool> vis(n + 1, false);

	auto bfs = [&](int hh) {
		queue<T> q;
		q.push(hh);
		vis[hh] = true;

		while (q.size()) {
			auto now = q.front();
			q.pop();

			cout << now << " ";

			for (EdgeNode<T>* p = h[now].next; p; p = p->next) {
				if (!vis[p->toid]) {
					vis[p->toid] = true;
					q.push(p->toid);
				}
			}
		}
	};

	// 遍历连通分量
	for (int i = 1; i <= n; i++)
		if (!vis[i])
			bfs(i);
}

template<class T>
bool ALGraph<T>::FindPathFromA2B(int a, int b) {
	// 越界判断
	if (a < 1 || a > n || b < 1 || b > n) {
		cerr << "Wrong Input! Out of Range!\n";
		exit(1);
	}

	// 辅助变量
	vector<bool> vis(n + 1, false);
	bool ok = false;

	// 宽搜函数
	auto bfs = [&](int hh) {
		queue<int> q;
		q.push(hh);

		while (q.size()) {
			auto now = q.front();
			q.pop();
			vis[now] = true;

			// 搜到路径了直接结束搜索
			if (now == b) {
				ok = true;
				break;
			}

			for (EdgeNode<T>* p = h[now].next; p; p = p->next) {
				if (!vis[p->toid]) {
					vis[p->toid] = true;
					q.push(p->toid);
				}
			}
		}
	};

	// 调用过程并返回答案
	bfs(a);
	return ok;
}

template<class T>
bool ALGraph<T>::FindPathFromA2BLengthK(int a, int b, int k) {
	// 越界判断
	if (a < 1 || a > n || b < 1 || b > n) {
		cerr << "Wrong Input! Out of Range!\n";
		exit(1);
	}

	// 辅助变量
	vector<vector<int>> paths;
	vector<int> path;
	vector<bool> vis(n + 1, false);

	// 深搜函数
	function<void(int)> dfs = [&](int now) {
		vis[now] = true;
		path.push_back(now);

		if (now == b && path.size() - 1 == k) {
			paths.push_back(path);
			path.pop_back();
			vis[now] = false;
			return;
		}

		for (EdgeNode<T>* p = h[now].next; p; p = p->next)
			if (!vis[p->toid])
				dfs(p->toid);

		path.pop_back();
		vis[now] = false;
	};

	// 调用并返回
	dfs(a);
	return paths.size() >= 1;
}

#endif //INC_3__DATASTRUCTURES_ALGRAPH_H
