//
// Created by 董文杰 on 2023-10-06.
//

#include <iostream>

using namespace std;

#ifndef INC_3__DATASTRUCTURES_SEQDOUBLESTACK_H
#define INC_3__DATASTRUCTURES_SEQDOUBLESTACK_H

template<class T, int MaxSize>
class SeqDoubleStack
{
private:
	T data[MaxSize];
	int l, r;

public:
	SeqDoubleStack();

	void Push_front(T x);
	T Pop_front();
	void Push_back(T x);
	T Pop_back();
//	void Output() {
//		for (int i = 0; i < MaxSize; i++) {
//			cout << data[i] << " \n"[i == MaxSize - 1];
//		}
//	}
};

template<class T, int MaxSize>
SeqDoubleStack<T, MaxSize>::SeqDoubleStack() {
	l = 0;
	r = MaxSize - 1;
}

template<class T, int MaxSize>
void SeqDoubleStack<T, MaxSize>::Push_front(T x) {
	if (l >= r) {
		cerr << "栈满" << endl;
		return;
	}
	data[l++] = x;
}

template<class T, int MaxSize>
T SeqDoubleStack<T, MaxSize>::Pop_front() {
	if (l == 0) {
		cerr << "左栈空" << endl;
	}
	T now = data[l--];
	return now;
}

template<class T, int MaxSize>
void SeqDoubleStack<T, MaxSize>::Push_back(T x) {
	if (r <= l) {
		cerr << "栈满" << endl;
		return;
	}
	data[r--] = x;
}

template<class T, int MaxSize>
T SeqDoubleStack<T, MaxSize>::Pop_back() {
	if (r == MaxSize - 1) {
		cerr << "右栈空" << endl;
	}
	T now = data[r++];
	return now;
}

#endif //INC_3__DATASTRUCTURES_SEQDOUBLESTACK_H



















