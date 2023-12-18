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
	int n, e;                               // 点数和边数
	GraphType kind;                         // 图类型
	vector<int> vexs;                       // 点集
	vector<vector<T>> edges;                // 边集(邻接矩阵)
	T INF = numeric_limits<T>::max() / 2;   // 最大值，之所以需要除以2是因为后续操作会爆int！

public:
	MGraph(GraphType _kind, vector<int>& _vexs, vector<pair<int, int>>& _edges);         // 图
	MGraph(GraphType _kind, vector<int>& _vexs, vector<tuple<int, int, T>>& _edges);     // 网
	~MGraph() {}

	void dfs();
	void bfs();
	vector<T> FindLoop();                            // 有向图找环
	deque<T> FindLoop_un();                          // 无向图找环
	T Prim(int v);                                   // MST
	vector<tuple<int, int, T>> Kruskal();            // MST
	vector<int> Dijkstra(int a, int b);              // 单源最短路 (a->b)
	vector<tuple<int, int , vector<int>>> Floyd();   // 多源最短路
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

template<class T>
vector<int> MGraph<T>::Dijkstra(int a, int b) {
	vector<int> res;                    // a->b 的最短路径
	vector<int> pre(n + 1, 0);          // SPT(shortest path tree) 中每一个结点的前驱结点
	vector<int> d(n + 1, INF);          // d[i] 表示源点 a 到 i 号点的最短路径长度
	vector<bool> SPT(n + 1, false);     // 标记 i 号点是否在 SPT 集合中

	d[a] = 0;

	// 将a号点加入SPT集合
	SPT[a] = true;
	pre[a] = -1;
	for (int j = 1; j <= n; j++)
		if (!SPT[j] && d[j] > d[a] + edges[a][j]) {
			/**
			 * @note d[j] > d[vex] + edges[vex][j] 注意爆int
			 */
			pre[j] = a;
			d[j] = d[a] + edges[a][j];
		}

	// 迭代更新n-1次
	for (int i = 1; i <= n - 1; i++) {
		// 1. 选择最短边对应的点vex
		int vex = -1;
		for (int j = 1; j <= n; j++)
			if (!SPT[j] && (vex == -1 || d[j] < d[vex]))
				vex = j;

		// 2. 将选出的点加入SPT集合
		SPT[vex] = true;

		// 3. 更新V-SPT中的点到源点的最短距离 & 记录被更新的点的前驱结点为vex
		for (int j = 1; j <= n; j++)
			if (!SPT[j] && d[j] > d[vex] + edges[vex][j]) {
				/**
				 * @note d[j] > d[vex] + edges[vex][j] 注意爆int
				 */
				pre[j] = vex;
				d[j] = d[vex] + edges[vex][j];
			}
	}

	// 求解最短路径
	while (b != -1) {
		res.push_back(b);
		b = pre[b];
	}
	reverse(res.begin(), res.end());

	return res;
}

template<class T>
vector<tuple<int, int, vector<int>>> MGraph<T>::Floyd() {
	/**
	 * @note more detailed info about spatial optimization: https://www.acwing.com/solution/content/218719/
	 */
	vector<tuple<int, int, vector<int>>> res;

	int d[n + 1][n + 1] {};     // d[i][j] means i to j shortest path length
	int aft[n + 1][n + 1] {};   // aft[i][j] means i to j first pass vex

	// init
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i == j) {
				d[i][j] = 0;
			} else {
				d[i][j] = INF;
			}
		}
	}

	// base
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i == j) continue;
			if (edges[i][j] != INF) {
				d[i][j] = edges[i][j];
				aft[i][j] = j;
			} else {
				d[i][j] = INF;
			}
		}
	}

	// dp
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (d[i][k] != INF && d[k][j] != INF && d[i][k] + d[k][j] < d[i][j]) {
					d[i][j] = d[i][k] + d[k][j];
					aft[i][j] = k; // aft[i][j] = aft[i][k] = k
				}
			}
		}
	}

	// result
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (d[i][j] != INF && d[i][j]) {
				vector<int> path;
				path.push_back(i);

				int next = aft[i][j];
				while (next != j) {
					path.push_back(next);
					next = aft[next][j];
				}

				path.push_back(j);
				res.push_back({i, j, path});
			}
		}
	}

	return res;
}
#endif //INC_3__DATASTRUCTURES_MGRAPH_H
