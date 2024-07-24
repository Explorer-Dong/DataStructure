//
// Created by 董文杰 on 2023-10-10.
//

#ifndef INC_3__DATASTRUCTURES_SEQQUEUENUM_H
#define INC_3__DATASTRUCTURES_SEQQUEUENUM_H

template<class T, int MaxSize>
class CircleSeqQueueWithNum {
private:
    T data[MaxSize];
    int head, tail;
    int num;

public:
    CircleSeqQueueWithNum() : head(0), tail(-1), num(0) {}
    void Push(T x);
    void Pop();
    T Front();
    bool Empty() { return !num; }
};

template<class T, int MaxSize>
void CircleSeqQueueWithNum<T, MaxSize>::Push(T x) {
    if (num == MaxSize - 1) {
        cerr << "full queue\n";
        exit(1);
    }
    data[tail] = x;
    tail = (tail + 1) % MaxSize;
    num++;
}

template<class T, int MaxSize>
void CircleSeqQueueWithNum<T, MaxSize>::Pop() {
    if (!num) {
        cerr << "empty queue\n";
        exit(1);
    }
    head = (head + 1) % MaxSize;
    num--;
}

template<class T, int MaxSize>
T CircleSeqQueueWithNum<T, MaxSize>::Front() {
    if (!num) {
        cerr << "empty queue\n";
        exit(1);
    }
    return data[head];
}

#endif //INC_3__DATASTRUCTURES_SEQQUEUENUM_H