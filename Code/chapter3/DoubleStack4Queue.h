//
// Created by 董文杰 on 2023-10-10.
//

#include "SeqStack.h"

#ifndef INC_3__DATASTRUCTURES_DSTACK2QUEUE_H
#define INC_3__DATASTRUCTURES_DSTACK2QUEUE_H

template<class T, int MaxSize>
class DoubleStack4Queue {
private:
    SeqStack<T, MaxSize> A; // top for queue push
    SeqStack<T, MaxSize> B; // top for queue pop

public:
    DoubleStack4Queue() {}
    void Push(T x);
    void Pop();
    T Front();
    bool Empty();
};

template<class T, int MaxSize>
void DoubleStack4Queue<T, MaxSize>::Push(T x) {
    // Stack already has overflow check
    while (!B.Empty()) {
        A.Push(B.Top());
        B.Pop();
    }
    A.Push(x);
}

template<class T, int MaxSize>
void DoubleStack4Queue<T, MaxSize>::Pop() {
    while (!A.Empty()) {
        B.Push(A.Top());
        A.Pop();
    }
    if (B.Empty()) {
        cerr << "empty queue\n";
        exit(1);
    }
    B.Pop();
}

template<class T, int MaxSize>
T DoubleStack4Queue<T, MaxSize>::Front() {
    while (!A.Empty()) {
        B.Push(A.Top());
        A.Pop();
    }
    if (B.Empty()) {
        cerr << "empty queue\n";
        exit(1);
    }
    return B.Top();
}

template<class T, int MaxSize>
bool DoubleStack4Queue<T, MaxSize>::Empty() {
    return A.Empty() && B.Empty();
}

#endif //INC_3__DATASTRUCTURES_DSTACK2QUEUE_H