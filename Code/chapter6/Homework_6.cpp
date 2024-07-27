//
// Created by Wenjie Dong on 2023-10-19.
//

#include <iostream>
#include "GList.h"
#include "GListNode.h"

using namespace std;

class Homework_6 {
public:
	// T 6.2 判断两个广义表是否相等
	void T2() {
		char s1[] = "(a, (b, c), d)";
		char s2[] = "(a, (b, c), d, e)";

		GList<char> gl1(s1);
		GList<char> gl2(s2);

		bool eq = Compare(gl1.head, gl2.head);

		cout << eq << "\n";
	}

	bool Compare(GListNode<char>* h1, GListNode<char>* h2) {
		if (!h1 && !h2) { // 排除 0 0
			return true;
		} else if (h1 && !h2 || !h1 && h2) { // 排除 0 1 和 1 0
			return false;
		} else if (h1->type != h2->type) { // 排除 类型不一样
			return false;
		} else if (h1->type == ATOM && h2->type == ATOM) { // 都是原子
			return h1->data == h2->data && Compare(h1->next, h2->next);
		} else { // 都是子表
			return Compare(h1->sublist, h2->sublist) && Compare(h1->next, h2->next);
		}
	}


	// T 6.3 删除广义表中所有元素值为x的原子结点
	void T3() {
		char s1[] = "((a, b), g, a, f)";
		char c = 'a';
		GList<char> gl(s1);
		GListNode<char>* pre = nullptr;

		gl.Output();
		Delete(gl.head, gl.head->sublist, c, true);
		gl.Output();
	}

	void Delete(GListNode<char>* pre, GListNode<char>* h, char c, bool pre_is_sub) {
		if (!h) {
			return;
		}

		if (h->type == LIST) { // 当前是子表
			Delete(h, h->sublist, c, true);
			Delete(h, h->next, c, false);
		} else { // 当前是原子
			if (h->data == c) {
				GListNode<char>* now = h;
				h = h->next;
				delete now;
				if (pre_is_sub) {
					pre->sublist = h;
				} else {
					pre->next = h;
				}
			}
			Delete(h, h->next, c, false);
		}
	}
};





















