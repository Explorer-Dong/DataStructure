//
// Created by 董文杰 on 2023-09-28.
//
#include <iostream>

using namespace std;

#ifndef INC_3__DATASTRUCTURES_SEQSTACK_H
#define INC_3__DATASTRUCTURES_SEQSTACK_H

template<class T, int MaxSize>
class SeqStack
{
private:
	T data[MaxSize];
	int top;
public:
	SeqStack() : top(-1) {}

	void Push(T x);
	T Pop();
	T Top();
	bool Empty();
};

template<class T, int MaxSize>
void SeqStack<T, MaxSize>::Push(T x) {
	if (top == MaxSize - 1) {
		cerr << "上溢" << endl;
		exit(1);
	}
	data[++top] = x;
}

template<class T, int MaxSize>
T SeqStack<T, MaxSize>::Pop() {
	if (top == -1) {
		cerr << "下溢" << endl;
		exit(1);
	}
	T res = data[top--];
	return res;
}

template<class T, int MaxSize>
T SeqStack<T, MaxSize>::Top() {
	if (top == -1) {
		cerr << "下溢" << endl;
		exit(1);
	}
	return data[top];
}

template<class T, int MaxSize>
bool SeqStack<T, MaxSize>::Empty() {
	return top == -1;
}

#endif //INC_3__DATASTRUCTURES_SEQSTACK_H
