//
// Created by Wenjie Dong on 2023-10-19.
//

#include <iostream>
#include "GList.h"
#include "GListNode.h"

using namespace std;

class Homework_6 {
public:
	// T 6.2 �ж�����������Ƿ����
	void T2() {
		char s1[] = "(a, (b, c), d)";
		char s2[] = "(a, (b, c), d, e)";

		GList<char> gl1(s1);
		GList<char> gl2(s2);

		bool eq = Compare(gl1.head, gl2.head);

		cout << eq << "\n";
	}

	bool Compare(GListNode<char>* h1, GListNode<char>* h2) {
		if (!h1 && !h2) { // �ų� 0 0
			return true;
		} else if (h1 && !h2 || !h1 && h2) { // �ų� 0 1 �� 1 0
			return false;
		} else if (h1->type != h2->type) { // �ų� ���Ͳ�һ��
			return false;
		} else if (h1->type == ATOM && h2->type == ATOM) { // ����ԭ��
			return h1->data == h2->data && Compare(h1->next, h2->next);
		} else { // �����ӱ�
			return Compare(h1->sublist, h2->sublist) && Compare(h1->next, h2->next);
		}
	}


	// T 6.3 ɾ�������������Ԫ��ֵΪx��ԭ�ӽ��
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

		if (h->type == LIST) { // ��ǰ���ӱ�
			Delete(h, h->sublist, c, true);
			Delete(h, h->next, c, false);
		} else { // ��ǰ��ԭ��
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





















