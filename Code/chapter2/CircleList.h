#include <iostream>
#include "Node.h"

using namespace std;

template<class T>
class CircleList
{
private:
	Node<T>* head;

public:
	CircleList() : head(nullptr) {}
	CircleList(T a[], int n);
	~CircleList();

	int CountNode();
};

template<class T>
CircleList<T>::CircleList(T a[], int n) {
	head = nullptr;

	if (!n) return;

	for (int i = n - 1; i >= 0; i--) {
		Node<T>* now = new Node<T>();
		now->data = a[i];
		now->next = head;
		head = now;
	}

	Node<T>* p = head;
	while (p->next) p = p->next;
	p->next = head;
}

template<class T>
CircleList<T>::~CircleList() {
	// 0个结点
	if (!head) return;

	// 1个结点
	if (head->next == head)
		delete head;

	// >= 2个结点
	Node<T>* p = head->next;
	while (p != head) {
		Node<T>* now = p;
		p = p->next;
		delete now;
	}
	delete head;
}

template<class T>
int CircleList<T>::CountNode() {
	if (!head) return 0;

	int res = 1;
	Node<T>* p = head->next;
	while (p != head) {
		res++;
		p = p->next;
	}
	return res;
}
