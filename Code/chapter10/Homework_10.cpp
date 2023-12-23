//
// Created by 董文杰 on 2023-12-18.
//

#include <bits/stdc++.h>
#include "Trail_10.cpp"

using namespace std;

class Homework_10 {
public:
	// T1 negitave left & positive right -> two points
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

	// T3 insert num to heap
	void InsertNum2Heap() {
		// ini heap
		int n = 10;
		vector<int> a = CreateHeap(n);

		// num to be inserted
		int num = 55;

		// fun insert
		a.resize(n + 1);

		/* 1. find pos to be inserted */
		int pos = n / 2 - 1;
		while (pos >= 0) {
			if (a[pos] < num) {
				if (pos % 2) pos = (pos - 1) / 2;
				else pos = (pos - 2) / 2;
			} else {
				break;
			}
		}

		/* 2. move path down */
		int i = n / 2 - 1, last = n;
		while (i >= pos) {
			if (i == pos) {
				a[last] = num;
				break;
			}
			a[last] = a[i];
			last = i;
			if (i % 2) i = (i - 1) / 2;
			else i = (i - 2) / 2;
		}
	}

	// create heap
	vector<int> CreateHeap(int n) {
		Trail_10 obj;
		vector<int> a = obj.Generate(n, 100);

		auto pushdown = [&](int top, int lim) {
			int j = 2 * top + 1;
			while (j <= lim) {
				j += j < lim && a[j] < a[j + 1];
				if (a[top] <= a[j]) {
					swap(a[top], a[j]);
					top = j;
					j = 2 * top + 1;
				} else {
					break;
				}
			}
		};

		for (int i = n / 2 - 1; i >= 0; i--) {
			pushdown(i, n - 1);
		}

		return a;
	}
};