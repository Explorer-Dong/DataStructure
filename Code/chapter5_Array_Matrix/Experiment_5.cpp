//
// Created by Wenjie Dong on 2023-10-23.
//

#include <vector>
#include "./Triple.h"
#include "./SparseMatrix.h"

using namespace std;

class Experiment_5 {
public:
    // Exp5 test sparse matrix: transpose, plus, minus
    void testSparseMatrix() {
        /* init a sparse matrix
         * 1 2 3
         * 4 5 6
         */
        SparseMatrix<int> sm;
        sm.update(Triple<int>(0, 0, 1));
        sm.update(Triple<int>(0, 1, 2));
        sm.update(Triple<int>(0, 2, 3));
        sm.update(Triple<int>(1, 0, 4));
        sm.update(Triple<int>(1, 1, 5));
        sm.update(Triple<int>(1, 2, 6));
        
        // transpose
        vector<vector<int>> trans = sm.transpose();
        cout << "transpose result:\n";
        for (int i = 0; i < trans.size(); i++) {
            for (int j = 0; j < trans[0].size(); j++) {
                cout << trans[i][j] << " \n"[j == trans[0].size() - 1];
            }
        }

        // plus
        vector<vector<int>> plus = sm.plus(sm);
        cout << "\nplus result:\n";
        for (int i = 0; i < plus.size(); i++) {
            for (int j = 0; j < plus[0].size(); j++) {
                cout << plus[i][j] << " \n"[j == plus[0].size() - 1];
            }
        }
        
        // minus
        vector<vector<int>> minus = sm.minus(sm);
        cout << "\nminus result:\n";
        for (int i = 0; i < minus.size(); i++) {
            for (int j = 0; j < minus[0].size(); j++) {
                cout << minus[i][j] << " \n"[j == minus[0].size() - 1];
            }
        }
    }
};