//
// Created by 董文杰 on 2023-10-10.
//

#include "SeqList.h"
#include "LinkList.h"
#include "CircleList.h"

using namespace std;

class Homework_2 {
public:
	// T 1.1 删除最小值并且返回最小值
	void TestDeleteMin() {
		int arr1[] = {2, 4, 1, 5}, n1 = 4;
		SeqList<int> a(arr1, n1);

		a.Output();
		cout << a.DeleteMin() << endl;
		a.Output();

		int arr2[] = {}, n2 = 0;
		SeqList<int> b(arr2, n2);

		// 测试空表
//		b.Output();
//		b.DeleteMin();
//		b.Output();
	}


	// T 1.2 删除具有给定值x的所有元素
	void TestDeleteAllX() {
		int arr[] = {2, 4, 1, 2, 5, 2}, n = 6;
		SeqList<int> a(arr, n);

		a.Output();
		a.DeleteAllX(2);
		a.Output();
	}


	// T 1.3 删除其值在给定值s和t(要求s小于t)之间的所有元素
	void TestDeleteRange() {
		int arr[] = {1, 3, 4, 5, 7, 8, 10}, n = 7;
		SeqList<int> a(arr, n);

		a.Output();
		a.DeleteRange(3, 7);
		a.Output();
	}


	// T 1.4 去重
	void TestUnique() {
		int arr[] = {3, 2, 5, 4, 2, 3, 9}, n = 7;
		SeqList<int> a(arr, n);

		a.Output();
		a.Unique();
		a.Output();
	}


	// T 1.5 有序表的插入
	void TestInsert() {
		int arr[] = {2, 3, 5, 7, 10}, n = 5;
		SeqList<int> a(arr, n);

		a.Output();
		a.IncreaseInsert(30);
		a.Output();
	}


	// T 1.6 链表拆分
	void TestDecompose() {
		int arr[] = {1, 2, 3, 4}, n = 4;
		LinkList<int> a(arr, n);
		LinkList<int> odd, even;
		a.Split(odd, even);
		odd.Output();
		even.Output();
	}


	// T 1.7 链表拷贝
	void TestCopy() {
		int arr[] = {1, 2, 3, 4}, n = 4;
		LinkList<int> a(arr, n);
		LinkList<int> b(a);
		b.Output();
	}


	// T 1.8 排序并输出
	void TestSortAndOutput() {
		int arr[] = {3, 2, 1, 4}, n = 4;
		LinkList<int> a(arr, n);
		a.SortAndOutput();
	}


	// T 1.9 排序一趟
	void TestSortOnce() {
		int arr[] = {4, 2, 1, 9}, n = 4;
		SeqList<int> a(arr, n);
		// 2 1 3 4
		a.Output();
		a.SortOnce();
		a.Output();
	}


	// T 1.10 计算循环链表的结点个数
	void TestCircleList() {
		int arr[] = {4, 2, 1, 9}, n = 4;
		CircleList<int> a(arr, n);
		cout << a.CountNode();
	}
};