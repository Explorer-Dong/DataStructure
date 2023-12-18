//
// Created by 董文杰 on 2023-12-18.
//

#include <bits/stdc++.h>

using namespace std;

class Trail_10 {
public:
	// Generate num random numbers in [0, range)
	vector<int> Generate(int num, int range) {
		srand(time(nullptr));
		vector<int> res;
		for (int i = 0; i < num; i++) {
			res.push_back(rand() % range);
		}
		return res;
	}

	// InsertSort
	int InsertSort(vector<int>& a) {
		int cnt = 0;

		auto Sort = [&]() {
			for (int i = 0; i < a.size(); i++) {
				// find insert pos
				int pos, temp = a[i];
				for (pos = i; pos >= 0; pos--)
					if (a[pos] < a[i])
						break;

				// move right & insert
				for (int j = i; j > pos + 1; j--)
					a[j] = a[j - 1], cnt++;
				a[pos + 1] = temp;
			}
		};

		Sort();

		return cnt;
	}

	// QuickSort
	int QuickSort(vector<int>& a) {
		int cnt = 0;

		function<void(int, int)> Sort = [&](int l, int r) {
			if (l == r) return;

			int i = l - 1, j = r + 1, x = a[(i + j) >> 1];
			while (i < j) {
				while (a[++i] < x);
				while (a[--j] > x);
				if (i < j) swap(a[i], a[j]), cnt++;
			}
			Sort(l, j);
			Sort(j + 1, r);
		};

		Sort(0, a.size() - 1);

		return cnt;
	}

	// HeapSort
	int HeapSort(vector<int>& a) {
		int cnt = 0;
		return cnt;
	}

	// MergeSort
	int MergeSort(vector<int>& a) {
		int cnt = 0;
		return cnt;
	}

	// Compare
	void Compare() {
		vector<int> a = Generate(3, 1000);

		for (auto& x: a) {
			cout << x << " ";
		} cout << endl;

		int insert_cnt = 0, quick_cnt = 0, heap_cnt = 0, merge_cnt = 0;

		insert_cnt = InsertSort(a);
		quick_cnt = QuickSort(a);
		heap_cnt = HeapSort(a);
		merge_cnt = MergeSort(a);

		cout << "insert count:\t" << insert_cnt << endl;
		cout << "quick count:\t" << quick_cnt << endl;
		cout << "heap count:\t" << heap_cnt << endl;
		cout << "merge count:\t" << merge_cnt << endl;
	}
};