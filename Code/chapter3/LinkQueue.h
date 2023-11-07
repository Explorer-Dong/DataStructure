//
// Created by 董文杰 on 2023-10-10.
//

#include "../chapter2/Node.h"


#ifndef INC_3__DATASTRUCTURES_LINKQUEUE_H
#define INC_3__DATASTRUCTURES_LINKQUEUE_H

// 含头结点且只有一个尾指针的循环链式队列
template<class T>
class LinkQueue {
private:
	Node<T>* rear;

public:
	LinkQueue();
	~LinkQueue();
	void Clear();
	void Push(T x);
	T Pop();
};

template<class T>
LinkQueue<T>::LinkQueue() {
	Node<T>* hh = new Node<T>();
	rear = hh;
}

template<class T>
LinkQueue<T>::~LinkQueue() {
	// 0个结点
	if (!rear->next) {
		cerr << "空队列，无法清空" << "\n";
		exit(1);
	}
	// 释放除了尾结点以外的所有的结点
	Node<T>* hh = rear->next;
	while (hh->next != rear) {
		Node<T>* front = hh->next;
		hh = front->next;
		delete front;
	}
	// 释放最后一个结点
	Node<T>* last = rear;
	rear = hh;
	hh->next = nullptr;
	delete last;
}

template<class T>
void LinkQueue<T>::Clear() {
	// 0个结点
	if (!rear->next) {
		cerr << "空队列，无法清空" << "\n";
		exit(1);
	}
	// 释放除了尾结点以外的所有的结点
	Node<T>* hh = rear->next;
	while (hh->next != rear) {
		Node<T>* front = hh->next;
		hh = front->next;
		delete front;
	}
	// 释放最后一个结点
	Node<T>* last = rear;
	rear = hh;
	hh->next = nullptr;
	delete last;
}

template<class T>
void LinkQueue<T>::Push(T x) {
	Node<T>* now = new Node<T>(x);
	// 区分首次入队
	Node<T>* hh = nullptr;
	if (!rear->next) {
		hh = rear;
	} else {
		hh = rear->next;
	}
	rear->next = now;
	rear = now;
	now->next = hh;
}

template<class T>
T LinkQueue<T>::Pop() {
	if (!rear->next) {
		cerr << "下溢" << "\n";
		exit(1);
	}
	Node<T>* hh = rear->next;
	Node<T>* front = hh->next;
	T res = front->data;
	if (front->next == hh) { // 弹出最后一个结点的情况，置空用来进行健壮性编写
		rear = hh;
		hh->next = nullptr;
	} else {
		hh->next = front->next;
		delete front;
	}
	return res;
}

#endif //INC_3__DATASTRUCTURES_LINKQUEUE_H
















