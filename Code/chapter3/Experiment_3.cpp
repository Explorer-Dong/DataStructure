//
// Created by 董文杰 on 2023-10-10.
//

#include <bits/stdc++.h>
#include "SeqStack.h"
#include "CircleSeqQueueWithFlag.h"

using namespace std;

#ifndef CODE_Experiment_3_H
#define CODE_Experiment_3_H

class Experiment_3 {
private:
    void displaySeqStackMenu() {
        cout << "====================\n";
        cout << "1. 入栈\n";
        cout << "2. 出栈\n";
        cout << "3. 取栈顶元素\n";
        cout << "4. 判断栈是否为空\n";
        cout << "0. 退出\n";
        cout << "请输入你的选择：";
    }
    
    void displayPatientMenu() {
        cout << "====================\n";
        cout << "1. 排队：患者取号，进入等待队列\n";
        cout << "2. 就诊：患者就诊，查看队首病历\n";
        cout << "3. 查看：打印所有患者的病历信息\n";
        cout << "0. 下班：退出\n";
        cout << "请输入你的选择：";
    }
    
    std::string genRandStr(int len) {
        std::string res;
        for (int i = 0; i < len; i++) {
            res += to_string(rand() % 10);
        }
        return res;
    }
    
    pair<vector<pair<int, int>>, int>
    getShortestPath(vector<vector<int>>& g, pair<int, int>& st, pair<int, int>& en) {
        int m = g.size(), n = g[0].size();
        vector<vector<int>> d(m, vector<int>(n, INT_MAX >> 1));
        int sti = st.first, stj = st.second;
        int eni = en.first, enj = en.second;
        
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        bool find_path = false;
        
        // update dist matrix with bfs algorithm
        CircleSeqQueueWithFlag<pair<int, int>, 100> q;
        q.Push({sti, stj});
        d[sti][stj] = 0;
        while (!q.Empty()) {
            auto now = q.Front();
            q.Pop();
            
            int i = now.first, j = now.second;
            if (i == eni && j == enj) {
                find_path = true;
                break;
            }
            for (int k = 0; k < 4; k++) {
                int ni = i + dx[k], nj = j + dy[k];
                if (ni < 0 || ni >= m || nj < 0 || nj >= n || g[ni][nj] || d[ni][nj] != INT_MAX >> 1) {
                    continue;
                }
                d[ni][nj] = d[i][j] + 1;
                q.Push({ni, nj});
            }
        }
        
        // edge case
        if (!find_path) {
            cerr << "no valid path!\n";
            exit(1);
        }
        
        // get path from end point
        vector<pair<int, int>> path;
        int i = eni, j = enj;
        while (i != sti || j != stj) {
            path.push_back({i, j});
            for (int k = 0; k < 4; k++) {
                int ni = i + dx[k], nj = j + dy[k];
                if (ni < 0 || ni >= m || nj < 0 || nj >= n || g[ni][nj] || d[ni][nj] != d[i][j] - 1) {
                    continue;
                }
                i = ni, j = nj;
                break;
            }
        }
        path.push_back({sti, stj});
        reverse(path.begin(), path.end());
        
        return make_pair(path, d[eni][enj]);
    }

public:
    // Exp2.1 test SeqStack
    void testSeqStack() {
        SeqStack<int, 100> s;
        
        int choice;
        while (true) {
            displaySeqStackMenu();
            cin >> choice;
            switch (choice) {
                case 1: {
                    cout << "input push in element: ";
                    int x;
                    cin >> x;
                    s.Push(x);
                    break;
                }
                case 2: {
                    s.Pop();
                    break;
                }
                case 3: {
                    cout << "top element: ";
                    cout << s.Top() << "\n";
                    break;
                }
                case 4: {
                    cout << (s.Empty() ? "empty stack\n" : "not empty stack\n");
                    break;
                }
                case 0: {
                    return;
                }
                default: {
                    cout << "invalid input, please try again!\n";
                    break;
                }
            }
        }
    }
    
    
    // Exp2.1 calc mid
    void testCalcMid(const std::string s = "2*(1+3+1)") {
        unordered_map<char, int> pri{{'(', 0},
                                     {'+', 1},
                                     {'-', 1},
                                     {'*', 2},
                                     {'/', 2}};
        
        SeqStack<int, 100> num;
        SeqStack<char, 100> op;
        
        auto calc = [&]() -> void {
            int b = num.Top();
            num.Pop();
            int a = num.Top();
            num.Pop();
            char o = op.Top();
            op.Pop();
            
            if (o == '+') num.Push(a + b);
            else if (o == '-') num.Push(a - b);
            else if (o == '/') num.Push(a / b);
            else num.Push(a * b);
        };
        
        for (int i = 0; i < s.size(); i++) {
            if (isdigit(s[i])) {
                int x = 0, j = i;
                while (j < s.size() && isdigit(s[j])) {
                    x = x * 10 + s[j++] - '0';
                }
                num.Push(x);
                i = j - 1;
            } else if (s[i] == '(') {
                op.Push(s[i]);
            } else if (s[i] == ')') {
                while (op.Top() != '(') {
                    calc();
                }
                op.Pop();
            } else {
                while (!op.Empty() && pri[op.Top()] >= pri[s[i]]) {
                    calc();
                }
                op.Push(s[i]);
            }
        }
        
        while (!op.Empty()) {
            calc();
        }
        
        cout << "result: " << num.Top() << "\n";
    }
    
    
    // Exp2.1 mid to post
    std::string Mid2Post(const std::string& s) {
        string post;
        
        unordered_map<char, int> pri{{'(', 0},
                                     {'+', 1},
                                     {'-', 1},
                                     {'*', 2},
                                     {'/', 2}};
        SeqStack<char, 100> op;
        
        for (int i = 0; i < s.size(); i++) {
            if (isdigit(s[i])) {
                int x = 0, j = i;
                while (j < s.size() && isdigit(s[j])) {
                    x = x * 10 + s[j++] - '0';
                }
                i = j - 1;
                post += to_string(x) + " ";
            } else if (s[i] == '(') {
                op.Push(s[i]);
            } else if (s[i] == ')') {
                while (op.Top() != '(') {
                    post += string(1, op.Top()) + " ";
                    op.Pop();
                }
                op.Pop();
            } else {
                while (!op.Empty() && pri[s[i]] <= pri[op.Top()]) {
                    post += string(1, op.Top()) + " ";
                    op.Pop();
                }
                op.Push(s[i]);
            }
        }
        
        while (!op.Empty()) {
            post += string(1, op.Top()) + " ";
            op.Pop();
        }
        
        return post;
    }
    
    
    // Exp2.1 calc post
    int CalcPost(const std::string& post) {
        SeqStack<int, 100> num;
        for (int i = 0; i < post.size(); i++) {
            if (isdigit(post[i])) {
                int x = 0, j = i;
                while (j < post.size() && isdigit(post[j])) {
                    x = x * 10 + post[j++] - '0';
                }
                num.Push(x);
                i = j - 1;
            } else if (post[i] == ' ') {
                continue;
            } else {
                int b = num.Top();
                num.Pop();
                int a = num.Top();
                num.Pop();
                if (post[i] == '+') num.Push(a + b);
                else if (post[i] == '-') num.Push(a - b);
                else if (post[i] == '/') num.Push(a / b);
                else num.Push(a * b);
            }
        }
        
        return num.Top();
    }
    
    
    // Exp2.1 mid to post and calc post
    void testMid2PostAndCalcPost(const std::string mid = "12*(1+3)") {
        cout << "mid expression: " << mid << "\n";
        
        string post = Mid2Post(mid);
        cout << "post expression: " << post << "\n";
        
        int res = CalcPost(post);
        cout << "calc post result: " << res << "\n";
    }
    
    
    // Exp2.2 test SeqQueue
    void testSeqQueue() {
        CircleSeqQueueWithFlag<int, 100> q;
        
        auto displayMenu = [&]() {
            cout << "====================\n";
            cout << "1. 入队\n";
            cout << "2. 出队\n";
            cout << "3. 取队头\n";
            cout << "4. 判断队列是否为空\n";
            cout << "0. 退出\n";
            cout << "请输入你的选择：";
        };
        
        int choice;
        while (true) {
            displayMenu();
            cin >> choice;
            switch (choice) {
                case 1: {
                    int x;
                    cout << "请输入要入队的元素：";
                    cin >> x;
                    q.Push(x);
                    cout << "入队成功\n";
                    break;
                }
                case 2: {
//                    cout << q.Pop() << "\n";
                    cout << "出队成功\n";
                    break;
                }
                case 3: {
                    cout << "队头元素为：\n";
                    cout << q.Front() << "\n";
                    break;
                }
                case 4: {
                    cout << q.Empty() << "\n";
                    break;
                }
                case 0: {
                    return;
                }
                default: {
                    cout << "输入错误，请重新输入\n";
                    break;
                }
            }
        }
    }
    
    
    // Exp2.2 test patient
    void testPatient() {
        CircleSeqQueueWithFlag<string, 100> q;
        int choice;
        while (true) {
            displayPatientMenu();
            cin >> choice;
            switch (choice) {
                case 1: {
                    string info = genRandStr(4);
                    q.Push(info);
                    cout << "info: " << info << "\n";
                    break;
                }
                case 2: {
                    if (q.Empty()) {
                        cout << "no patient!\n";
                    } else {
                        cout << "patient: " << q.Front() << " successful!\n";
                        q.Pop();
                    }
                    break;
                }
                case 3: {
                    vector<string> t;
                    cout << "all patients' info:\n";
                    while (!q.Empty()) {
                        t.push_back(q.Front());
                        cout << q.Front() << ' ';
                        q.Pop();
                    }
                    cout << "\n";
                    for (auto& x: t) {
                        q.Push(x);
                    }
                    break;
                }
                case 0: {
                    return;
                }
            }
        }
    }
    
    
    // Exp2.3 shortest path
    void testShortestPath() {
        vector<vector<int>> g = {{0, 1, 1},
                                 {0, 0, 1},
                                 {1, 0, 0},
                                 {0, 1, 0}};
        pair<int, int> st = {0, 0};
        pair<int, int> en = {3, 2};
        
        pair<vector<pair<int, int>>, int> res = getShortestPath(g, st, en);
        
        auto all_path = res.first;
        auto min_dist = res.second;
        cout << "shortest path:\n";
        for (int i = 0; i < all_path.size(); i++) {
            cout << '(' << all_path[i].first << ',' << all_path[i].second << ')';
            if (i == all_path.size() - 1) {
                cout << "\n";
            } else {
                cout << " -> ";
            }
        }
        cout << "shortest path length: " << min_dist << "\n";
    }
};

#endif //CODE_Experiment_3_H