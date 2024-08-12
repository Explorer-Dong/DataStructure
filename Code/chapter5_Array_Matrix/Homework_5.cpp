//
// Created by Wenjie Dong on 2023-10-19.
//

#include <vector>
#include <array>
#include <climits>
#include "SparseMatrix.h"

using namespace std;

class Homework_5 {
public:
    // T5.2 get all saddles of a matrix
    vector<pair<int, int>> getSaddlesOfMatrix(
            const vector<vector<int>>& mat = {{0,  2, 0},
                                              {-1, 2, -2}}) {
        if (mat.empty() || mat[0].empty()) {
            return {};
        }
        
        vector<pair<int, int>> res;
        int n = mat.size(), m = mat[0].size();
        vector<int> r(m, INT_MAX), c(n, INT_MIN);
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                r[i] = min(r[i], mat[i][j]);
                c[j] = max(c[j], mat[i][j]);
            }
        }
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (mat[i][j] <= r[i] && mat[i][j] >= c[j]) {
                    res.push_back({i, j});
                }
            }
        }
        
        return res;
    }
    
    
    // T5.3 calc sum of the diagonal elements of a sparse matrix
    int calcDiagSumOfSparseMatrix() {
        SparseMatrix<int> sm;
        sm.update(Triple<int>(0, 0, 3));
        sm.update(Triple<int>(1, 2, 3));
        sm.update(Triple<int>(3, 3, 9));
        return sm.sumOfDiag();
    }
};