//
// Created by 董文杰 on 2023-10-10.
//

#include <bits/stdc++.h>
#include "SeqStack.h"
#include "SeqDoubleStack.h"
#include "LinkQueue.h"
#include "SeqQueueFlag.h"
#include "SeqQueueNum.h"
#include "Dstack2Queue.h"
#include "Experiment_3.cpp"

using namespace std;

class Homework_3 {
    // get all the train sequence
    void get_train_seq(SeqStack<int, 100>& station, vector<int>& out, int idx) {
        /**
		 * @note get all the train sequence
		 * @param station train station
		 * @param out the train sequence
		 * @param idx the number of the train
		 */
        
        if (out.size() == 5) {
            // all the train has been out
            for (int i = 0; i < out.size(); i++) {
                cout << out[i] << " \n"[i == out.size() - 1];
            }
            return;
        }
        
        if (idx > 0) {
            // condition 1: there are trains not in the station, push the train into the station
            station.Push(idx);
            get_train_seq(station, out, idx - 1);
            station.Pop();
        }
        
        if (!station.Empty()) {
            // condition 2: there are trains in the station, pop the train out
            int train = station.Top();
            station.Pop();
            out.push_back(train);
            get_train_seq(station, out, idx);
            out.pop_back();
            station.Push(train);
        }
    }

public:
    // T3.1 print all the train sequence
    void testCatlan() {
        SeqStack<int, 100> station;
        vector<int> out;
        int n = 5;
        get_train_seq(station, out, n);
    }
    
    
    // T3.2 convert decimal to either base between 2 and 16
    void testConvert() {
        int num, base;
        cin >> num >> base;
        
        SeqStack<int, 100> a;
        while (num >= base) {
            int mod = num % base;
            a.Push(mod);
            num = (num - mod) / base;
        }
        a.Push(num);
        
        while (!a.Empty()) {
            int t = a.Top();
            a.Pop();
            if (t < 10) {
                cout << t;
            } else {
                cout << (char) ('A' + t - 10);
            }
        }
    }
    
    
    // T3.3 bracket match
    bool testMatch(std::string s = "{10+9*12+[10/(2+90)+1]*(1+2)}") {
        SeqStack<char, 100> a;
        string op = "{[()]}";
        int i = 0;
        
        while (i < s.size()) {
            if (isdigit(s[i]) || op.find(s[i]) == string::npos) {
                // skip numbers or operators
                i++;
            } else if (s[i] == '{' || s[i] == '[' || s[i] == '(') {
                // left bracket
                a.Push(s[i++]);
            } else {
                // right bracket
                if (a.Empty()) {
                    // too many right brackets
                    return false;
                } else if (s[i] == '}' && a.Top() == '{' ||
                           s[i] == ']' && a.Top() == '[' ||
                           s[i] == ')' && a.Top() == '(') {
                    a.Pop();
                    i++;
                } else {
                    // mismatch
                    return false;
                }
            }
        }
        
        return a.Empty();
    }
    
    
    // T3.4 double stack
    void testDoubleStack() {
        SeqDoubleStack<int, 10> a;
        a.Output();
        a.Push_front(12), a.Push_front(2), a.Push_front(23);
        a.Pop_front();
        a.Push_back(3), a.Push_back(4), a.Push_back(5);
        a.Pop_back();
        a.Output();
    }
    
    
    // T3.5 mid to post
    void testMid2Post(std::string mid = "12+3*4/6*(5+7)") {
        Experiment_3 t3;
        string post = t3.Mid2Post(mid);
        cout << "post: " << post << "\n";
    }
    
    
    // T3.6 循环链式队列
    void testCircleLinkQueue() {
        LinkQueue<int> lq;
        lq.Push(1);
        lq.Push(2);
        lq.Push(3);
        lq.Push(4);
        cout << lq.Pop() << "\n";
        cout << lq.Pop() << "\n";
        cout << lq.Pop() << "\n";
        cout << lq.Pop() << "\n";
    }
    
    
    // T3.7 循环顺序队列 flag
    void testSeqQueueFlag() {
        SeqQueueFlag<int, 10> sqf;
        sqf.Push(2);
        sqf.Push(8);
        sqf.Push(1);
        cout << sqf.Front() << "\n";
    }
    
    
    // T3.8 循环顺序队列 num
    void testSeqQueueNum() {
        SeqQueueNum<int, 3> sqn;
        cout << sqn.Empty() << "\n";
    }
    
    
    // T3.9 双栈实现队列
    void testDstack2Queue() {
        int cnt = 0;
        Dstack2Queue<int, 10> dst2q;
        dst2q.Push(4);
        dst2q.Push(7);
        cout << dst2q.Empty() << "\n";
        cout << dst2q.Front() << "\n";
        dst2q.Pop();
        cout << dst2q.Front() << "\n";
    }
};