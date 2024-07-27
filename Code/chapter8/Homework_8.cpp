//
// Created by Wenjie Dong on 2023-11-27.
//

#include <bits/stdc++.h>
#include "MGraph.h"
#include "ALGraph.h"

using namespace std;

class Homework_8 {
public:
	// T1 dfs遍历图 - 邻接表
	void Trans() {
		vector<int> vexs = {1, 2, 3, 4};
		vector<pair<int, int>> edges = {{2, 3}, {1, 2}, {3, 4}, {1, 4}, {1, 3}};
		ALGraph<int> G(undigraph, vexs, edges);
		G.dfs();
	}

	// T2 bfs找u到v的路径 - 邻接表
	void FindPath() {
		vector<int> vexs = {1, 2, 3, 4};
		vector<pair<int, int>> edges = {{2, 3}, {1, 2}, {3, 4}, {1, 4}, {1, 3}};
		ALGraph<int> G(undigraph, vexs, edges);
		int a = 2, b = 4;
		cout << G.FindPathFromA2B(a, b) << endl;
	}

	// T3 无向图寻找u到v长度为k的路径 - 邻接表
	void FindPathLengthK() {
		vector<int> vexs = {1, 2, 3, 4, 5, 6, 7};
		vector<pair<int, int>> edges = {
				{1, 2}, {1, 6},
				{2, 3}, {2, 4}, {2, 5},
				{3, 4}, {3, 7},
				{6, 7},
		};
		ALGraph<int> G(undigraph, vexs, edges);
		int a = 7, b = 2, k = 3;
		cout << G.FindPathFromA2BLengthK(a, b, k) << endl;
	}

	// T4 有向图判环 - 邻接矩阵
	void FindLoop() {
		vector<int> vexs = {1, 2, 3, 4, 5, 6, 7};
		vector<pair<int, int>> edges = {
				{1, 2}, {6, 1},
				{2, 3}, {4, 2}, {2, 5},
				{3, 4}, {3, 7},
				{7, 6}, {7, 9}
//				{1, 2}, {6, 1},
//				{2, 3}, {2, 5},
//				{3, 7},
//				{7, 6}, {7, 9}
		};
		MGraph<int> G(digraph, vexs, edges);
		vector<int> loop = G.FindLoop();
		for (auto& road: loop) {
			cout << road << ' ';
		}
	}

	// T5 无向图寻找回路 - 邻接矩阵
	void FindLoop_un() {
		vector<int> vexs = {1, 2, 3, 4, 5, 6, 7};
		vector<pair<int, int>> edges = {
				{1, 2}, {1, 6},
				{2, 3}, {2, 4}, {2, 5},
				{3, 4}, {3, 7},
				{6, 7},
		};
		MGraph<int> G(undigraph, vexs, edges);

		auto loop = G.FindLoop_un();

		while (loop.size()) {
			auto road = loop.front();
			loop.pop_front();
			cout << road << " ";
		}
	}

	// T6 prim & kruskal
	void MST() {
		vector<int> vexs = {1, 2, 3, 4, 5, 6, 7, 8};
		vector<tuple<int, int, int>> edges = {
				{1, 2, 2}, {1, 3, 3},
				{2, 4, 2}, {3, 4, 1},
				{4, 5, 2}, {4, 6, 4},
				{5, 7, 5}, {5, 6, 1},
				{6, 7, 2}, {6, 8, 1},
				{7, 8, 1}
		};
		MGraph<int> G(undinetwork, vexs, edges);

		int length = G.Prim(1);
		cout << length << "\n";

		auto res = G.Kruskal();
		for (auto& x: res) {
			cout << get<0>(x) << " --> " << get<1>(x) << " weight: " << get<2>(x) << "\n";
		}
	}
};
