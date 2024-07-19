#include <bits/stdc++.h>

using namespace std;

#ifndef INC_2__DATASTRUCTURES_SEQLIST_H
#define INC_2__DATASTRUCTURES_SEQLIST_H

template<class T>
class SeqList {
private:
    T* data;
    int size;
    void Renew();
    void QuickSort(int left, int right);

public:
    SeqList() : data(nullptr), size(0) {}
    SeqList(T a[], int n);
    SeqList(int n) : data(new T[n]), size(n) {}
    ~SeqList();
    void Output();
    T DeleteMin();                         // T1: delete and return min
    void DeleteAllX(T x);                  // T2: delete all elements equal to x
    void DeleteRange(T left, T right);     // T3: delete ordered list's all elements range from s to t
    void Unique();                         // T4: unique
    void Insert(int pos, T x);
    void IncreaseInsert(T x);              // T5: insert x to ordered list
    void SortOnce();                       // T9: sort once
    void Sort();                           // exp T1: quick sort
    void Merge(SeqList<T>& obj);           // exp T1: merge two ordered list
    T& operator[](int idx) { return data[idx]; }
    bool find(T x);
};

template<class T>
void SeqList<T>::Renew() {
    // dynamic expansion
    int newsize = size + size;
    T* newdata = new T[newsize];
    for (int i = 0; i < size; i++)
        newdata[i] = data[i];
    delete[] data;
    data = newdata;
}

template<class T>
SeqList<T>::SeqList(T* a, int n) {
    if (n > 1e7) {
        cerr << "Memeory Limit Exceeded!" << endl;
        exit(1);
    }
    data = new T[n];
    for (int i = 0; i < n; i++) {
        data[i] = a[i];
    }
    size = n;
}

template<class T>
SeqList<T>::~SeqList() {
    delete[] data;
}

template<class T>
void SeqList<T>::Output() {
    for (int i = 0; i < size; i++) {
        cout << data[i] << "\n";
    }
}

template<class T>
T SeqList<T>::DeleteMin() {
    if (!size) {
        cerr << "Error: empty seqlist!" << endl;
        exit(1);
    }
    
    int min_index = 0;
    for (int i = 0; i < size; i++) {
        if (data[i] < data[min_index]) {
            min_index = i;
        }
    }
    
    T temp = data[min_index];
    
    if (size == 1) {
        size--;
    } else {
        data[min_index] = data[size - 1];
        size--;
    }
    
    return temp;
}

template<class T>
void SeqList<T>::DeleteAllX(T x) {
    for (int i = 0; i < size; i++) {
        if (data[i] == x) {
            for (int j = i + 1; j < size; j++) {
                data[j - 1] = data[j];
            }
            size--;
        }
    }
}

template<class T>
void SeqList<T>::DeleteRange(T left, T right) {
    if (left > right) {
        cerr << "Error: Wrong Range!";
        exit(1);
    }
    
    // find boundary of two points
    int pl = 0, pr = size - 1;
    while (data[pl] < left) pl++;
    while (data[pr] > right) pr--;
    
    for (int i = pr + 1, j = pl; i < size; i++, j++) {
        data[j] = data[i];
    }
    
    size -= pr - pl + 1;
}

template<class T>
void SeqList<T>::Unique() {
    // use stl to hash, we can also use bucket to hash if data is not big enough
    unordered_map<T, bool> hash;
    for (int i = 0; i < size; i++) {
        hash[data[i]] = true;
    }
    
    // hashhing logic looks like a stack, so it's reversed
    int idx = hash.size() - 1;
    for (auto& x: hash) {
        data[idx] = x.first;
        idx--;
    }
    
    size = hash.size();
}

template<class T>
void SeqList<T>::Insert(int pos, T x) {
    Renew();
    for (int i = size - 1; i >= pos; i--)
        data[i + 1] = data[i];
    data[pos] = x;
    size++;
}

template<class T>
void SeqList<T>::IncreaseInsert(T x) {
    int l = 0, r = size - 1;
    while (l < r) {
        int m = (l + r) >> 1;
        if (data[m] < x) l = m + 1;
        else r = m;
    }
    Insert(r, x);
}

template<class T>
void SeqList<T>::SortOnce() {
    int i = -1, j = size, x = data[0];
    while (i < j) {
        while (data[++i] < x);
        while (data[--j] > x);
        if (i < j) {
            swap(data[i], data[j]);
        }
    }
}

template<class T>
void SeqList<T>::Sort() {
    QuickSort(0, size - 1);
}

template<class T>
void SeqList<T>::QuickSort(int left, int right) {
    if (left == right) {
        return;
    }
    int i = left - 1, j = right + 1;
    T x = data[(i + j) >> 1];
    while (i < j) {
        while (data[++i] < x);
        while (data[--j] > x);
        if (i < j) {
            swap(data[i], data[j]);
        }
    }
    QuickSort(left, j);
    QuickSort(j + 1, right);
}

template<class T>
void SeqList<T>::Merge(SeqList<T>& obj) {
    int n = this->size, m = obj.size;
    T* res = new T[n + m];
    int i = 0, j = 0, k = 0;
    
    while (i < n && j < m) {
        if (data[i] < obj[j]) {
            res[k++] = data[i++];
        } else {
            res[k++] = obj[j++];
        }
    }
    
    while (i < n) { res[k++] = data[i++]; }
    while (j < m) { res[k++] = obj[j++]; }
    
    delete[] data;
    data = res;
    size = n + m;
}

template<class T>
bool SeqList<T>::find(T x) {
    for (int i = 0; i < size; i++) {
        if (data[i] == x) {
            return true;
        }
    }
    return false;
}

#endif //INC_2__DATASTRUCTURES_SEQLIST_H