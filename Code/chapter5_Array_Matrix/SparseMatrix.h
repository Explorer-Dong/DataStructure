#include <iostream>
#include <vector>
#include "./Triple.h"

using namespace std;

#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

template<class T>
class SparseMatrix {
private:
    vector<Triple<T>> data;
    int row, col;
    const int MaxSize;

public:
    SparseMatrix() : row(0), col(0), MaxSize(1000) {};
    void update(Triple<T> x);
    vector<vector<T>> transpose();
    vector<vector<T>> plus(SparseMatrix& sm, bool is_plus = true);
    vector<vector<T>> minus(SparseMatrix& sm);
    T sumOfDiag();
};

template<class T>
void SparseMatrix<T>::update(Triple<T> x) {
    data.push_back(x);
    row = max(row, x.r);
    col = max(col, x.c);
    if (row > MaxSize || col > MaxSize) {
        cerr << "matrix is too big to contain!" << "\n";
        exit(1);
    }
}

template<class T>
vector<vector<T>> SparseMatrix<T>::transpose() {
    swap(row, col);
    vector<vector<T>> res(row + 1, vector<T>(col + 1, 0));
    for (auto& tri: data) {
        res[tri.c][tri.r] = tri.value;
        swap(tri.r, tri.c);
    }
    return res;
}

template<class T>
vector<vector<T>> SparseMatrix<T>::plus(SparseMatrix<T>& sm, bool is_plus) {
    if (row != sm.row || col != sm.col) {
        cerr << "different shape! can't calculate" << "\n";
        exit(1);
    }
    
    vector<vector<T>> res(row + 1, vector<T>(col + 1, 0));
    for (auto& tri: data) {
        int r = tri.r, c = tri.c;
        T value = tri.value;
        res[r][c] += value;
    }
    for (auto& tri: sm.data) {
        int r = tri.r, c = tri.c;
        T value = tri.value;
        res[r][c] += is_plus ? value : -value;
    }
    
    return res;
}

template<class T>
vector<vector<T>> SparseMatrix<T>::minus(SparseMatrix<T>& sm) {
    return plus(sm, false);
}

template<class T>
T SparseMatrix<T>::sumOfDiag() {
    T res = 0;
    for (auto t: data) {
        if (t.r == t.c) {
            res += t.value;
        }
    }
    return res;
}

#endif //SPARSEMATRIX_H