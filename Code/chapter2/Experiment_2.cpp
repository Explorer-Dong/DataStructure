//
// Created by 董文杰 on 2023-10-10.
//

#include "SeqList.h"
#include "LinkList.h"
#include <iostream>
#include <fstream>

using namespace std;

struct item {
    string id, name;
    int price, cnt;
    bool operator< (const item& t) const {
        return this->id < t.id;
    }
    bool operator> (const item& t) const {
        return this->id > t.id;
    }
    bool operator== (const item& t) const {
        return this->id == t.id;
    }
    friend ostream& operator<< (ostream& os, const item& t) {
        os << t.id << " " << t.name << " " << t.price << " " << t.cnt;
        return os;
    }
};

struct stu {
    string id, name, gender, major, birth;
    bool operator== (const stu& t) const {
        return this->id == t.id;
    }
    friend ostream& operator<< (ostream& os, const stu& t) {
        os << t.id << " " << t.name << " " << t.gender << " " << t.major << " " << t.birth << endl;
        return os;
    }
};

#ifndef CODE_Experiment_2_H
#define CODE_Experiment_2_H

class Experiment_2 {
private:
    void displaySeqMenu() {
        cout << endl;
        cout << "====================" << endl;
        cout << "1. 打印" << endl;
        cout << "2. 删除最小值" << endl;
        cout << "3. 删除所有值为x的元素" << endl;
        cout << "4. 删除指定值为x的元素" << endl;
        cout << "5. 删除值在l到r之间的所有元素" << endl;
        cout << "6. 去重" << endl;
        cout << "7. 插入" << endl;
        cout << "8. 增序插入" << endl;
        cout << "9. 排序一轮" << endl;
        cout << "0. 退出" << endl;
        cout << "请输入你的选择：";
    }
    
    void displayItemMenu() {
        cout << endl;
        cout << "====================" << endl;
        cout << "1. 打印" << endl;
        cout << "2. 修改库存 or 新增记录" << endl;
        cout << "3. 删除指定代号的商品" << endl;
        cout << "4. 按商品代号对库存表中的记录排序" << endl;
        cout << "0. 保存并退出" << endl;
        cout << "请输入你的选择：";
    }
    
    void displayLinkMenu() {
        cout << endl;
        cout << "====================" << endl;
        cout << "1. 打印" << endl;
        cout << "2. 头插入" << endl;
        cout << "3. 排序并打印" << endl;
        cout << "0. 退出" << endl;
        cout << "请输入你的选择：";
    }
    
