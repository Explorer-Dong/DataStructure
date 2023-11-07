//
// Created by 董文杰 on 2023-10-23.
//

#include <iostream>
#include "GListNode.h"

using namespace std;

#ifndef INC_3__DATASTRUCTURES_GLIST_H
#define INC_3__DATASTRUCTURES_GLIST_H

template<class T>
class GList{
private:
	GListNode<T>* DoCreat(char s[], int& i);
	void DoOutput(GListNode<T>* h);
	int Length(GListNode<T>* h);
	void Depth(GListNode<T>* h, int& depth, int now_depth, bool pre_is_sub);
	void Replace(GListNode<T>* h, T ori, T x);
	void Delete(GListNode<T>* pre, GListNode<T>* h, T x, bool pre_is_sub);

public:
	GListNode<T>* head;
	GList();
	GList(char s[]);			// 传入字符串进行构造
//	GList(GList<T>& obj);
//	~GList();

	int Length();				// 计算广义表的长度
	int Depth();				// 计算广义表的深度
	void Output();				// 打印广义表
	void Replace(T ori, T x);	// 替换广义表中值为 ori 的元素为 x
	void Delete(T x);			// 删除广义表中值为 x 的元素
};

template<class T>
GListNode<T>* GList<T>::DoCreat(char s[], int& i) {
	while (s[i] == ' ' || s[i] == ',') i++;
	char now = s[i++];

	GListNode<T>* h;

	if (now == '(') {
		h = new GListNode<T>;
		h->type = LIST;
		h->sublist = DoCreat(s, i);
		h->next = DoCreat(s, i);
		return h;
	} else if (now == ')' || now == '\0') {
		return nullptr;
	} else { // now == ATOM
		h = new GListNode<T>;
		h->type = ATOM;
		h->data = now;
		h->next = DoCreat(s, i);
		return h;
	}
}

template<class T>
void GList<T>::DoOutput(GListNode<T>* h) {
	if (h == nullptr) {
		return;
	} else if (h->type == ATOM) {
		cout << h->data;
	} else { // h->type == LIST
		cout << '(';
		DoOutput(h->sublist);
		cout << ')';
	}

	if (h->next) {
		cout << ',';
		DoOutput(h->next);
	}
}

template<class T>
int GList<T>::Length(GListNode<T>* h) {
	if (!h) {
		return 0;
	}

	return Length(h->next) + 1;
}

template<class T>
void GList<T>::Depth(GListNode<T>* h, int& max_depth, int now_depth, bool pre_is_sub) {
	/**
	 * @param h 当前结点
	 * @param max_depth 最大深度
	 * @param now_depth 当前深度
	 * @param pre_is_sub 上一个结点的类型
	 */

	if (!h) {
		if (pre_is_sub) {
			max_depth = max(max_depth, now_depth);
		}
		return;
	}

	max_depth = max(max_depth, now_depth);

	if (h->type == LIST) {
		Depth(h->sublist, max_depth, now_depth + 1, true);
		Depth(h->next, max_depth, now_depth, false);
	} else {
		Depth(h->next, max_depth, now_depth, false);
	}
}

template<class T>
void GList<T>::Replace(GListNode<T>* h, T ori, T x) {
	if (!h) {
		return;
	}

	if (h->type == ATOM) {
		if (h->data == ori) {
			h->data = x;
		}
		Replace(h->next, ori, x);
	} else {
		Replace(h->sublist, ori, x);
		Replace(h->next, ori, x);
	}
}

template<class T>
void GList<T>::Delete(GListNode<T>* pre, GListNode<T>* h, T c, bool pre_is_sub) {
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

// -------------------------以下为用户可调用函数--------------------------

template<class T>
GList<T>::GList() {
	head = new GListNode<T>;
	head->type = LIST;
	head->sublist = nullptr;
	head->next = nullptr;
}

template<class T>
GList<T>::GList(char s[]) {
	int* i = new int(0);
	head = DoCreat(s, *i);
}

template<class T>
int GList<T>::Length() {
	int res = Length(head->sublist);
	return res;
}

template<class T>
int GList<T>::Depth() {
	int max_depth = 0;
	int now_depth = 0;
	bool pre_is_sub = false;
	Depth(head, max_depth, now_depth, pre_is_sub);
	return max_depth;
}

template<class T>
void GList<T>::Output() {
	DoOutput(head);
	cout << "\n";
}

template<class T>
void GList<T>::Replace(T ori, T x) {
	Replace(head, ori, x);
}

template<class T>
void GList<T>::Delete(T x) {
	Delete(head, head->sublist, x, true);
}

#endif //INC_3__DATASTRUCTURES_GLIST_H