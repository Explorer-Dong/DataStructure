//
// Created by 董文杰 on 2023-10-09.
//

#include <iostream>
using namespace std;


#ifndef INC_3__DATASTRUCTURES_SEQQUEUEFLAG_H
#define INC_3__DATASTRUCTURES_SEQQUEUEFLAG_H

// 以辅助bool变量flag来判断队满与队空的情况
template<class T, int MaxSize>
class SeqQueueFlag
{
private:
	T data[MaxSize];
	int front, rear;
	bool flag;

public:
	SeqQueueFlag();
	void Push(T x);
	T Pop();
	T Front();
	bool Empty();
};

template<class T, int MaxSize>
SeqQueueFlag<T, MaxSize>::SeqQueueFlag() {
	front = 0;
	rear = 0;
	flag = false;
}

template<class T, int MaxSize>
void SeqQueueFlag<T, MaxSize>::Push(T x) {
	if (flag) {
		cerr << "队满" << "\n";
		exit(1);
	}
	data[rear] = x;
	rear = (rear + 1) % MaxSize;
	if (rear == front) {
		flag = true;
	}
}

template<class T, int MaxSize>
T SeqQueueFlag<T, MaxSize>::Pop() {
	if (rear == front && !flag) {
		cerr << "队空" << "\n";
		exit(1);
	}
	T res = data[front];
	front = (front + 1) % MaxSize;
	if (flag) {
		flag = false;
	}
	return res;
}

template<class T, int MaxSize>
T SeqQueueFlag<T, MaxSize>::Front() {
	if (rear == front && !flag) {
		cerr << "队空" << "\n";
		exit(1);
	}
	return data[front];
}

template<class T, int MaxSize>
bool SeqQueueFlag<T, MaxSize>::Empty() {
	return front == rear && !flag;
}

#endif //INC_3__DATASTRUCTURES_SEQQUEUEFLAG_H




























