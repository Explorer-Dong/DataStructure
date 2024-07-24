//
// Created by ���Ľ� on 2023-10-10.
//

#include <bits/stdc++.h>
#include "SeqStack.h"
#include "CircleSeqQueueWithFlag.h"

using namespace std;

#ifndef CODE_Experiment_3_H
#define CODE_Experiment_3_H

class Experiment_3 {
public:
    // Exp2.1 test SeqStack
    void testSeqStack() {
        SeqStack<int, 100> s;
        
        auto displayMenu = [&]() {
            cout << "====================\n";
            cout << "1. ��ջ\n";
            cout << "2. ��ջ\n";
            cout << "3. ȡջ��Ԫ��\n";
            cout << "4. �ж�ջ�Ƿ�Ϊ��\n";
            cout << "0. �˳�\n";
            cout << "���������ѡ��";
        };
        
        int choice;
        while (true) {
            displayMenu();
            cin >> choice;
            switch (choice) {
                case 1: {
                    int x;
                    cout << "������Ҫ��ջ��Ԫ�أ�";
                    cin >> x;
                    s.Push(x);
                    break;
                }
                case 2: {
                    cout << s.Pop() << "\n";
                    break;
                }
                case 3: {
                    cout << "ջ��Ԫ��Ϊ��\n";
                    cout << s.Top() << "\n";
                    break;
                }
                case 4: {
                    cout << s.Empty() << "\n";
                    break;
                }
                case 0: {
                    return;
                }
                default: {
                    cout << "�����������������\n";
                    break;
                }
            }
        }
    }
    
    
    // Exp2.1 calc mid
    void testCalcMid() {
        unordered_map<char, int> pri{{'+', 1},
                                     {'-', 1},
                                     {'*', 2},
                                     {'/', 2}};
        
        string s = "2*(1+3+1)";
//		cout << "������һ���Ϸ�����׺���ʽ��\n";
//		cin >> s;
        SeqStack<int, 100> num;
        SeqStack<char, 100> op;
        
        auto calc = [&]() {
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
        
        int i = 0;
        while (i < s.size()) {
            if (isdigit(s[i])) {
                int x = 0;
                while (i < s.size() && isdigit(s[i])) {
                    x = x * 10 + s[i] - '0';
                    i++;
                }
                num.Push(x);
            } else if (s[i] == '(') {
                op.Push(s[i++]);
            } else if (s[i] == ')') {
                while (op.Top() != '(') calc();
                op.Pop();
                i++;
            } else {
                while (!op.Empty() && op.Top() != '(' && pri[op.Top()] >= pri[s[i]]) calc();
                op.Push(s[i++]);
            }
        }
        while (!op.Empty()) calc();
        
        cout << "������Ϊ: " << num.Top() << "\n";
    }
    
    
    // Exp2.1 mid to post and calc post
    void testMid2PostCalcPost() {
        string s = "2*(1+3)";
//		cin >> s;
        
        string post = Mid2Post(s);
        cout << "��׺���ʽΪ��\n";
        cout << post << "\n";
        
        int res = CalcPost(post);
        cout << "��׺���ʽ�ļ�����Ϊ��\n";
        // 2 1 3 + *
        cout << res << "\n";
    }
    
    
    // mid to post
    string Mid2Post(const string& s) {
        string post;
        
        unordered_map<char, int> pri{{'(', 0}, {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};
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
    
    
    // calc post
    int CalcPost(string& post) {
        SeqStack<int, 100> num;
        int i = 0, n = post.size();
        while (i < n) {
            if (isdigit(post[i])) {
                int x = 0;
                while (i < n && isdigit(post[i])) {
                    x = x * 10 + post[i] - '0';
                    i++;
                }
                num.Push(x);
            } else if (post[i] == ' ') {
                i++;
            } else {
                int b = num.Top();
                num.Pop();
                int a = num.Top();
                num.Pop();
                if (post[i] == '+') num.Push(a + b);
                else if (post[i] == '-') num.Push(a - b);
                else if (post[i] == '/') num.Push(a / b);
                else num.Push(a * b);
                i++;
            }
        }
        
        return num.Top();
    }
    
    
    // Exp2.2 test SeqQueue
    void testSeqQueue() {
        CircleSeqQueueWithFlag<int, 100> q;
        
        auto displayMenu = [&]() {
            cout << "====================\n";
            cout << "1. ���\n";
            cout << "2. ����\n";
            cout << "3. ȡ��ͷ\n";
            cout << "4. �ж϶����Ƿ�Ϊ��\n";
            cout << "0. �˳�\n";
            cout << "���������ѡ��";
        };
        
        int choice;
        while (true) {
            displayMenu();
            cin >> choice;
            switch (choice) {
                case 1: {
                    int x;
                    cout << "������Ҫ��ӵ�Ԫ�أ�";
                    cin >> x;
                    q.Push(x);
                    cout << "��ӳɹ�\n";
                    break;
                }
                case 2: {
//                    cout << q.Pop() << "\n";
                    cout << "���ӳɹ�\n";
                    break;
                }
                case 3: {
                    cout << "��ͷԪ��Ϊ��\n";
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
                    cout << "�����������������\n";
                    break;
                }
            }
        }
    }
    
    
    // Exp2.2 test patient
    void testPatient() {
        // �������һ��ֻ�����ֵ��ַ���
        auto genRandStr = [](int len) {
            string res;
            for (int i = 0; i < len; i++) {
                res += to_string(rand() % 10);
            }
            return res;
        };
        
        auto displayMenu = []() {
            cout << "====================\n";
            cout << "1. �Ŷӣ�����ȡ��\n";
            cout << "2. ������߾���\n";
            cout << "3. �鿴����ӡ���л��ߵĲ�����\n";
            cout << "0. �°ࣺ�˳�\n";
            cout << "���������ѡ��";
        };
        
        CircleSeqQueueWithFlag<string, 100> q;
        int choice;
        while (true) {
            displayMenu();
            cin >> choice;
            switch (choice) {
                case 1: {
                    string x = genRandStr(6);
                    q.Push(x);
                    cout << "����ȡ�ųɹ���������Ϊ��\n";
                    cout << x << "\n";
                    break;
                }
                case 2: {
                    if (q.Empty()) {
                        cout << "��ǰû�л����ڵȴ�����\n";
                    }
                    cout << "���� " << q.Front() << " ����ɹ�\n";
                    q.Pop();
                    break;
                }
                case 3: {
                    vector<string> t;
                    cout << "��ǰ���л��ߵĲ�����Ϊ��\n";
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
    
    
    // Exp2.3 �����·��
    void testShortestPath() {
        CircleSeqQueueWithFlag<int, 100> q;
        
        int m = 4, n = 3;
        vector<vector<int>> g = {
                {0, 1, 1},
                {0, 0, 1},
                {1, 0, 0},
                {0, 1, 0}
        };
        
        pair<vector<pair<int, int>>, int> res = get_shortest_path(g, 0, 0, m - 1, n - 1, m, n);
        
        vector<pair<int, int>> path = res.first;
        int min_dist = res.second;
        
        cout << "���·��Ϊ��\n";
        for (auto& x: path) {
            cout << "(" << x.first << "," << x.second << ")" << ' ';
        }
        
        cout << "\n���·���ĳ���Ϊ��\n";
        cout << min_dist << "\n";
    }
    
    
    // Exp2.3 get shortest path
    pair<vector<pair<int, int>>, int> get_shortest_path(vector<vector<int>>& g, int sti, int stj, int endi, int endj, int m, int n) {
        vector<pair<int, int>> path; // ���·��
        vector<vector<int>> d(m, vector<int>(n, INT_MAX)); // ���·���ĳ��� d[endi][endj]
        
        CircleSeqQueueWithFlag<pair<int, int>, 100> q;
        
        q.Push({sti, stj});
        d[sti][stj] = 0;
        
        int dx[] = {0, 1, 0, -1, 1, 1, -1, -1}, dy[] = {1, 0, -1, 0, 1, -1, 1, -1};
        
        while (!q.Empty()) {
            auto now = q.Front();
            q.Pop();
            
            int i = now.first, j = now.second;
            
            if (i == endi && j == endj) {
                break;
            }
            
            for (int k = 0; k < 8; k++) {
                int ni = i + dx[k], nj = j + dy[k];
                if (ni >= 0 && ni < m && nj >= 0 && nj < n && g[ni][nj] == 0 && d[ni][nj] == INT_MAX) {
                    d[ni][nj] = d[i][j] + 1;
                    q.Push({ni, nj});
                }
            }
        }
        
        // ���յ㿪ʼ���������·��
        int i = endi, j = endj;
        while (i != sti || j != stj) {
            path.push_back({i, j});
            for (int k = 0; k < 8; k++) {
                int ni = i + dx[k], nj = j + dy[k];
                if (ni >= 0 && ni < m && nj >= 0 && nj < n && g[ni][nj] == 0 && d[ni][nj] == d[i][j] - 1) {
                    i = ni;
                    j = nj;
                    break;
                }
            }
        }
        
        reverse(path.begin(), path.end());
        return make_pair(path, d[endi][endj]);
    }
};

#endif //CODE_Experiment_3_H