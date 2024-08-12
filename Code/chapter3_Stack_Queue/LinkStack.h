#include <iostream>
#include "../chapter2_List//Node.h"

using namespace std;

#ifndef LINKSTACK_H
#define LINKSTACK_H

template<class T>
class LinkStack {
private:
    Node<T>* top;

public:
    LinkStack() : top(nullptr) {}
    
    ~LinkStack();
    void Push(T x);
    void Pop();
    T Top();
    bool Empty();
};

template<class T>
LinkStack<T>::~LinkStack() {
    while (top) {
        Node<T>* p = top;
        top = top->next;
        delete p;
    }
}

template<class T>
void LinkStack<T>::Push(T x) {
    Node<T>* now = new Node<T>(x);
    now->next = top;
    top = now;
}

template<class T>
void LinkStack<T>::Pop() {
    if (!top) {
        cerr << "underflow!" << endl;
        exit(1);
    }
    Node<T>* temp = top;
    top = top->next;
    delete temp;
}

template<class T>
T LinkStack<T>::Top() {
    if (!top) {
        cerr << "underflow!" << endl;
        exit(1);
    }
    return top->data;
}

template<class T>
bool LinkStack<T>::Empty() {
    return !top;
}

#endif //LINKSTACK_H