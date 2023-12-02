//
// Created by 董文杰 on 2023-11-27.
//

#include <bits/stdc++.h>
using namespace std;

#ifndef INC_3__DATASTRUCTURES_MGRAPH_H
#define INC_3__DATASTRUCTURES_MGRAPH_H

enum GraphType {undigraph, undinetwork, digraph, dinetwork};

template<class T>
class MGraph {
private:
	int n, e;                   // 点数和边数
	GraphType kind;             // 图类型
	vector<int> vexs;           // 点集
	vector<vector<T>> edges;    // 边集(邻接矩阵)

public:
	MGraph(GraphType _kind, vector<int>& _vexs, vector<pair<int, int>>& _edges);         // 图
	MGraph(GraphType _kind, vector<int>& _vexs, vector<tuple<int, int, T>>& _edges);     // 网
	~MGraph() {}

	void dfs();
	void bfs();
	vector<T> FindLoop();
};


// -------------------------以下为构造与析构函数--------------------------


template<class T>
MGraph<T>::MGraph(GraphType _kind, vector<int>& _vexs, vector<pair<int, int>>& _edges) {
	n = _vexs.size(), e = _edges.size();
	kind = _kind;
	vexs = _vexs;
	edges.resize(n + 1, vector<T>(n + 1, 0));       // 结点下标从1开始

	if (kind == undigraph) {
		for (auto& edge: _edges) {
			T u = edge.first, v = edge.second;
			edges[u][v] = 1;
			edges[v][u] = 1;
		}
	} else { // kind == digraph
		for (auto& edge: _edges) {
			int u = edge.first, v = edge.second;
			edges[u][v] = 1;
		}
	}
}

template<class T>
MGraph<T>::MGraph(GraphType _kind, vector<int>& _vexs, vector<tuple<int, int, T>>& _edges) {
	n = _vexs.size(), e = _edges.size();
	kind = _kind;
	vexs = _vexs;
	edges.resize(n + 1, vector<T>(n + 1, 0));

	if (kind == undinetwork) {
		for (auto& edge: _edges) {
			int u = get<0>(edge), v = get<1>(edge);
			T w = get<2>(edge);
			edges[u][v] = w;
			edges[v][u] = w;
		}
	} else { // kind == dinetwork
		for (auto& edge: _edges) {
			int u = get<0>(edge), v = get<1>(edge);
			T w = get<2>(edge);
			edges[u][v] = w;
		}
	}
}


// -------------------------以下为私有函数--------------------------





// -------------------------以下为用户可调用函数--------------------------


template<class T>
void MGraph<T>::dfs() {
	vector<bool> vis(n + 1, false);

	function<void(int, vector<bool>&)> dfs = [&](int now, vector<bool>& vis) {
		cout << now << " ";
		vis[now] = true;
		for (int i = 1; i <= n; i++) {
			if (edges[now][i] && !vis[i]) {
				dfs(i, vis);
			}
		}
	};

	for (int i = 1; i <= n; i++) {
		if (!vis[i]) {
			dfs(i, vis);
		}
	}
}

template<class T>
void MGraph<T>::bfs() {
	vector<bool> vis(n + 1, false);

	auto bfs = [&](int hh) {
		queue<int> q;
		q.push(hh);

		while (q.size()) {
			auto now = q.front();
			q.pop();

			cout << now << " ";
			vis[now] = true;

			for (int i = 1; i <= n; i++) {
				if (edges[now][i] && !vis[i]) {
					vis[i] = true;  // 与树的宽搜的区别就在于此，需要在入队时就打标记 - 因为树是不会访问到已经访问过的点的，而图会
					q.push(i);
				}
			}
		}
	};

	for (int i = 1; i <= n; i++) {
		if (!vis[i]) {
			bfs(i);
		}
	}
}

template<class T>
vector<T> MGraph<T>::FindLoop() {
	vector<T> loop;

	bool ok = false;
	vector<bool> vis(n + 1, false), vis2(n + 1, false);

	// 存环
	function<void(int)> GetPath = [&](int now) {
		vis2[now] = true;
		loop.push_back(now);

		for (int i = 1; i <= n; i++)
			if (edges[now][i] && vis[i] && !vis2[i])
				GetPath(i);
	};

	// 判环
	function<void(int)> dfs = [&](int now) {
		if (ok) {
			return;
		}

		if (vis[now]) {
			ok = true;
			GetPath(now);
			return;
		}

		vis[now] = true;

		for (int i = 1; i <= n; i++)
			if (edges[now][i])
				dfs(i);

		vis[now] = false;
	};

	// 遍历连通分量
	for (int i = 1; i <= n; i++)
		if (!ok)
			dfs(i);

	return loop;
}

#endif //INC_3__DATASTRUCTURES_MGRAPH_H
