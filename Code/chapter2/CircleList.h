#include <iostream>
#include "Node.h"

using namespace std;

template<class T>
class CircleList {
private:
    Node<T>* head;

public:
    CircleList() : head(nullptr) {}
    CircleList(T a[], int n);
    ~CircleList();
    
    int CountNode();
};

template<class T>
CircleList<T>::CircleList(T a[], int n) : head(nullptr) {
    if (!n) return;
    for (int i = n - 1; i >= 0; i--) {
        Node<T>* now = new Node<T>(a[i]);
        now->next = head;
        head = now;
    }
    Node<T>* p = head;
    while (p->next) {
        p = p->next;
    }
    p->next = head;
}

template<class T>
CircleList<T>::~CircleList() {
    // 0 node
    if (!head) {
        return;
    }
    
    // at least 1 node
    Node<T>* p = head->next;
    while (p != head) {
        Node<T>* now = p;
        p = p->next;
        delete now;
    }
    delete head;
}

template<class T>
int CircleList<T>::CountNode() {
    if (!head) {
        return 0;
    }
    
    int res = 1;
    for (Node<T>* p = head->next; p != head; p = p->next) {
        res++;
    }
    return res;
}
