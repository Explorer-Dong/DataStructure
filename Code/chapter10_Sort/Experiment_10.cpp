#include <bits/stdc++.h>

using namespace std;

#ifndef EXPERIMENT_10_H
#define EXPERIMENT_10_H

class Experiment_10 {
public:
    // generate num random numbers in [0, range)
    vector<int> generate(int num, int range) {
        srand(time(nullptr));
        vector<int> res;
        for (int i = 0; i < num; i++) {
            res.push_back(rand() % range);
        }
        return res;
    }

    // insertSort
    int insertSort(vector<int> a) {
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

    // quickSort
    int quickSort(vector<int> a) {
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

    // HeapSort(largest top)
    int heapSort(vector<int> a) {
        int cnt = 0;
        auto pushdown = [&](int top, int lim) {
            int j = 2 * top + 1;
            while (j <= lim) {
                j += j < lim && a[j] < a[j + 1];
                cnt++;
                if (a[top] <= a[j]) {
                    cnt++;
                    swap(a[top], a[j]);
                    top = j;
                    j = 2 * top + 1;
                } else {
                    break;  // have to add it, or it's a dead loop
                }
            }
        };

        // ini heap
        int n = a.size();
        for (int i = n / 2 - 1; i >= 0; i--) {
            pushdown(i, n - 1);
        }

        // modify heap
        for (int i = 0; i < n - 1; i++) {
            swap(a[0], a[n - i - 1]);
            pushdown(0, n - i - 2);
        }

        return cnt;
    }

    // MergeSort - recursion
    int mergeSort(vector<int> a) {
        int cnt = 0;
        vector<int> t(a.size(), 0);
        function<void(int, int)> mergeSort = [&](int l, int r) {
            if (l >= r) return;

            // divide
            int mid = (l + r) >> 1;

            // conquer
            mergeSort(l, mid), mergeSort(mid + 1, r);

            // combine
            int i = l, j = mid + 1, k = 0;
            while (i <= mid && j <= r) {
                if (a[i] < a[j]) t[k++] = a[i++];
                else t[k++] = a[j++];
                cnt++;
            }
            while (i <= mid) t[k++] = a[i++];
            while (j <= r) t[k++] = a[j++];

            for (i = l, j = 0; i <= r; i++) a[i] = t[j++];
        };

        mergeSort(0, a.size() - 1);

        return cnt;
    }

    // Compare
    void compare() {
        vector<int> a = generate(1000, 1000);
        int insert_cnt = 0, quick_cnt = 0, heap_cnt = 0, merge_cnt = 0;

        insert_cnt = insertSort(a);
        quick_cnt = quickSort(a);
        heap_cnt = heapSort(a);
        merge_cnt = mergeSort(a);

        cout << "insert count:\t" << insert_cnt << endl;
        cout << "quick count:\t" << quick_cnt << endl;
        cout << "heap count:\t" << heap_cnt << endl;
        cout << "merge count:\t" << merge_cnt << endl;
    }
};

#endif //EXPERIMENT_10_H