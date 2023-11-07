//
// Created by 董文杰 on 2023-09-28.
//

#include <iostream>
#include "../chapter2/Node.h"

using namespace std;

#ifndef INC_3__DATASTRUCTURES_LINKSTACK_H
#define INC_3__DATASTRUCTURES_LINKSTACK_H

template<class T>
class LinkStack
{
private:
	Node<T>* top;

public:
	LinkStack() : top(nullptr) {}
	~LinkStack();

	void Push(T x);
	T Pop();
	T Top();
	bool Empty();
};

template<class T>
LinkStack<T>::~LinkStack() {
	while (top) {
		Node<T>* p = top;
		top = top->next;
		delete p;
	}
}

template<class T>
void LinkStack<T>::Push(T x) {
	Node<T>* now = new Node<T>(x);
	now->next = top;
	top = now;
}

template<class T>
T LinkStack<T>::Pop() {
	if (!top) {
		cerr << "下溢" << endl;
		exit(1);
	}
	Node<T>* now = top;
	top = top->next;
	T res = now->data;
	delete now;
	return res;
}

template<class T>
T LinkStack<T>::Top() {
	if (!top) {
		cerr << "下溢" << endl;
		exit(1);
	}
	return top->data;
}

template<class T>
bool LinkStack<T>::Empty() {
	return !top;
}

#endif //INC_3__DATASTRUCTURES_LINKSTACK_H
