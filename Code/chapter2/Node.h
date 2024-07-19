#ifndef NODE_H
#define NODE_H

template<class T>
struct Node {
    T data;
    Node<T>* next;
    Node() : next(nullptr) {}
    Node(T x) : data(x), next(nullptr) {}
};

#endif