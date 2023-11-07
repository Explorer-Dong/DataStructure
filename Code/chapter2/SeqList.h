#include <bits/stdc++.h>

using namespace std;

#ifndef INC_2__DATASTRUCTURES_SEQLIST_H
#define INC_2__DATASTRUCTURES_SEQLIST_H

template<class T>
class SeqList {
private:
	void Renew();

public:
	T* data;
	int size;
	SeqList() : data(nullptr), size(0) {}
	SeqList(T a[], int n);
	SeqList(int n) : data(new T[n]), size(n) {}
	~SeqList();
	void Output();
	T DeleteMin(); // T1: 删除最小值并返回最小值
	void DeleteAllX(T x); // T2: 删除所有值为x的元素
	void DeleteElem(T x); // 根据值删除列表中的一个元素
	void DeleteRange(T left, T right); // T3: 删除值在range范围内的所有元素
	void Unique(); // T4: 去重
	void Insert(int pos, T x); // 按位插入
	void IncreaseInsert(T x); // T5: 增序序列插入元素（二分）
	void SortOnce(); // T9: 排序一次
	void QuickSort(int left, int right); // 快速排序
	void Merge(SeqList<T>& obj); // 实验1.1 合并两个有序表
	T& operator[] (int idx) { return data[idx]; }
};

template<class T>
void SeqList<T>::Renew() {
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
		return;
	}
	data = new T[n];
	for (int i = 0; i < n; i++)
		data[i] = a[i];
	size = n;
}

template<class T>
SeqList<T>::~SeqList() {
	delete[] data;
}

template<class T>
void SeqList<T>::Output() {
	for (int i = 0; i < size; i++)
		cout << data[i] << " \n"[i == size - 1];
}

template<class T>
T SeqList<T>::DeleteMin() {
	if (!size) {
		cerr << "Error: empty seqlist!" << endl;
		return 0;
	}

	int min_index = 0;
	for (int i = 0; i < size; i++)
		if (data[i] < data[min_index])
			min_index = i;

	T temp = data[min_index];

	if (size == 1) size--;
	else data[min_index] = data[size - 1], size--;

	return temp;
}

template<class T>
void SeqList<T>::DeleteAllX(T x) {
	for (int i = 0; i < size; i++)
		if (data[i] == x)
			DeleteElem(data[i]);
}

template<class T>
void SeqList<T>::DeleteElem(T x) {
	if (!size) {
		cerr << "Error: empty seqlist!" << endl;
		return;
	}

	int i = 0;
	for (; i < size; i++)
		if (data[i] == x)
			break;

	if (i == size) {
		cerr << "Error: No such element!" << endl;
		return;
	} else {
		for (int j = i + 1; j < size; j++)
			data[j - 1] = data[j];
	}

	size--;
}

template<class T>
void SeqList<T>::DeleteRange(T left, T right) {
	if (left > right) {
		cerr << "Error: Wrong Range!";
		return;
	}

	// 找到两个边界的指针
	int pl = 0, pr = size - 1;
	while (data[pl] < left) pl++;
	while (data[pr] > right) pr--;

	for (int i = pr + 1, j = pl; i < size; i++, j++)
		data[j] = data[i];

	size -= pr - pl + 1;
}

template<class T>
void SeqList<T>::Unique() {
	unordered_map<T, bool> has;
	for (int i = 0; i < size; i++)
		has[data[i]] = true;

	// 由于在哈希表中，元素的创造是一个类似于栈的结构，所以需要逆序存储
	int idx = has.size();
	for (auto& x: has)
		data[--idx] = x.first;
	size = has.size();
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
	int l = 0, r = size;
	while (l < r) {
		int m = (l + r) >> 1;
		if (data[m] < x) l = m + 1;
		else r = m;
	}
	Insert(r, x);
}

template<class T>
void SeqList<T>::SortOnce() {
	int i = -1, j = size, m = data[0];
	while (i < j) {
		while (data[++i] < m);
		while (data[--j] > m);
		if (i < j) swap(data[i], data[j]);
	}
}

template<class T>
void SeqList<T>::QuickSort(int left, int right) {
	if (left == right) {
		return;
	}
	int i = left - 1, j = right + 1, x = data[(i + j) >> 1];
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


/**
 * @note 1. 对于DT数据类型，delete和delete[]的没有区别
 * @note 2. 对于ADT数据类型，delete只能析构data[0]，delete[]可以析构data[0]到data[size - 1]
 * @note 3. 不要忘记修改size为n + m
 */

template<class T>
void SeqList<T>::Merge(SeqList<T>& obj) {
	int n = this->size, m = obj.size;
	T* res = new T[n + m];
	int i = 0, j = 0, k = 0;

	while (i < n && j < m)
		if (data[i] < obj[j]) res[k++] = data[i++];
		else res[k++] = obj[j++];

	while (i < n) res[k++] = data[i++];
	while (j < m) res[k++] = obj[j++];

	delete[] data;
	data = res;
	size = n + m;
}

#endif //INC_2__DATASTRUCTURES_SEQLIST_H
















