#include <iostream>
#include <queue>
#include "Node.h"

using namespace std;

#ifndef INC_2__DATASTRUCTURES_LINKLIST_H
#define INC_2__DATASTRUCTURES_LINKLIST_H

template<class T>
class LinkList {
private:

public:
	Node<T>* head;

	LinkList() : head(nullptr) {}
	LinkList(T a[], int n);
	LinkList(LinkList<T>& obj); // T7: 复制一个单链表
	~LinkList();

	void Output();
	void Insert(int pos, T x);
	Node<T>* Reverse(Node<T>* node);
	void Split(LinkList<T>& odd, LinkList<T>& even); // T6: 将链表分解为奇数与偶数链表，且原链表保持不变
	void SortAndOutput(); // T8: 递增打印链表数据
	void Merge(LinkList<T>& obj); // T10: 合并两个有序链表
};

template<class T>
LinkList<T>::LinkList(T a[], int n) {
	// 逆向头插
	head = nullptr;
	for (int i = n - 1; i >= 0; i--) {
		Node<T>* now = new Node<T>();
		now->data = a[i];
		now->next = head;
		head = now;
	}
}

template<class T>
LinkList<T>::LinkList(LinkList<T>& obj) {
	// 头插 + 反转 = 逆向头插
	head = nullptr;
	Node<T>* p = obj.head;
	while (p) {
		Node<T>* now = new Node<T>();
		now->data = p->data;
		now->next = head;
		head = now;
		p = p->next;
	}
	head = Reverse(head);
}

template<class T>
LinkList<T>::~LinkList() {
	Node<T>* p = head;
	while (p) {
		Node<T>* now = p;
		p = p->next;
		delete now;
	}
}

template<class T>
void LinkList<T>::Output() {
	Node<T>* p = head;
	while (p) {
		cout << p->data << " \n"[!p->next];
		p = p->next;
	}
}

template<class T>
void LinkList<T>::Insert(int pos, T x) {
	if (pos < 0) {
		cerr << "插入位置不能为负" << endl;
		return;
	}

	// 插在第一个位置
	if (!pos) {
		Node<T>* now = new Node<T>();
		now->data = x;
		now->next = head;
		head = now;
		return;
	}

	// 找到要插入位置的前一个位置的指针 p
	Node<T>* p = head;
	for (int i = 0; i < pos - 1; i++) {
		p = p->next;
		if (!p) {
			cerr << "插入位置超过链表长度！" << endl;
			return;
		}
	}

	Node<T>* now = new Node<T>();
	now->data = x;
	now->next = p->next;
	p->next = now;
}

/**
@note 法一：三指针迭代
template<class T>
Node<T>* LinkList<T>::Reverse(Node<T>* node)
{
	if (!node) return node;


	Node<T>* pre = nullptr, * now = node;

	while (now)
	{
		Node<T>* temp = now->next;
		now->next = pre;
		pre = now;
		now = temp;
	}
	return pre;
}
*/

// 法二：头插法双指针迭代
template<class T>
Node<T>* LinkList<T>::Reverse(Node<T>* node) {
	if (!node) return node; // 空表
	Node<T>* tail = nullptr;
	Node<T>* p = node;
	while (p) {
		Node<T>* now = p;
		p = p->next;
		now->next = tail;
		tail = now;
	}
	return tail;
}

/**
 法三：递归
 @note 返回当前链表的尾结点并且实现反转以当前结点为头结点的整个链表
template<class T>
Node<T>* LinkList<T>::Reverse(Node<T>* node) {
	if (!node || !node->next) return node; // 空表 or 尾结点
	Node<T>* tail = Reverse(node->next);
	node->next->next = node;
	node->next = nullptr;
	return tail;
}
*/

template<class T>
void LinkList<T>::Split(LinkList<T>& odd, LinkList<T>& even) {
	int cnt1 = 0, cnt2 = 0;
	Node<T>* p = head;
	while (p) {
		if (p->data % 2) odd.Insert(cnt1++, p->data);
		else even.Insert(cnt2++, p->data);
		p = p->next;
	}
}

template<class T>
void LinkList<T>::SortAndOutput() {
	Node<T>* p = head;
	priority_queue<T, vector<T>, greater<T>> q;
	while (p) {
		q.push(p->data);
		p = p->next;
	}
	while (q.size()) {
		cout << q.top() << ' ';
		q.pop();
	}
}

template<class T>
void LinkList<T>::Merge(LinkList<T>& obj) {
	Node<T>* p = head, * q = obj.head;
	head = nullptr;
	while (p && q) {
		if (p->data < q->data) {
			Node<T>* now = new Node<T>();
			now->data = p->data;
			now->next = head;
			head = now;
			p = p->next;
		} else {
			Node<T>* now = new Node<T>();
			now->data = q->data;
			now->next = head;
			head = now;
			q = q->next;
		}
	}
	while (p) {
		Node<T>* now = new Node<T>();
		now->data = p->data;
		now->next = head;
		head = now;
		p = p->next;
	}
	while (q) {
		Node<T>* now = new Node<T>();
		now->data = q->data;
		now->next = head;
		head = now;
		q = q->next;
	}
	head = Reverse(head);
}

#endif //INC_2__DATASTRUCTURES_LINKLIST_H