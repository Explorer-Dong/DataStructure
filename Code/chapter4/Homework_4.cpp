//
// Created by Wenjie Dong on 2023-10-12.
//

#include <bits/stdc++.h>

using namespace std;

class Homework_4 {
public:
	// T 4.1 计算模板串的 next 数组
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


	// T 4.2 统计s串中t串的个数
	int TestContain(const string& s, const string& t) {
		int cnt = 0;

		vector<int> ne = GetNext(t);
		int n = s.size(), m = t.size();

		string news = "1" + s;
		string newt = "1" + t;

		for (int i = 1, j = 0; i <= n; i++) {
			while (j && news[i] != newt[j + 1]) {
				// 未匹配上则不断回溯
				j = ne[j];
			}
			if (news[i] == newt[j + 1]) {
				// 匹配上了则j指针后移一位
				j++;
			}

			if (j == m) {
				// 匹配完全，则统计并且回溯
				cnt++;
				j = ne[j];
			}
		}

		return cnt;
	}


	// T 4.3 删除s串中所有t串
	string TestDelete(const string& s, const string& t) {
		string res;

		int n = s.size(), m = t.size();
		string news = "1" + s;
		string newt = "1" + t;
		vector<int> ne = GetNext(t);

		int l = 1, r = -1;
		for (int i = 1, j = 0; i <= n; i++) {
			while (j && news[i] != newt[j + 1]) {
				j = ne[j];
			}

			if (news[i] == newt[j + 1]) {
				j++;
			}

			if (j == m) {
				r = i - m;
				for (int c = l; c <= r; c++) {
					res += news[c];
				}
				l = i + 1;
				j = ne[j];
			}
		}

		// 收尾
		for (int c = l; c <= n; c++) {
			res += news[c];
		}

		return res.size() ? res : s;
	}


	// T 4.4 返回所有的最大公共子串 TODO
	vector<string> LongestCommomSubstring(const string& s, const string& t) {
		vector<string> res;

		int n = s.size(), m = t.size();
		string news = "1" + s;
		string newt = "1" + t;

		// dp[i][j]表示s串的[1,i]个字符和t串的[1,j]个字符的最长公共子串长度
		vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
		int ma = 0; // 最长公共子串的长度 ma

		// 求解最大公共子串的长度
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (news[i] == newt[j]) {
					dp[i][j] = dp[i - 1][j - 1] + 1;
					ma = max(ma, dp[i][j]);
				} else {
					dp[i][j] = 0;
				}
			}
		}

		// 根据最大长度找到公共子串
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (dp[i][j] == ma) {
					res.emplace_back(s.substr(i - ma, ma));
				}
			}
		}

		return res;
	}


	// T 4.5 反转句子中单词的顺序
	string TestReverse(const string& s) {
		string res;

		int n = s.size(), l = 0;
		for (int r = 0; r < n; r++) {
			if (s[r] == ' ') {
				res = s.substr(l, r - l) + res;
				res = " " + res;
				l = r + 1;
			}
		}

		// 收尾
		res = s.substr(l) + res;

		return res;
	}
};


















