//
// Created by Wenjie Dong on 2023-11-27.
//

#include <bits/stdc++.h>
#include "MGraph.h"
#include "ALGraph.h"

using namespace std;

class Trail_8 {
public:
	// -------------------------------实验1-------------------------------

	// 8.1 (1) 建立无向图 - 邻接矩阵
	void Mbuild() {
		vector<int> vexs = {1, 2, 3, 4, 5, 6, 7, 8};
		vector<pair<int, int>> edges = {{1, 2}, {1, 3}, {3, 4}, {3, 5}, {3, 6}, {3, 8}, {5, 6}, {4, 7}, {8, 7}};
		MGraph<int> G(undigraph, vexs, edges);

		// 补充：无向网
		vector<int> vexs2 = {1, 2, 3, 4, 5, 6, 7, 8};
		vector<tuple<int, int, int>> edges2 = {{1, 2, 2}, {1, 3, 4}, {3, 4, 1}, {3, 5, 3}, {3, 6, 6}, {3, 8, 7}, {5, 6, 5}, {4, 7, 8}, {8, 7, 9}};
		MGraph<int> G2(undinetwork, vexs2, edges2);
	}

	// 8.1 (2) 建立无向图 - 邻接表
	void ALbuild() {
		vector<int> vexs = {1, 2, 3, 4};
		vector<pair<int, int>> edges = {{1, 2}, {1, 3}, {1, 4}, {2, 3}, {3, 4}};
		ALGraph<int> G(undigraph, vexs, edges);

		// 补充：无向网
		vector<int> vexs2 = {1, 2, 3, 4};
		vector<tuple<int, int, double>> edges2 = {{1, 2, 2.5}, {1, 3, 4.0}, {1, 4, 1.6}, {2, 3, 3.9}, {3, 4, 6.2}};
		ALGraph<double> G2(undinetwork, vexs, edges);
	}

	// 8.1 (3) 基于邻接矩阵的dfs
	void Mdfs() {
		vector<int> vexs = {1, 2, 3, 4};
		vector<pair<int, int>> edges = {{2, 3}, {1, 2}, {3, 4}, {1, 4}, {1, 3}};
		MGraph<int> G(undigraph, vexs, edges);
		G.dfs();
	}

	// 8.1 (3) 基于邻接表的dfs
	void ALdfs() {
		vector<int> vexs = {1, 2, 3, 4};
		vector<pair<int, int>> edges = {{2, 3}, {1, 2}, {3, 4}, {1, 4}, {1, 3}};
		ALGraph<int> G(undigraph, vexs, edges);
		G.dfs();
	}

	// 8.1 (3) 基于邻接矩阵的bfs
	void Mbfs() {
		vector<int> vexs = {1, 2, 3, 4};
		vector<pair<int, int>> edges = {{2, 3}, {1, 2}, {3, 4}, {1, 4}, {1, 3}};
		MGraph<int> G(undigraph, vexs, edges);
		G.bfs();
	}

	// 8.1 (3) 基于邻接表的bfs
	void ALbfs() {
		vector<int> vexs = {1, 2, 3, 4};
		vector<pair<int, int>> edges = {{2, 3}, {1, 2}, {3, 4}, {1, 4}, {1, 3}};
		ALGraph<int> G(undigraph, vexs, edges);
		G.bfs();
	}

	// -------------------------------实验2-------------------------------

	// 8.2 (1) 基于邻接矩阵(无向网)的Prim求解
	void Prim() {
		vector<int> vexs = {1, 2, 3};
		vector<tuple<int, int, double>> edges = {
				{1, 2, 5.5},
				{1, 3, 4.0},
				{2, 3, 10.0}
		};
		MGraph<double> G(undinetwork, vexs, edges);

		double length = G.Prim(1);
		cout << length << "\n";
	}

	// 8.2 (2) 基于邻接矩阵(无向网)的Kruskal求解
	void Kruskal() {
		vector<int> vexs = {1, 2, 3};
		vector<tuple<int, int, double>> edges = {
				{1, 2, 5.5},
				{1, 3, 4.0},
				{2, 3, 10.0}
		};
		MGraph<double> G(undinetwork, vexs, edges);

		vector<tuple<int, int, double>> MST_edges = G.Kruskal();
		for (auto& x: MST_edges) {
			cout << get<0>(x) << " --> " << get<1>(x) << " weight: " << get<2>(x) << "\n";
		}
	}

	// -------------------------------实验3-------------------------------

	// 8.3 (1) Dijkstra 单源最短路 - 朴素版 O(n^2)
	void Dijkstra() {
		vector<int> vexs = {1, 2, 3, 4, 5};
		vector<tuple<int, int, int>> edges = {
				{1, 2, 10}, {1, 4, 30}, {1, 5, 100},
				{2, 3, 50},
				{3, 5, 10},
				{4, 3, 20}, {4, 5, 60}
		};
		MGraph<int> G(dinetwork, vexs, edges);
		vector<int> path = G.Dijkstra(1, 3);
		for (auto& road: path) {
			cout << road << " ";
		}
	}

	// 8.3(2) Floyd多源最短路 - O(n^3)
	void Floyd() {
		vector<int> vexs = {1, 2, 3, 4, 5};
		vector<tuple<int, int, int>> edges = {
				{1, 2, 10}, {1, 4, 30}, {1, 5, 100},
				{2, 3, 50},
				{3, 5, 10},
				{4, 3, 20}, {4, 5, 60}
		};
		MGraph<int> G(dinetwork, vexs, edges);
		vector<tuple<int, int, vector<int>>> paths = G.Floyd();
		for (auto& path: paths) {
			cout << get<0>(path) << "->" << get<1>(path) << ":\n";
			for (auto& road: get<2>(path)) {
				cout << road << " ";
			}
			cout << "\n\n";
		}
	}
};