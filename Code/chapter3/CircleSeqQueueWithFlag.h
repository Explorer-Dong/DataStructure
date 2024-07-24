//
// Created by 董文杰 on 2023-10-09.
//

#include <iostream>

using namespace std;

#ifndef INC_3__DATASTRUCTURES_SEQQUEUEFLAG_H
#define INC_3__DATASTRUCTURES_SEQQUEUEFLAG_H

template<class T, int MaxSize>
class CircleSeqQueueWithFlag {
private:
    T data[MaxSize];
    int head, tail;
    bool is_empty; // flag var

public:
    CircleSeqQueueWithFlag() : head(0), tail(-1), is_empty(true) {}
    void Push(T x);
    void Pop();
    T Front();
    bool Empty() { return is_empty; }
};

template<class T, int MaxSize>
void CircleSeqQueueWithFlag<T, MaxSize>::Push(T x) {
    if ((tail + 1) % MaxSize == head && !is_empty) {
        cerr << "full queue!\n";
        exit(1);
    }
    data[(tail + 1) % MaxSize] = x;
    tail = (tail + 1) % MaxSize;
    is_empty = false;
}

template<class T, int MaxSize>
void CircleSeqQueueWithFlag<T, MaxSize>::Pop() {
    if (is_empty) {
        cerr << "empty queue\n";
        exit(1);
    }
    head = (head + 1) % MaxSize;
    if ((tail + 1) % MaxSize == head) {
        is_empty = true;
    }
}

template<class T, int MaxSize>
T CircleSeqQueueWithFlag<T, MaxSize>::Front() {
    if (is_empty) {
        cerr << "empty queue\n";
        exit(1);
    }
    return data[head];
}

#endif //INC_3__DATASTRUCTURES_SEQQUEUEFLAG_H