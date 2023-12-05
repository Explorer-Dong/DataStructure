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
	T INF = numeric_limits<T>::max();

public:
	MGraph(GraphType _kind, vector<int>& _vexs, vector<pair<int, int>>& _edges);         // 图
	MGraph(GraphType _kind, vector<int>& _vexs, vector<tuple<int, int, T>>& _edges);     // 网
	~MGraph() {}

	void dfs();
	void bfs();
	vector<T> FindLoop();       // 有向图找环
	deque<T> FindLoop_un();     // 无向图找环
	T Prim(int v);
	vector<tuple<int, int, T>> Kruskal();
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
	edges.resize(n + 1, vector<T>(n + 1, INF));

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

template<class T>
deque<T> MGraph<T>::FindLoop_un() {
	deque<T> loop;

	vector<bool> vis(n + 1, false);
	deque<T> path;
	bool ok = false;

	// 深搜函数
	function<void(int, int)> dfs = [&](int before, int now) {
		if (ok) return;

		if (vis[now]) {
			ok = true;
			while (path.front() != now) path.pop_front();
			loop = path;
			return;
		}

		vis[now] = true;
		path.push_back(now);

		for (int i = 1; i <= n; i++)
			if (edges[now][i] && i != before)
				dfs(now, i);

		vis[now] = false;
		path.pop_back();
	};

	// 选择探索起点 - 任意选择一个点即可
	dfs(-1, 1);

	return loop;
}

template<class T>
T MGraph<T>::Prim(int v) {
	T length = 0;

	vector<T> d(n + 1, INF); // d[i]表示i号点到集合MST中的最短边长
	vector<bool> MST(n + 1, false);

	auto min = [&](T a, T b) {
		return a < b ? a : b;
	};

	/* 1. 选择一个点到集合MST中 */
	MST[v] = true;
	for (int i = 1; i <= n; i++)
		if (!MST[i])
			d[i] = min(d[i], edges[i][v]);

	/* 2. 迭代n-1次，选择其他的点到集合MST中 */
	for (int i = 2; i <= n; i++) {
		// 找到交叉边中的最短边min_e和其在U-MST集合中的顶点vex
		T min_e = INF;
		int vex;
		for (int j = 1; j <= n; j++)
			if (!MST[j] && d[j] < min_e)
				min_e = d[j], vex = j;

		// 加入MST集合
		MST[vex] = true;
		if (min_e == INF) {
			cerr << "unable to generate MST!\n";
			exit(1);
		} else {
			length += min_e;
		}

		// 迭代更新d数组
		for (int j = 1; j <= n; j++)
			if (!MST[j])
				d[j] = min(d[j], edges[j][vex]);
	}

	return length;
}

template<class T>
vector<tuple<int, int, T>> MGraph<T>::Kruskal() {
	vector<tuple<int, int, T>> res, edges_set;

	// 获取边集
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (edges[i][j]) {
				edges_set.push_back({i, j, edges[i][j]});
			}
		}
	}

	/* 1. 按边权升序排序 */
	sort(edges_set.begin(), edges_set.end(), [&](tuple<int, int, T>& x, tuple<int, int, T>& y){
		return get<2>(x) < get<2>(y);
	});

	/* 2. 选边构造MST */

	// dsu
	vector<int> p(n + 1);
	for (int i = 1; i <= n; i++) {
		p[i] = i;
	}
	function<int(int)> Find = [&](int now) {
		if (p[now] != now) {
			p[now] = Find(p[now]);
		}
		return p[now];
	};

	// 选边
	int cnt = 0; // 统计选择的边数
	for (auto& edge: edges_set) {
		int u = get<0>(edge), v = get<1>(edge);
		T weight = get<2>(edge);

		int pu = Find(u), pv = Find(v);
		if (pu != pv) {
			p[pu] = pv;
			res.push_back({u, v, weight});
			cnt++;
		}

		if (cnt == n - 1) {
			break;
		}
	}

	if (cnt < n - 1) {
		cerr << "unable to generate MST!\n";
		exit(1);
	}

	return res;
}
#endif //INC_3__DATASTRUCTURES_MGRAPH_H
