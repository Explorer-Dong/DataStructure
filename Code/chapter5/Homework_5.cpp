//
// Created by 董文杰 on 2023-10-19.
//

#include <bits/stdc++.h>

using namespace std;

class Homework_5 {
public:
	// T 5.2 计算鞍点，即行最小且列最大
	vector<pair<int, int>> Saddle(vector<vector<int>>& g) {
		vector<pair<int, int>> res;

		if (g.empty() || g[0].empty()) {
			return res;
		}

		int n = g.size(), m = g[0].size();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				bool row_min = true, col_max = true;
				for (int k = 0; k < m; k++) {
					if (g[i][k] < g[i][j]) {
						row_min = false;
						break;
					}
				}
				for (int k = 0; k < n; k++) {
					if (g[k][j] > g[i][j]) {
						col_max = false;
						break;
					}
				}
				if (row_min && col_max) {
					res.emplace_back(make_pair(i, j));
				}
			}
		}

		return res;
	}


	// T 5.3 计算稀疏矩阵的主对角线元素之和
	int SumOfDiag(vector<array<int, 3>>& a) {
		int res = 0;

		int n = a.size();
		for (int i = 0; i < n; i++) {
			if (a[i][0] == a[i][1]) {
				res += a[i][2];
			}
		}

		return res;
	}
};