//
// Created by Wenjie Dong on 2023-10-23.
//

#include <iostream>
#include <vector>
#include "Triple.h"

using namespace std;

#ifndef INC_3__DATASTRUCTURES_SPARSEMATRIX_H
#define INC_3__DATASTRUCTURES_SPARSEMATRIX_H

template<class T>
class SparseMatrix {
private:
	vector<Triple<T>> data;
	int row, col, size;

public:
	SparseMatrix() : row(0), col(0), size(0) {};
	SparseMatrix(vector<vector<T>>& obj);
	vector<vector<T>> Trans();
	vector<vector<T>> Plus(SparseMatrix& obj);
	vector<vector<T>> Minus(SparseMatrix& obj);
};

template<class T>
SparseMatrix<T>::SparseMatrix(vector<vector<T>>& obj) {
	if (obj.empty() || obj[0].empty()) {
		return;
	}

	row = obj.size(), col = obj[0].size();

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (obj[i][j]) {
				Triple<T> t(i, j, obj[i][j]);
				data.emplace_back(t);
				size++;
			}
		}
	}
}

template<class T>
vector<vector<T>> SparseMatrix<T>::Trans() {
	vector<vector<T>> res(col, vector<T>(row, 0));

	for (auto& x: data) {
		int i = x.r, j = x.c;
		T val = x.elem;
		res[j][i] = val;
	}

	return res;
}

template<class T>
vector<vector<T>> SparseMatrix<T>::Plus(SparseMatrix<T>& obj) {
	if (row != obj.row || col != obj.col) {
		cerr << "形状不同！" << "\n";
		exit(1);
	}

	vector<vector<T>> res(row, vector<T>(col, 0));

	for (auto& x: data) {
		int i = x.r, j = x.c;
		T val = x.elem;
		res[i][j] += val;
	}

	for (auto& x: obj.data) {
		int i = x.r, j = x.c;
		T val = x.elem;
		res[i][j] += val;
	}

	return res;
}

template<class T>
vector<vector<T>> SparseMatrix<T>::Minus(SparseMatrix<T>& obj) {
	if (row != obj.row || col != obj.col) {
		cerr << "形状不同！" << "\n";
		exit(1);
	}

	vector<vector<T>> res(row, vector<T>(col, 0));

	for (auto& x: data) {
		int i = x.r, j = x.c;
		T val = x.elem;
		res[i][j] += val;
	}

	for (auto& x: obj.data) {
		int i = x.r, j = x.c;
		T val = x.elem;
		res[i][j] -= val; // 与加法唯一的区别
	}

	return res;
}

#endif //INC_3__DATASTRUCTURES_SPARSEMATRIX_H
