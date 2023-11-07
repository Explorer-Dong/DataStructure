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
#include "Trail_3.cpp"

using namespace std;

class Homework_3 {
public:
	// T 3.1 打印出栈顺序
	void TestCatlan() {
		SeqStack<int, 100> station;
		vector<int> out;
		int n = 5;
		get_train_seq(station, out, n);
	}


	// T 3.1 辅助递归函数
	void get_train_seq(SeqStack<int, 100>& station, vector<int>& out, int n) {
		/**
		 * @note 获得当前车站状况以及列车出站情况下的所有出栈序列
		 * @param station 车站
		 * @param out 当前出栈序列
		 * @param n 当前列车编号
		 */

		if (out.size() == 5) {
			// 递归终点：所有列车都已出站
			for (int i = 0; i < out.size(); i++) {
				cout << out[i] << " \n"[i == out.size() - 1];
			}
			return;
		}

		if (n > 0) {
			// 状态1：有列车未进站，入站
			station.Push(n);
			get_train_seq(station, out, n - 1);
			station.Pop();
		}

		if (!station.Empty()) {
			// 状态2：站点不为空，出站
			int train = station.Top();
			station.Pop();
			out.push_back(train);
			get_train_seq(station, out, n);
			out.pop_back();
			station.Push(train);
		}
	}


	// T 3.2 十进制转换为任意进制
	void TestTransfor() {
		int num, scale;
		cin >> num >> scale;

		SeqStack<int, 100> a;
		while (num >= scale) {
			int ys = num % scale;
			a.Push(ys);
			num = (num - ys) / scale;
		}
		a.Push(num);

		while (!a.Empty()) {
			int t = a.Top();
			a.Pop();
			if (t >= 10) {
				cout << char(t - 10 + 'A');
			} else {
				cout << t;
			}
		}
	}


	// T 3.3 括号匹配
	bool TestMatch() {
		string s;
		cin >> s;
		//	s = "{10+9*12+[10/(2+90)+1]*(1+2)}";
		SeqStack<char, 100> a;

		string op = "{[()]}";
		for (int i = 0; i < s.size();) {
			if (isdigit(s[i])) {
				i++;
			} else if (op.find(s[i]) != string::npos) {
				if (s[i] == '{' || s[i] == '[' || s[i] == '(') {
					a.Push(s[i]);
				} else {
					if (a.Empty()) { // 右括号多了
						return false;
					} else {
						if (s[i] == '}' && a.Top() == '{' ||
							s[i] == ']' && a.Top() == '[' ||
							s[i] == ')' && a.Top() == '(') {
							a.Pop();
						} else { // 不匹配
							return false;
						}
					}
				}
				i++;
			} else {
				i++;
			}
		}

		if (!a.Empty()) { // 左括号多了
			return false;
		}

		return true;
	}


	// T 3.4 两栈共享一个线性空间
	void TestDStack() {
		SeqDoubleStack<int, 10> a;
//		a.Output();
		a.Push_front(12);
		a.Push_front(35);
		a.Pop_front();
//		a.Output();
	}


	// T 3.5 中缀转后缀
	void TestMid2Post() {
		string s;
		cout << "请输入中缀表达式：";
		cin >> s;

		Trail_3 t3;
		string post = t3.Mid2Post(s);
		cout << "后缀表达式为：" << post << "\n";
	}


	// T 3.6 循环链式队列
	void TestCircleLinkQueue() {
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


	// T 3.7 循环顺序队列 flag
	void TestSeqQueueFlag() {
		SeqQueueFlag<int, 10> sqf;
		sqf.Push(2);
		sqf.Push(8);
		sqf.Push(1);
		cout << sqf.Front() << "\n";
	}


	// T 3.8 循环顺序队列 num
	void TestSeqQueueNum() {
		SeqQueueNum<int, 3> sqn;
		cout << sqn.Empty() << "\n";
	}


	// T 3.9 双栈实现队列
	void TestDstack2Queue() {
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