    void displayStuMenu() {
        cout << endl;
        cout << "====================" << endl;
        cout << "1. 打印" << endl;
        cout << "2. 增加一条学生信息" << endl;
        cout << "3. 删除一条学生信息" << endl;
        cout << "4. 修改一条学生信息" << endl;
        cout << "0. 保存并退出" << endl;
        cout << "请输入你的选择：";
    }

public:
    // Exp1.1 test Seqlist all functions
    void testSeqList() {
        int arr[] = {4, 2, 1, 3, 8, 0, 123}, n = 7;
        SeqList<int> seqList(arr, n);
        
        int choice;
        while (true) {
            displaySeqMenu();
            cin >> choice;
            cout << endl;
            
            switch (choice) {
                case 1: {
                    cout << "打印" << endl;
                    seqList.Output();
                    break;
                }
                case 2: {
                    int minVal = seqList.DeleteMin();
                    cout << "删除最小值 " << minVal << " 完毕" << endl;
                    break;
                }
                case 3: {
                    int deleteX;
                    cout << "删除所有的元素x";
                    cin >> deleteX;
                    seqList.DeleteAllX(deleteX);
                    cout << "删除完毕" << endl;
                    break;
                }
                case 4: {
                    int deleteValue;
                    cout << "删除指定值为x的元素";
                    cin >> deleteValue;
                    seqList.DeleteAllX(deleteValue);
                    cout << "删除完毕" << endl;
                    break;
                }
                case 5: {
                    int left, right;
                    cout << "删除值在 l 到 r 之间的所有元素";
                    cout << "请输入l：" << endl;
                    cin >> left;
                    cout << "请输入r：" << endl;
                    cin >> right;
                    seqList.DeleteRange(left, right);
                    cout << "删除完毕" << endl;
                    break;
                }
                case 6: {
                    seqList.Unique();
                    cout << "去重完毕" << endl;
                    break;
                }
                case 7: {
                    int insertPos, insertValue;
                    cout << "插入位置：";
                    cin >> insertPos;
                    cout << "插入值：";
                    cin >> insertValue;
                    seqList.Insert(insertPos, insertValue);
                    cout << "插入完毕" << endl;
                    break;
                }
                case 8: {
                    int insertIncreasing;
                    cout << "增序插入";
                    cin >> insertIncreasing;
                    seqList.IncreaseInsert(insertIncreasing);
                    cout << "插入完毕" << endl;
                    break;
                }
                case 9: {
                    seqList.SortOnce();
                    cout << "排序一轮" << endl;
                    break;
                }
                case 0: {
                    cout << "退出." << endl;
                    break;
                }
                default: {
                    cout << "未知输入，请重新输入" << endl;
                }
            }
        }
    }
    
    
    // Exp1.2 sort
    void testSort() {
        int arr[] = {4, 2, 1, 3}, n = 4;
        SeqList<int> a(arr, n);
        a.Output();
        a.Sort();
        a.Output();
    }
    
    
    // Exp 1.2 merge two ordered list
    void testMergeOrderedSeqList() {
        int arr1[] = {1, 2, 3, 4}, n1 = 4;
        int arr2[] = {0, 7, 10}, n2 = 3;
        SeqList<int> a(arr1, n1), b(arr2, n2);
        a.Output(), b.Output();
        a.Merge(b);
        a.Output();
    }
    
    
    // Exp2 item manage system with seqlist
    void testItemManageSystem() {
        // read data from txt file
        ifstream fin("HomeWork\\Exp2_T2.txt");
        if (!fin) {
            cout << "unsuccessful open file" << endl;
            exit(1);
        } else {
            cout << "successful open file" << endl;
        }
        
        // store data in cpu
        int n;
        fin >> n;
        SeqList<item> a(n);
        for (int i = 0; i < n; i++) {
            fin >> a[i].id >> a[i].name >> a[i].price >> a[i].cnt;
        }
        
        int choice;
        while (true) {
            displayItemMenu();
            cin >> choice;
            switch (choice) {
                case 1: {
                    a.Output();
                    break;
                }
                case 2: {
                    string nowid;
                    cout << "请输入商品编号：";
                    cin >> nowid;
                    if (!a.find({nowid, "", 0, 0})) {
                        // new item info
                        item now;
                        now.id = nowid;
                        cout << "请输入商品名称：";
                        cin >> now.name;
                        cout << "请输入商品价格：";
                        cin >> now.price;
                        cout << "请输入商品数量：";
                        cin >> now.cnt;
                        a.Insert(n++, now);
                    } else {
                        // modify cnt
                        int cnt;
                        cout << "请输入商品数量：";
                        cin >> cnt;
                        for (int i = 0; i < n; i++) {
                            if (a[i].id == nowid) {
                                a[i].cnt += cnt;
                                break;
                            }
                        }
                    }
                    break;
                }
                case 3: {
                    string nowid;
                    cout << "请输入商品编号：";
                    cin >> nowid;
                    for (int i = 0; i < n; i++) {
                        if (a[i].id == nowid) {
                            a.DeleteAllX({nowid, "", 0, 0});
                            n--;
                            break;
                        }
                    }
                    break;
                }
                case 4: {
                    a.Sort();
                    break;
                }
                case 0: {
                    ofstream fout("HomeWork\\Exp2_T2.txt");
                    fout << n << endl;
                    for (int i = 0; i < n; i++) {
                        fout << a[i].id << " " << a[i].name << " " << a[i].price << " " << a[i].cnt << endl;
                    }
                    fout.close();
                    return;
                }
            }
        }
    }


