//
// Created by Wenjie Dong on 2023-10-16.
//

#include <bits/stdc++.h>

using namespace std;

#ifndef CODE_TRAIL_4_H
#define CODE_TRAIL_4_H

class Trail_4 {
public:
	// Tr 4.1 BF模式匹配
	int TrBF(const string& s, const string& t) {
		int pos = -1;

		string news = "$" + s;
		string newt = "$" + t;

		int n = s.size(), m = t.size();

		for (int i = 1; i <= n - m + 1; i++) {
			int j = 1, k = i;
			for (; j <= m; j++, k++) {
				if (news[k] != newt[j]) {
					break;
				}
			}
			if (j == m + 1) {
				pos = i - 1;
				break;
			}
		}

		if (pos == -1) {
			cerr << "no match\n";
		} else {
			return pos;
		}
	}


	// Tr 4.2 求next
	vector<int> GetNext(const string& str) {
		int m = str.size();
		vector<int> ne(m + 1);
		string t = "1" + str; // 扩展下标为从1开始

		for (int i = 2, j = 0; i <= m; i++) {
			while (j && t[i] != t[j + 1]) {
				// 未匹配上则不断回溯
				j = ne[j];
			}
			if (t[i] == t[j + 1]) {
				// 匹配上了则j指针后移一位
				j++;
			}
			ne[i] = j;
		}

		return ne;
	}


	// Tr 4.1 KMP未优化的模式匹配
	int TrKMP(const string& s, const string& t) {
		int pos = -1;

		string news = "$" + s;
		string newt = "$" + t;

		int n = s.size(), m = t.size();

		vector<int> ne = GetNext(t);

		for (int i = 1, j = 0; i <= n; i++) {
			if (j && news[i] != newt[j + 1]) {
				j = ne[j];
			}

			if (news[i] == newt[j + 1]) {
				j++;
			}

			if (j == m) {
				pos = i - m;
				break;
			}
		}

		if (pos == -1) {
			cerr << "no match\n";
		} else {
			return pos;
		}
	}


	// Tr 4.1 KMP优化的模式匹配
	int TrKMPFinal(const string& s, const string& t) {
		int pos = -1;

		string news = "$" + s;
		string newt = "$" + t;

		int n = s.size(), m = t.size();

		vector<int> ne = GetNext(t);

		for (int i = 1, j = 0; i <= n; i++) {
			while (j && news[i] != newt[j + 1]) {
				j = ne[j];
			}

			if (news[i] == newt[j + 1]) {
				j++;
			}

			if (j == m) {
				pos = i - m;
				break;
			}
		}

		if (pos == -1) {
			cerr << "no match\n";
		} else {
			return pos;
		}
	}


	// Tr 4.2 凯撒密码：加密
	void TrCaesarCipher(char* input, char* output, int dx) {
		ifstream fin(input);
		ofstream fout(output);

		string s;
		fin >> s;

		int n = s.size();
		for (int i = 0; i < n; i++) {
			char c;
			if (islower(s[i])) {
				c = (s[i] - 'a' + dx) % 26 + 'a';
			} else if (isupper(s[i])) {
				c = (s[i] - 'A' + dx) % 26 + 'A';
			} else {
				cerr << "unknow character\n";
				break;
			}
			fout << c;
		}

		fin.close();
		fout.close();
	}


	// Tr 4.2 凯撒密码：解密
	void TrCaesarDecipher(char* in, char* out, int dx) {
		TrCaesarCipher(out, in, 26 - dx);
	}
};

#endif //CODE_TRAIL_4_H