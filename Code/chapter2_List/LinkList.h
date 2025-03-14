#include <iostream>
#include <queue>
#include <fstream>
#include "./Node.h"

using namespace std;

#ifndef LINKLIST_H
#define LINKLIST_H

template<class T>
class LinkList {
private:
    Node<T>* head;
    Node<T>* Reverse(Node<T>* node);                 // reverse a list

public:
    
    LinkList() : head(nullptr) {}
    
    LinkList(T a[], int n);
    LinkList(LinkList<T>& obj);                      // T7: copy construct
    ~LinkList();
    void Output();                                   // print to console
    void OutputToFile(const string& path);           // print to file
    void PushFront(T x);                             // push node to head
    void Reverse();                                  // public use to reverse a list
    void Delete(T x);                                // delete item with value of x
    bool Find(T x);                                  // find item with value of x
    void Split(LinkList<T>& odd, LinkList<T>& even); // T6: split into odd and even
    void PrintInOrder();                             // T8: print list in order
    void Merge(LinkList<T>& obj);                    // T10: merge two ordered list
};

template<class T>
LinkList<T>::LinkList(T a[], int n) {
    // reverse pushfront to build a forward list
    head = nullptr;
    for (int i = n - 1; i >= 0; i--) {
        Node<T>* now = new Node<T>();
        now->data = a[i];
        now->next = head;
        head = now;
    }
}

template<class T>
LinkList<T>::LinkList(LinkList<T>& obj) {
    head = nullptr;
    Node<T>* p = obj.head;
    while (p) {
        Node<T>* now = new Node<T>();
        now->data = p->data;
        now->next = head;
        head = now;
        p = p->next;
    }
    head = Reverse(head);
}

template<class T>
LinkList<T>::~LinkList() {
    Node<T>* p = head;
    while (p) {
        Node<T>* now = p;
        p = p->next;
        delete now;
    }
}

template<class T>
void LinkList<T>::Output() {
    Node<T>* p = head;
    while (p) {
        cout << p->data << "\n";
        p = p->next;
    }
}

template<class T>
void LinkList<T>::OutputToFile(const string& path) {
    ofstream out(path);
    Node<T>* q = head, * p = head;
    int cnt = 0;
    while (q) {
        cnt++;
        q = q->next;
    }
    out << cnt << "\n";
    while (p) {
        out << p->data;
        p = p->next;
    }
    out.close();
}

template<class T>
void LinkList<T>::PushFront(T x) {
    Node<T>* now = new Node<T>(x);
    now->next = head;
    head = now;
}

/**
// method1: three points
template<class T>
Node<T>* LinkList<T>::Reverse(Node<T>* node) {
    if (!node) return node;
    Node<T>* pre = nullptr, * now = node;
    while (now) {
        Node<T>* temp = now->next;
        now->next = pre;
        pre = now;
        now = temp;
    }
    return pre;
}
*/

/**
// method2: two points
template<class T>
Node<T>* LinkList<T>::Reverse(Node<T>* node) {
	if (!node) return node; // empty list
	Node<T>* tail = nullptr;
	Node<T>* p = node;
	while (p) {
		Node<T>* now = p;
		p = p->next;
		now->next = tail;
		tail = now;
	}
	return tail;
}
*/

// method3: recursion
template<class T>
Node<T>* LinkList<T>::Reverse(Node<T>* node) {
    if (!node || !node->next) return node; // empty list or tail node
    Node<T>* tail = Reverse(node->next);
    node->next->next = node;
    node->next = nullptr;
    return tail;
}

template<class T>
void LinkList<T>::Reverse() {
    head = Reverse(head);
}

template<class T>
void LinkList<T>::Delete(T x) {
    Node<T>* p = head, * pre = nullptr;
    while (p) {
        if (p->data == x) {
            if (pre) {
                pre->next = p->next;
                delete p;
                return;
            } else {
                Node<T>* now = head;
                head = head->next;
                delete now;
                return;
            }
        } else {
            pre = p;
            p = p->next;
        }
    }
}

template<class T>
bool LinkList<T>::Find(T x) {
    Node<T>* p = head;
    while (p) {
        if (p->data == x) {
            return true;
        }
        p = p->next;
    }
    return false;
}

template<class T>
void LinkList<T>::Split(LinkList<T>& odd, LinkList<T>& even) {
    Node<T>* p = head;
    while (p) {
        if (p->data % 2) odd.PushFront(p->data);
        else even.PushFront(p->data);
        p = p->next;
    }
    odd.Reverse();
    even.Reverse();
}

template<class T>
void LinkList<T>::PrintInOrder() {
    Node<T>* p = head;
    priority_queue<T, vector<T>, greater<T>> q;
    while (p) {
        q.push(p->data);
        p = p->next;
    }
    while (q.size()) {
        cout << q.top() << " ";
        q.pop();
    }
}

template<class T>
void LinkList<T>::Merge(LinkList<T>& obj) {
    Node<T>* p = head, * q = obj.head;
    head = nullptr;
    while (p && q) {
        if (p->data < q->data) {
            Node<T>* now = new Node<T>();
            now->data = p->data;
            now->next = head;
            head = now;
            p = p->next;
        } else {
            Node<T>* now = new Node<T>();
            now->data = q->data;
            now->next = head;
            head = now;
            q = q->next;
        }
    }
    while (p) {
        Node<T>* now = new Node<T>();
        now->data = p->data;
        now->next = head;
        head = now;
        p = p->next;
    }
    while (q) {
        Node<T>* now = new Node<T>();
        now->data = q->data;
        now->next = head;
        head = now;
        q = q->next;
    }
    head = Reverse(head);
}

#endif //LINKLIST_H