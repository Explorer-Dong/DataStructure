//
// Created by Wenjie Dong on 2023-10-23.
//

#include <bits/stdc++.h>
#include "SparseMatrix.h"

using namespace std;

class Trail_5 {
public:
	// Tr 5.1 ͨ����Ԫ�鲻�ϳ�ʼ��ϡ�����ʵ�־���ת�á��ӷ�������������Ϊһ�����о���
	void TrSparseMatrix() {
		// ��ʼ������
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

		// ת��
		vector<vector<int>> trans = spa.Trans();
		cout << "ת�ý��\n";
		for (auto& row: trans) {
			for (auto& x: row) {
				cout << x << ' ';
			}
			cout << "\n";
		}

		// �ӷ�
		vector<vector<int>> plus = spa.Plus(sppl);
		cout << "�ӷ����\n";
		for (auto& row: plus) {
			for (auto& x: row) {
				cout << x << ' ';
			}
			cout << "\n";
		}

		// ����
		vector<vector<int>> minus = spa.Minus(spmi);
		cout << "�������\n";
		for (auto& row: minus) {
			for (auto& x: row) {
				cout << x << ' ';
			}
			cout << "\n";
		}
	}
};