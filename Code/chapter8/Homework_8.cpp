//
// Created by 董文杰 on 2023-11-27.
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

	// T2 bfs找u到v的路径 - 邻接表 TODO
	void FindRoad() {
		vector<int> vexs = {1, 2, 3, 4};
		vector<pair<int, int>> edges = {{2, 3}, {1, 2}, {3, 4}, {1, 4}, {1, 3}};
		ALGraph<int> G(undigraph, vexs, edges);
		cout << G.FindPathFromA2B(2, 4) << endl;
	}
};
