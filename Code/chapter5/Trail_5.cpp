//
// Created by Wenjie Dong on 2023-10-23.
//

#include <bits/stdc++.h>
#include "SparseMatrix.h"

using namespace std;

class Trail_5 {
public:
	// Tr 5.1 通过三元组不断初始化稀疏矩阵，实现矩阵转置、加法、减法，返回为一个阵列矩阵
	void TrSparseMatrix() {
		// 初始化构造
		vector<vector<int>> a = {
				{0, 0, 3, 0, 4, 0},
				{0, 0, 0, 0, 0, 1},
				{0, 0, 0, 0, 0, 0},
				{1, 0, 9, 0, 0, 0},
				{0, 0, 0, 0, 2, 0},
				{0, 0, 7, 0, 0, 0},
				{0, 0, 0, 0, 0, 0},
		};
		SparseMatrix<int> spa(a);

		vector<vector<int>> pl = {
				{0, 0, 3, 0, 4, 0},
				{0, 0, 0, 0, 0, 1},
				{0, 0, 0, 0, 0, 0},
				{1, 0, 9, 0, 0, 0},
				{0, 0, 0, 0, 2, 0},
				{0, 0, 7, 0, 0, 0},
				{0, 0, 0, 0, 0, 0},
		};
		SparseMatrix<int> sppl(pl);

		vector<vector<int>> mi = {
				{0, 0, 3, 0, 4, 0},
				{0, 0, 0, 0, 0, 1},
				{0, 0, 0, 0, 0, 0},
				{1, 0, 9, 0, 0, 0},
				{0, 0, 0, 0, 2, 0},
				{0, 0, 7, 0, 0, 0},
				{0, 0, 0, 0, 0, 0},
		};
		SparseMatrix<int> spmi(mi);

		// 转置
		vector<vector<int>> trans = spa.Trans();
		cout << "转置结果\n";
		for (auto& row: trans) {
			for (auto& x: row) {
				cout << x << ' ';
			}
			cout << "\n";
		}

		// 加法
		vector<vector<int>> plus = spa.Plus(sppl);
		cout << "加法结果\n";
		for (auto& row: plus) {
			for (auto& x: row) {
				cout << x << ' ';
			}
			cout << "\n";
		}

		// 减法
		vector<vector<int>> minus = spa.Minus(spmi);
		cout << "减法结果\n";
		for (auto& row: minus) {
			for (auto& x: row) {
				cout << x << ' ';
			}
			cout << "\n";
		}
	}
};