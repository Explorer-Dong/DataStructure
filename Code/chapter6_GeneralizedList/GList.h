#include <iostream>
#include <string>

using namespace std;

#ifndef GLIST_H
#define GLIST_H

enum GListNodeType {
    ATOM, LIST
};
template<class T>
struct GListNode {
    GListNodeType type;
    union {
        T data;
        GListNode* sublist;
    };
    GListNode<T>* next;
};

template<class T>
class GList {
private:
    GListNode<T>* create(const string& s, int& i);
    void decreate(GListNode<T>* now);
    void print(GListNode<T>* now);
    int length(GListNode<T>* now);
    int depth(GListNode<T>* now);
    void replaceAtom(GListNode<T>* h, T origin, T target);
    void deleteAtom(GListNode<T>* pre, GListNode<T>* now, T x);
    bool same(GListNode<T>* pa, GListNode<T>* pb);

public:
    GListNode<T>* head;
    GList();
    GList(const string& s);               // create with string
    ~GList();
    void print();                         // print glist
    int length();                         // calculate glist length
    int depth();                          // calculate glist depth
    void replaceAtom(T origin, T target); // replace atoms from origin to target
    void deleteAtom(T x);                 // delete atoms of x
    bool same(GList<T>& obj);             // compare to another glist
};

template<class T>
GListNode<T>* GList<T>::create(const string& s, int& i) {
    while (i < s.size() && (s[i] == ' ' || s[i] == ',')) {
        i++;
    }
    
    if (i == s.size()) {
        return nullptr;
    } else if (s[i] == ')') {
        i++;
        return nullptr;
    }
    
    GListNode<T>* h = new GListNode<T>;
    T now = s[i++];
    
    if (now == '(') {
        h->type = LIST;
        h->sublist = create(s, i);
        h->next = create(s, i);
    } else {
        h->type = ATOM;
        h->data = now;
        h->next = create(s, i);
    }
    
    return h;
}

template<class T>
void GList<T>::decreate(GListNode<T>* now) {
    if (!now) {
        return;
    }
    if (now->type == LIST) {
        decreate(now->sublist);
        decreate(now->next);
    } else {
        decreate(now->next);
    }
    delete now;
}

template<class T>
void GList<T>::print(GListNode<T>* now) {
    if (!now) {
        return;
    }
    
    if (now->type == ATOM) {
        cout << now->data;
    } else { // now->type == LIST
        cout << '(';
        print(now->sublist);
        cout << ')';
    }
    
    if (now->next) {
        cout << ',';
        print(now->next);
    }
}

template<class T>
int GList<T>::length(GListNode<T>* now) {
    if (!now) {
        return 0;
    }
    return length(now->next) + 1;
}

template<class T>
int GList<T>::depth(GListNode<T>* now) {
    if (!now) {
        return 0;
    }
    if (now->type == ATOM) {
        return depth(now->next);
    } else {
        return max(1 + depth(now->sublist), depth(now->next));
    }
}

template<class T>
void GList<T>::replaceAtom(GListNode<T>* now, T origin, T target) {
    if (!now) {
        return;
    }
    
    if (now->type == ATOM) {
        if (now->data == origin) {
            now->data = target;
        }
        replaceAtom(now->next, origin, target);
    } else {
        replaceAtom(now->sublist, origin, target);
        replaceAtom(now->next, origin, target);
    }
}

template<class T>
void GList<T>::deleteAtom(GListNode<T>* pre, GListNode<T>* now, T x) {
    if (!now) {
        return;
    }
    
    if (now->type == LIST) {
        deleteAtom(now, now->sublist, x);
        deleteAtom(now, now->next, x);
    } else if (now->data == x) {
        GListNode<T>* temp = now;
        now = now->next;
        delete temp;
        if (pre->type == LIST) {
            pre->sublist = now;
        } else {
            pre->next = now;
        }
        deleteAtom(now, now->next, x);
    } else {
        deleteAtom(now, now->next, x);
    }
}

template<class T>
bool GList<T>::same(GListNode<T>* pa, GListNode<T>* pb) {
    if (!pa && !pb) {
        return true;
    } else if (pa && !pb || !pa && pb) {
        return false;
    } else if (pa->type != pb->type) {
        return false;
    } else if (pa->type == ATOM) {
        // both are atom
        return pa->data == pb->data && same(pa->next, pb->next);
    } else {
        // both are list
        return same(pa->sublist, pb->sublist) && same(pa->next, pb->next);
    }
}

template<class T>
GList<T>::GList() {
    head = new GListNode<T>;
    head->type = LIST;
    head->sublist = nullptr;
    head->next = nullptr;
}

template<class T>
GList<T>::GList(const string& s) {
    int i = 0;
    head = create(s, i);
}

template<class T>
GList<T>::~GList() {
    decreate(head);
}

template<class T>
void GList<T>::print() {
    print(head);
    cout << "\n";
}

template<class T>
int GList<T>::length() {
    int res = length(head->sublist);
    return res;
}

template<class T>
int GList<T>::depth() {
    return depth(head);
}

template<class T>
void GList<T>::replaceAtom(T origin, T target) {
    replaceAtom(head, origin, target);
}

template<class T>
void GList<T>::deleteAtom(T x) {
    deleteAtom(head, head->sublist, x);
}

template<class T>
bool GList<T>::same(GList<T>& obj) {
    return same(this->head, obj.head);
}

#endif //GLIST_H