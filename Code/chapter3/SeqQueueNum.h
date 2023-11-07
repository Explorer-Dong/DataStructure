//
// Created by 董文杰 on 2023-10-10.
//

#ifndef INC_3__DATASTRUCTURES_SEQQUEUENUM_H
#define INC_3__DATASTRUCTURES_SEQQUEUENUM_H

// 以辅助变量num来记录队列的元素数量
template<class T, int MaxSize>
class SeqQueueNum {
private:
	T data[MaxSize];
	int front, rear;
	int num;

public:
	SeqQueueNum();
	void Push(T x);
	T Pop();
	T Front();
	bool Empty();
};

template<class T, int MaxSize>
SeqQueueNum<T, MaxSize>::SeqQueueNum() {
	front = 0;
	rear = 0;
	num = 0;
}

template<class T, int MaxSize>
void SeqQueueNum<T, MaxSize>::Push(T x) {
	if (num == MaxSize) {
		cerr << "队满" << "\n";
		exit(1);
	}
	data[rear] = x;
	num++;
	rear = (rear + 1) % MaxSize;
}

template<class T, int MaxSize>
T SeqQueueNum<T, MaxSize>::Pop() {
	if (!num) {
		cerr << "队空" << "\n";
		exit(1);
	}
	T res = data[front];
	front = (front + 1) % MaxSize;
	num--;
	return res;
}

template<class T, int MaxSize>
T SeqQueueNum<T, MaxSize>::Front() {
	if (!num) {
		cerr << "队空" << "\n";
		exit(1);
	}
	return data[front];
}

template<class T, int MaxSize>
bool SeqQueueNum<T, MaxSize>::Empty() {
	return !num;
}

#endif //INC_3__DATASTRUCTURES_SEQQUEUENUM_H
