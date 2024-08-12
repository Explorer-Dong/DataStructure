//
// Created by Wenjie Dong on 2023-10-12.
//

#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include <unordered_map>

using namespace std;

#ifndef Homework_4_H
#define Homework_4_H

class Homework_4 {
public:
    // T4.1 get next array of child string
    vector<int> getNext(const string& child) {
        int m = child.size();
        vector<int> ne(m + 1);
        string t = " " + child;
        
        for (int i = 2, j = 0; i <= m; i++) {
            while (j && t[i] != t[j + 1]) {
                j = ne[j];
            }
            if (t[i] == t[j + 1]) {
                j++;
            }
            ne[i] = j;
        }
        
        return ne;
    }
    
    
    // T4.2 count t in s
    int countKMP(const string& s = "abccabaccaba", const string& t = "ab") {
        int cnt = 0;
        int n = s.size(), m = t.size();
        string news = " " + s;
        string newt = " " + t;
        vector<int> ne = getNext(t);
        
        for (int i = 1, j = 0; i <= n; i++) {
            while (j && news[i] != newt[j + 1]) {
                j = ne[j];
            }
            if (news[i] == newt[j + 1]) {
                j++;
            }
            if (j == m) {
                cnt++;
                j = ne[j];
            }
        }
        
        return cnt;
    }
    
    
    // T4.3 del all t in s
    string deleteKMP(const string& s = "abccabaccaba", const string& t = "ab") {
        string res;
        int n = s.size(), m = t.size();
        string news = " " + s;
        string newt = " " + t;
        vector<int> ne = getNext(t);
        
        int l = 1;
        for (int i = 1, j = 0; i <= n; i++) {
            while (j && news[i] != newt[j + 1]) {
                j = ne[j];
            }
            if (news[i] == newt[j + 1]) {
                j++;
            }
            if (j == m) {
                res += news.substr(l, i - m - l + 1);
                l = i + 1;
                j = ne[j];
            }
        }
        
        // get possible end
        res += news.substr(l);
        
        return res.size() ? res : s;
    }
    
    
    // T4.4 get all longest common substrings - kmp
    vector<string> getLongestCommomSubstring_kmp(const string& s = "abaadqbacaba", const string& t = "abac") {
        vector<string> res;
        
        int m = t.size();
        for (int len = m; len >= 1; len--) {
            bool ok = false;
            for (int i = 0; i < m - len + 1; i++) {
                string tt = t.substr(i, len);
                if (countKMP(s, tt)) {
                    ok = true;
                    res.push_back(tt);
                }
            }
            if (ok) {
                return res;
            }
        }
        
        return res;
    }
    
    
    // T4.4 get all longest common substrings - dp
    vector<string> getLongestCommomSubstring_dp(const string& s = "abaadqbacaba", const string& t = "abac") {
        string news = " " + s;
        string newt = " " + t;
        int n = s.size(), m = t.size();
        
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        int ma = 0;
        
        // update dp table
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (news[i] == newt[j]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    ma = max(ma, dp[i][j]);
                }
            }
        }
        
        // find all longest common substrings
        unordered_map<string, bool> dict;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (dp[i][j] == ma) {
                    dict[news.substr(i - ma + 1, ma)] = true;
                }
            }
        }
        
        // get result
        vector<string> res;
        for (auto& [lcs, _]: dict) {
            res.push_back(lcs);
        }
        
        return res;
    }
    
    
    // T4.5 reverse words order in sentence - change original string
    string reverseOrigin(string s = "Do or do not, there is no try.") {
        int n = s.size();
        
        reverse(s.begin(), s.end());
        
        int i = 0;
        while (i < n) {
            int j = i;
            while (j < n && s[j] != ' ') {
                j++;
            }
            reverse(s.begin() + i, s.begin() + j);
            i = j + 1;
        }
        
        return s;
    }
    
    
    // T4.5 reverse words order in sentence - use stack to reverse
    string reverseWithStack(const string& s = "Do or do not, there is no try.") {
        int n = s.size();
        
        // get words
        stack<string> stk;
        int i = 0;
        while (i < n) {
            int j = i;
            while (s[j] != ' ') {
                j++;
            }
            stk.push(s.substr(i, j - i));
            i = j + 1;
        }
        
        // splice result
        string res;
        while (stk.size()) {
            res += stk.top() + " ";
            stk.pop();
        }
        
        return res;
    }
};

#endif // Homework_4_H