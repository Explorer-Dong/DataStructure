//
// Created by 董文杰 on 2023-12-18.
//

#include <bits/stdc++.h>

using namespace std;

class Homework_10 {
public:
	// T1 neg left & posi right -> two points
	void clarify() {
		int n = 10;
		int x[10] = {-1, 4, 2, -3, -9, -10, 3, 5, -6, -7};

		int l = 0, r = n - 1;
		while (l < r) {
			while (x[l] < 0) l++;
			while (x[r] > 0) r--;
			if (l < r) swap(x[l], x[r]);
		}

		for (int i = 0; i < n; i++) {
			cout << x[i] << " \n"[i == n - 1];
		}
	}

	// T2 non-recursive QuickSort
	void _QuickSort() {
		int n = 10;
		int x[10] = {-1, 4, 2, -3, -9, -10, 3, 5, -6, -7};

		auto partition = [&](int l, int r) {
			int i = l - 1, j = r + 1, m = x[(l + r) >> 1];
			while (i < j) {
				while (x[++i] < m);
				while (x[--j] > m);
				if (i < j) swap(x[i], x[j]);
			}
			return j;
		};

		struct board {
			int l, r;
		};

		stack<board> stk;
		stk.push({0, n - 1});

		while (stk.size()) {
			auto h = stk.top();
			stk.pop();

			int l = h.l, r = h.r;
			if (l >= r) continue;

			int j = partition(l, r);

			stk.push({l, j});
			stk.push({j + 1, r});
		}

		for (int i = 0; i < n; i++) {
			cout << x[i] << " \n"[i == n - 1];
		}
	}
};