	// Exp3 test LinkList all functions
	void testLinkList() {
		int arr[] = {4, 2, 1, 3, 8, 0, 123}, n = 7;
		LinkList<int> linkList(arr, n);
  
		int choice;
        while (true) {
            displayLinkMenu();
            cin >> choice;
            cout << "\n";
            
            switch (choice) {
                case 1: {
                    cout << "打印" << endl;
                    linkList.Output();
                    break;
                }
                case 2: {
                    cout << "头插入" << endl;
                    int insertValue;
                    cin >> insertValue;
                    linkList.PushFront(insertValue);
                    cout << "插入完毕" << endl;
                    break;
                }
                case 3: {
                    cout << "排序完毕" << endl;
                    linkList.PrintInOrder();
                    break;
                }
                case 0:
                    cout << "退出." << endl;
                    return;
                default:
                    cout << "未知输入，请重新输入" << endl;
            }
        }
	}


	// Exp3.1 reverse list
	void testReverseLinkList() {
		int arr[] = {4, 2, 1, 3, 8, 0, 123}, n = 7;
		LinkList<int> ls(arr, n);
  
		cout << "原链表：";
		ls.Output();
        ls.Reverse();
		cout << "逆置后：";
		ls.Output();
	}


	// Exp3.2 merge two ordered linklist
	void testMergeLinkList() {
		int arr1[] = {1, 2, 3, 4}, n1 = 4;
		int arr2[] = {0, 7, 10}, n2 = 3;
		LinkList<int> a(arr1, n1), b(arr2, n2);
		cout << "归并前：\n";
		a.Output(), b.Output();
		a.Merge(b);
		cout << "归并后：";
		a.Output();
	}


	// Exp4 student manage system with linklist
	void testStudentManageSystem() {
		// read data from txt file
		ifstream fin("Homework\\Exp2_T4.txt");
		if (!fin) {
			cout << "unsuccessful open file" << endl;
			exit(1);
		} else {
			cout << "successful open file" << endl;
		}

		// store data in cpu
		int n;
		fin >> n;
		stu arr[n];
		for (int i = 0; i < n; i++) {
			fin >> arr[i].id >> arr[i].name >> arr[i].gender >> arr[i].major >> arr[i].birth;
		}
		LinkList<stu> ls(arr, n);

		int choice;
		while (true) {
            displayStuMenu();
			cin >> choice;
			switch (choice) {
				case 1: {
                    ls.Output();
					break;
				}
				case 2: {
					cout << "请输入学生信息：";
					stu now;
					cout << "学号：";
					cin >> now.id;
					cout << "姓名：";
					cin >> now.name;
					cout << "性别：";
					cin >> now.gender;
					cout << "专业：";
					cin >> now.major;
					cout << "出生日期：";
					cin >> now.birth;
                    ls.PushFront(now);
					cout << "增加完毕" << endl;
					break;
				}
				case 3: {
					cout << "请输入学生学号：";
					string nowid;
					cin >> nowid;
                    ls.Delete({nowid, "", "", "", ""});
					break;
				}
				case 4: {
                    cout << "请输入待修改信息的学生学号：";
                    string nowid;
                    cin >> nowid;
                    if (ls.Find({nowid, "", "", "", ""})) {
                        ls.Delete({nowid, "", "", "", ""});
                        cout << "请输入学生新信息：";
                        stu now;
                        now.id = nowid;
                        cout << "姓名：";
                        cin >> now.name;
                        cout << "性别：";
                        cin >> now.gender;
                        cout << "专业：";
                        cin >> now.major;
                        cout << "出生日期：";
                        cin >> now.birth;
                        ls.PushFront(now);
                    }
					break;
				}
				case 0: {
					ls.OutputToFile("Homework\\Exp2_T4.txt");
					return;
				}
			}
		}
	}
};

#endif //CODE_Experiment_2_H