//
// Created by 董文杰 on 2023-10-10.
//

#include "SeqStack.h"

#ifndef INC_3__DATASTRUCTURES_DSTACK2QUEUE_H
#define INC_3__DATASTRUCTURES_DSTACK2QUEUE_H

template<class T, int MaxSize>
class Dstack2Queue {
private:
	SeqStack<T, MaxSize> A;
	SeqStack<T, MaxSize> B;

public:
	Dstack2Queue() {}
	void Push(T x);
	T Pop();
	T Front();
	bool Empty();
};

template<class T, int MaxSize>
void Dstack2Queue<T, MaxSize>::Push(T x) {
	// 由于A和B栈已经有上溢的检查，所以这里不需要再检查
	while (!B.Empty()) {
		A.Push(B.Top());
		B.Pop();
	}
	A.Push(x);
}

template<class T, int MaxSize>
T Dstack2Queue<T, MaxSize>::Pop() {
	while (!A.Empty()) {
		B.Push(A.Top());
		A.Pop();
	}
	if (B.Empty()) {
		cerr << "队空" << "\n";
		exit(1);
	}
	T res = B.Pop();
	return res;
}

template<class T, int MaxSize>
T Dstack2Queue<T, MaxSize>::Front() {
	while (!A.Empty()) {
		B.Push(A.Top());
		A.Pop();
	}
	if (B.Empty()) {
		cerr << "队空" << "\n";
		exit(1);
	}
	return B.Top();
}

template<class T, int MaxSize>
bool Dstack2Queue<T, MaxSize>::Empty() {
	return A.Empty() && B.Empty();
}

#endif //INC_3__DATASTRUCTURES_DSTACK2QUEUE_H
