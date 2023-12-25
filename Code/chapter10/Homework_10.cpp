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
	void InsertNum2Heap(vector<int>& a, int num) {
		// resize
		int n = a.size();
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

	// T4 merge two ordered seq
	vector<int> MergeTwoOrderedSeq(vector<int>& a, vector<int>& b) {
		vector<int> res(a.size() + b.size());

		int i = 0, j = 0, k = 0;
		while (i < a.size() && j < b.size()) {
			if (a[i] < b[j]) res[k++] = a[i++];
			else res[k++] = b[j++];
		}

		while (i < a.size()) res[k++] = a[i++];
		while (j < b.size()) res[k++] = b[j++];

		return res;
	}

	// T5 count reverse order
	int CountReverseOrder(vector<int>& a) {
		int cnt = 0;

		function<void(int, int)> mergeSort = [&](int l, int r) {
			if (l >= r) return;

			// divide
			int mid = (l + r) >> 1;

			// conquer
			mergeSort(l, mid), mergeSort(mid + 1, r);

			// combine
			int t[a.size()], i = l, j = mid + 1, k = 0;
			while (i <= mid && j <= r) {
				if (a[i] <= a[j]) t[k++] = a[i++];
				else {
					t[k++] = a[j++];
					cnt += mid - i + 1;     // count
				}
			}
			while (i <= mid) t[k++] = a[i++];
			while (j <= r) t[k++] = a[j++];

			for (i = l, k = 0; i <= r; i++) a[i] = t[k++];
		};

		mergeSort(0, a.size() - 1);

		return cnt;
	}
};