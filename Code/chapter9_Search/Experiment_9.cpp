//
// Created by Wenjie Dong on 2023-12-25.
//

#include <iostream>
#include <vector>
#include <bits/stdc++.h>

class Experiment_9 {
private:
	// seq
	int SeqSearch(std::vector<int>& a, int n, int target) {
		int i = 0;
		while (i < n && a[i] != target) {
			i++;
		}
		return i == n ? -1 : i;
	}

	// seq search with guard
	int SeqSearchWithGuard(std::vector<int>& a, int n, int target) {
		int i = 0;
		a[n] = target;
		while (a[i] != target) {
			i++;
		}
		return i == n ? -1 : i;
	}

	// binary
	int Binary(std::vector<int>& a, int n, int target) {
		int l = 0, r = n;
		while (l < r) {
			int mid = (l + r) >> 1;
			if (a[mid] < target) l = mid + 1;
			else r = mid;
		}
		return a[r] == target ? r : -1;
	}

	// binary with recursion
	int BinaryRecursion(std::vector<int>& a, int n, int target) {

		std::function<int(int, int, int)> binSearch = [&](int l, int r, int target) -> int {
			if (l >= r) return a[r] == target ? r : -1;
			int mid = (l + r) >> 1;
			if (a[mid] < target) return binSearch(mid + 1, r, target);
			else return binSearch(l, mid, target);
		};

		return binSearch(0, n - 1, target);
	}

public:
	/* -------------------- 实验一 -------------------- */

	// menu fun
	void Menu() {
		auto disp = [&]() {
			std::cout << "\n ================================= \n";
			std::cout << "0. disp seqlist\n";
			std::cout << "1. seq search\n";
			std::cout << "2. seq search with guard\n";
			std::cout << "3. binary search\n";
			std::cout << "4. binary search using recursion\n";
			std::cout << "-1. exit program\n";
			std::cout << " ================================= \n";
			std::cout << "please input your choose:\n";
		};

		int max_size = 200;

		std::cout << "please input your seq size:\n";
		int n;
		std::cin >> n;
		if (n > max_size) {
			std::cerr << "out of limlit!\n";
			exit(1);
		}

		std::cout << "please input your seq:\n";
		std::vector<int> a(max_size);
		for (int i = 0; i < n; i++) {
			std::cin >> a[i];
		}

		while (true) {
			disp();

			int choose;
			std::cin >> choose;

			switch (choose) {
				case -1: {
					return;
				}
				case 0: {
					for (int i = 0; i < n; i++) {
						std::cout << a[i] << " \n"[i == n - 1];
					}
					break;
				}
				case 1: {
					std::cout << "please input yuor target:\n";
					int tar;
					std::cin >> tar;
					std::cout << SeqSearch(a, n, tar) << "\n";
					break;
				}
				case 2: {
					std::cout << "please input yuor target:\n";
					int tar;
					std::cin >> tar;
					std::cout << SeqSearchWithGuard(a, n, tar) << "\n";
					break;
				}
				case 3: {
					std::cout << "please input yuor target:\n";
					int tar;
					std::cin >> tar;
					std::cout << Binary(a, n, tar) << "\n";
					break;
				}
				case 4: {
					std::cout << "please input yuor target:\n";
					int tar;
					std::cin >> tar;
					std::cout << BinaryRecursion(a, n, tar) << "\n";
					break;
				}
			}
		}
	}

	/* -------------------- 实验二 -------------------- */

};