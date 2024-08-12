//
// Created by Wenjie Dong on 2023-10-10.
//

#include "SeqList.h"
#include "LinkList.h"
#include "CircleList.h"

using namespace std;

class Homework_2 {
public:
    // T1.1 delete and return min
    void testDeleteMin() {
        // correct demo
        int arr1[] = {2, 4, 1, 5}, n1 = 4;
        SeqList<int> a(arr1, n1);
        a.Output();
        cout << a.DeleteMin() << endl;
        a.Output();
        
        // abnormal demo
        int arr2[] = {}, n2 = 0;
        SeqList<int> b(arr2, n2);
        b.Output();
        b.DeleteMin();
        b.Output();
    }
    
    
    // T1.2 delete all elements equal to x
    void testDeleteAllX() {
        int arr[] = {2, 4, 1, 2, 5, 2}, n = 6;
        SeqList<int> a(arr, n);
        a.Output();
        a.DeleteAllX(2);
        a.Output();
    }
    
    
    // T1.3 delete ordered list's all elements range from s to t
    void testDeleteRange() {
        int arr[] = {1, 3, 4, 5, 7, 8, 10}, n = 7;
        SeqList<int> a(arr, n);
        a.Output();
        a.DeleteRange(3, 7);
        a.Output();
    }
    
    
    // T1.4 unique
    void testUnique() {
        int arr[] = {3, 2, 5, 4, 2, 3, 9}, n = 7;
        SeqList<int> a(arr, n);
        a.Output();
        a.Unique();
        a.Output();
    }
    
    
    // T1.5 insert to ordered list
    void testInsert() {
        int arr[] = {2, 3, 5, 7, 10}, n = 5;
        SeqList<int> a(arr, n);
        a.Output();
        a.IncreaseInsert(-1);
        a.Output();
    }
    
    
    // T1.6 split into odd and even
    void testSplit() {
        int arr[] = {1, 2, 3, 4}, n = 4;
        LinkList<int> ls(arr, n);
        LinkList<int> odd, even;
        ls.Split(odd, even);
        odd.Output();
        even.Output();
    }
    
    
    // T1.7 copy list
    void testCopy() {
        int arr[] = {1, 2, 3, 4}, n = 4;
        LinkList<int> a(arr, n);
        LinkList<int> b(a);
        b.Output();
    }
    
    
    // T1.8 print in order
    void testPrintInOrder() {
        int arr[] = {3, 2, 1, 4}, n = 4;
        LinkList<int> a(arr, n);
        a.PrintInOrder();
    }
    
    
    // T1.9 sort once
    void testSortOnce() {
        int arr[] = {4, 2, 1, 9}, n = 4;
        SeqList<int> a(arr, n);
        a.Output();
        a.SortOnce();
        a.Output();
    }
    
    
    // T1.10 count node of cicle list
    void testCircleListNodeCount() {
        CircleList<int> a;
        a.PushBack(2), a.PushBack(2), a.PushBack(2), a.PushBack(2);
        a.PopFront();
        cout << a.CountNode();
    }
};