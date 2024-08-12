#include "./Node.h"

#ifndef CircleList_H
#define CircleList_H

template<class T>
class CircleList {
private:
    Node<T>* tail;

public:
    CircleList();
    ~CircleList();
    
    void PushBack(T x);  // push element to end
    void PopFront();     // pop front element
    void Clear();        // clear all elements
    int CountNode();     // count node number
};

template<class T>
CircleList<T>::CircleList() {
    tail = new Node<T>();
    tail->next = tail;
}

template<class T>
CircleList<T>::~CircleList() {
    while (tail->next != tail) {
        PopFront();
    }
}

template<class T>
void CircleList<T>::PushBack(T x) {
    Node<T>* now = new Node<T>(x);
    Node<T>* temp = tail->next;
    tail->next = now;
    tail = now;
    tail->next = temp;
}

template<class T>
void CircleList<T>::PopFront() {
    if (tail->next == tail) {
        std::cerr << "empty circle list!" << "\n";
        exit(1);
    }
    if (tail->next->next == tail) {
        // one node
        Node<T>* temp = tail;
        tail = tail->next;
        tail->next = tail;
        delete temp;
    } else {
        // at least two nodes
        Node<T>* temp = tail->next->next;
        tail->next->next = temp->next;
        delete temp;
    }
}

template<class T>
void CircleList<T>::Clear() {
    while (tail->next != tail) {
        PopFront();
    }
}

template<class T>
int CircleList<T>::CountNode() {
    int ans = 0;
    for (Node<T>* p = tail->next; p != tail; p = p->next) {
        ans++;
    }
    return ans;
}

#endif