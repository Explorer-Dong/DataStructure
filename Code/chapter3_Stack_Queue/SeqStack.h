#include <iostream>

using namespace std;

#ifndef SEQSTACK_H
#define SEQSTACK_H

template<class T, int MaxSize>
class SeqStack {
private:
    T data[MaxSize];
    int top;

public:
    SeqStack() : top(-1) {}
    
    void Push(T x);
    void Pop();
    T Top();
    bool Empty();
};

template<class T, int MaxSize>
void SeqStack<T, MaxSize>::Push(T x) {
    if (top == MaxSize - 1) {
        cerr << "overflow!" << endl;
        exit(1);
    }
    data[++top] = x;
}

template<class T, int MaxSize>
void SeqStack<T, MaxSize>::Pop() {
    if (top == -1) {
        cerr << "underflow!" << endl;
        exit(1);
    }
    --top;
}

template<class T, int MaxSize>
T SeqStack<T, MaxSize>::Top() {
    if (top == -1) {
        cerr << "underflow!" << endl;
        exit(1);
    }
    return data[top];
}

template<class T, int MaxSize>
bool SeqStack<T, MaxSize>::Empty() {
    return top == -1;
}

#endif //SEQSTACK_H