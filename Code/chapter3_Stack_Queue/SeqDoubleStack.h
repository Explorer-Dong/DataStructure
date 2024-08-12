#include <iostream>

using namespace std;

#ifndef SEQDOUBLESTACK_H
#define SEQDOUBLESTACK_H

template<class T, int MaxSize>
class SeqDoubleStack {
private:
    T data[MaxSize];
    int l, r;

public:
    SeqDoubleStack() : l(-1), r(MaxSize) {}
    
    void Push_front(T x);
    T Pop_front();
    void Push_back(T x);
    T Pop_back();
    void Output();
};

template<class T, int MaxSize>
void SeqDoubleStack<T, MaxSize>::Push_front(T x) {
    if (l + 1 == r) {
        cerr << "full size" << endl;
        exit(1);
    }
    data[++l] = x;
}

template<class T, int MaxSize>
T SeqDoubleStack<T, MaxSize>::Pop_front() {
    if (l == -1) {
        cerr << "empty left stack" << endl;
        exit(1);
    }
    T now = data[l--];
    return now;
}

template<class T, int MaxSize>
void SeqDoubleStack<T, MaxSize>::Push_back(T x) {
    if (l + 1 == r) {
        cerr << "full size" << endl;
        exit(1);
    }
    data[--r] = x;
}

template<class T, int MaxSize>
T SeqDoubleStack<T, MaxSize>::Pop_back() {
    if (r == MaxSize) {
        cerr << "empty right stack" << endl;
        exit(1);
    }
    T now = data[r++];
    return now;
}

template<class T, int MaxSize>
void SeqDoubleStack<T, MaxSize>::Output() {
    for (int i = 0; i <= l; i++) {
        cout << data[i] << " \n"[i == l];
    }
    for (int i = MaxSize - 1; i >= r; i--) {
        cout << data[i] << " \n"[i == r];
    }
}

#endif //SEQDOUBLESTACK_H