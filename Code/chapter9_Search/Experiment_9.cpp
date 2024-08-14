#include <iostream>
#include <vector>
#include <functional>

using namespace std;

class Experiment_9 {
private:
    // seq
    int seqSearch(vector<int>& a, int n, int target) {
        int i = 0;
        while (i < n && a[i] != target) {
            i++;
        }
        return i == n ? -1 : i;
    }
    
    // seq search with guard
    int seqSearchWithGuard(vector<int>& a, int n, int target) {
        int i = 0;
        a[n] = target;
        while (a[i] != target) {
            i++;
        }
        return i == n ? -1 : i;
    }
    
    // binary
    int binary(vector<int>& a, int n, int target) {
        int l = 0, r = n;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (a[mid] < target) l = mid + 1;
            else r = mid;
        }
        return a[r] == target ? r : -1;
    }
    
    // binary with recursion
    int binaryRecursion(vector<int>& a, int n, int target) {
        function<int(int, int, int)> binSearch = [&](int l, int r, int target) -> int {
            if (l >= r) return a[r] == target ? r : -1;
            int mid = (l + r) >> 1;
            if (a[mid] < target) return binSearch(mid + 1, r, target);
            else return binSearch(l, mid, target);
        };
        return binSearch(0, n - 1, target);
    }
    
    void dispSeqSearchMenu() {
        cout << "\n=================================\n";
        cout << "0. disp seqlist\n";
        cout << "1. seq search\n";
        cout << "2. seq search with guard\n";
        cout << "3. binary search\n";
        cout << "4. binary search using recursion\n";
        cout << "-1. exit program\n";
        cout << "=================================\n";
        cout << "please input your choose:\n";
    }

public:
    // menu fun
    void testSeqMenu() {
        int max_size = 200;
        cout << "please input your seq size:\n";
        int n;
        cin >> n;
        if (n > max_size) {
            cerr << "out of limlit!\n";
            exit(1);
        }
        cout << "please input your seq:\n";
        vector<int> a(max_size);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        
        while (true) {
            dispSeqSearchMenu();
            int choose;
            cin >> choose;
            switch (choose) {
                case -1: {
                    return;
                }
                case 0: {
                    for (int i = 0; i < n; i++) {
                        cout << a[i] << " \n"[i == n - 1];
                    }
                    break;
                }
                case 1: {
                    cout << "please input yuor target:\n";
                    int tar;
                    cin >> tar;
                    cout << seqSearch(a, n, tar) << "\n";
                    break;
                }
                case 2: {
                    cout << "please input yuor target:\n";
                    int tar;
                    cin >> tar;
                    cout << seqSearchWithGuard(a, n, tar) << "\n";
                    break;
                }
                case 3: {
                    cout << "please input yuor target:\n";
                    int tar;
                    cin >> tar;
                    cout << binary(a, n, tar) << "\n";
                    break;
                }
                case 4: {
                    cout << "please input yuor target:\n";
                    int tar;
                    cin >> tar;
                    cout << binaryRecursion(a, n, tar) << "\n";
                    break;
                }
            }
        }
    }
};