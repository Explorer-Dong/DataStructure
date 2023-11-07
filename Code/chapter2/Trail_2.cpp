//
// Created by 董文杰 on 2023-10-10.
//

#include "SeqList.h"
#include "LinkList.h"

using namespace std;

#ifndef CODE_TRAIL_2_H
#define CODE_TRAIL_2_H

class Trail_2 {
public:
	// Tr 1.1 菜单测试 SeqList
	void TrSeqList() {
		int arr[] = {4, 2, 1, 3, 8, 0, 123}, n = 7;
		SeqList<int> seqList(arr, n);
		int choice;

		function<void()> DisplayMenu = []() {
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
		};

		do {
			DisplayMenu();
			cin >> choice;
			cout << "\n";

			switch (choice) {
				case 1:
					cout << "打印" << endl;
					seqList.Output();
					break;
				case 2:
					if (seqList.size > 0) {
						int minVal = seqList.DeleteMin();
						cout << "删除最小值 " << minVal << " 完毕" << endl;
					} else {
						cout << "表空，请重新输入" << endl;
					}
					break;
				case 3:
					int deleteX;
					cout << "删除所有的元素x";
					cin >> deleteX;
					seqList.DeleteAllX(deleteX);
					cout << "删除完毕" << endl;
					break;
				case 4:
					int deleteValue;
					cout << "删除指定值为x的元素";
					cin >> deleteValue;
					seqList.DeleteElem(deleteValue);
					cout << "删除完毕" << endl;
					break;
				case 5:
					int left, right;
					cout << "删除值在l到r之间的所有元素";
					cout << "请输入l：" << endl;
					cin >> left;
					cout << "请输入r：" << endl;
					cin >> right;
					seqList.DeleteRange(left, right);
					cout << "删除完毕" << endl;
					break;
				case 6:
					seqList.Unique();
					cout << "去重完毕" << endl;
					break;
				case 7:
					int insertPos, insertValue;
					cout << "插入位置：";
					cin >> insertPos;
					cout << "插入值：";
					cin >> insertValue;
					seqList.Insert(insertPos, insertValue);
					cout << "插入完毕" << endl;
					break;
				case 8:
					int insertIncreasing;
					cout << "增序插入";
					cin >> insertIncreasing;
					seqList.IncreaseInsert(insertIncreasing);
					cout << "插入完毕" << endl;
					break;
				case 9:
					seqList.SortOnce();
					cout << "排序一轮" << endl;
					break;
				case 0:
					cout << "退出." << endl;
					break;
				default:
					cout << "未知输入，请重新输入" << endl;
			}
		} while (choice != 0);
	}


	// Tr 1.1 排序
	void TrQuickSort() {
		int arr[] = {4, 2, 1, 3}, n = 4;
		SeqList<int> a(arr, n);
		a.Output();
		a.QuickSort(0, n - 1);
		a.Output();
	}


	// Tr 1.1 归并两个有序顺序表
	void TrMergeSeqList() {
		int arr1[] = {1, 2, 3, 4}, n1 = 4;
		int arr2[] = {0, 7, 10}, n2 = 3;
		SeqList<int> a(arr1, n1), b(arr2, n2);
		a.Output(), b.Output();
		a.Merge(b);
		a.Output();
	}


	// Tr 1.2 顺序表实现：商品管理系统
	void TrSeqManageSystem() {
		struct item {
			string code; // 商品编号
			string name; // 商品名称
			int price;   // 商品价格
			int num;     // 商品数量
		};

		// 读取文件
		ifstream fin("../Homework/实验2_T2.txt");
		if (!fin) {
			cout << "文件打开失败" << endl;
			return;
		} else {
			cout << "文件打开成功" << endl;
		}

		// 存储数据
		int n;
		fin >> n;
		SeqList<item> a(n);
		for (int i = 0; i < n; i++) {
			fin >> a[i].code >> a[i].name >> a[i].price >> a[i].num;
		}

		// 菜单选择
		function<void()> displayMenu = []() {
			cout << endl;
			cout << "====================" << endl;
			cout << "1. 打印" << endl;
			cout << "2. 修改库存 or 新增记录" << endl;
			cout << "3. 删除指定代号的商品" << endl;
			cout << "4. 按商品代号对库存表中的记录排序" << endl;
			cout << "0. 保存并退出" << endl;
			cout << "请输入你的选择：";
		};
		int choice;
		while (true) {
			displayMenu();
			cin >> choice;
			switch (choice) {
				case 1: { // 打印
					for (int i = 0; i < n; i++) {
						cout << a[i].code << " " << a[i].name << " " << a[i].price << " " << a[i].num << endl;
					}
					break;
				}
				case 2: { // 修改库存 or 新增记录
					string nowcode;
					cout << "请输入商品编号：";
					cin >> nowcode;
					int j = 0;
					for (; j < n; j++) {
						if (a[j].code == nowcode) {
							break;
						}
					}
					if (j == n) {
						// 新增记录
						a[n].code = nowcode;
						cout << "请输入商品名称：";
						cin >> a[n].name;
						cout << "请输入商品价格：";
						cin >> a[n].price;
						cout << "请输入商品数量：";
						cin >> a[n].num;
						n++;
					} else {
						// 修改库存
						cout << "请输入商品数量：";
						cin >> a[j].num;
					}
					break;
				}
				case 3: { // 删除指定代号的商品
					string nowcode;
					cout << "请输入商品编号：";
					cin >> nowcode;
					int j = 0;
					for (; j < n; j++) {
						if (a[j].code == nowcode) {
							break;
						}
					}
					if (j == n) {
						cout << "未找到该商品" << endl;
					} else {
						for (int k = j; k < n - 1; k++) {
							a[k] = a[k + 1];
						}
						n--;
					}
					break;
				}
				case 4: { // 按商品代号对库存表中的记录排序，代号是字符串，按字典序排序
					sort(a.data, a.data + n, [](item a, item b) {
						return a.code < b.code;
					});
					break;
				}
				case 0: { // 保存并退出
					ofstream fout("../Homework/实验2_T2.txt");
					fout << n << endl;
					for (int i = 0; i < n; i++) {
						fout << a[i].code << " " << a[i].name << " " << a[i].price << " " << a[i].num << endl;
					}
					fout.close();
					return;
				}
			}
		}
	}


	// Tr 1.3 菜单测试 LinkList
	void TrLinkList() {
		int arr[] = {4, 2, 1, 3, 8, 0, 123}, n = 7;
		LinkList<int> linkList(arr, n);
		int choice;

		function<void()> display = []() {
			cout << endl;
			cout << "====================" << endl;
			cout << "1. 打印" << endl;
			cout << "2. 插入" << endl;
			cout << "3. 排序并打印" << endl;
			cout << "0. 退出" << endl;
			cout << "请输入你的选择：";
		};

		do {
			display();
			cin >> choice;
			cout << "\n";

			switch (choice) {
				case 1:
					cout << "打印" << endl;
					linkList.Output();
					break;
				case 2: {
					int insertPos, insertValue;
					cout << "插入位置：";
					cin >> insertPos;
					cout << "插入值：";
					cin >> insertValue;
					linkList.Insert(insertPos, insertValue);
					cout << "插入完毕" << endl;
					break;
				}
				case 3: { // 排序并打印
					cout << "排序完毕" << endl;
					linkList.SortAndOutput();
					break;
				}
				case 0:
					cout << "退出." << endl;
					break;
				default:
					cout << "未知输入，请重新输入" << endl;
			}
		} while (choice != 0);
	}


	// Tr 1.3 原地逆置单链表
	void TrReverseLinkList() {
		int arr[] = {4, 2, 1, 3, 8, 0, 123}, n = 7;
		LinkList<int> linkList(arr, n);
		cout << "原链表：";
		linkList.Output();

		Node<int>* h = linkList.head;
		function<Node<int>*(Node<int>*)> Reverse = [&](Node<int>* node) -> Node<int>* {
			if (!node || !node->next) return node; // 空表 or 尾结点
			Node<int>* tail = Reverse(node->next);
			node->next->next = node;
			node->next = nullptr;
			return tail;
		};
		linkList.head = Reverse(linkList.head);

		cout << "逆置后：";
		linkList.Output();
	}


	// Tr 1.3 归并两个有序单链表
	void TrMergeLinkList() {
		int arr1[] = {1, 2, 3, 4}, n1 = 4;
		int arr2[] = {0, 7, 10}, n2 = 3;
		LinkList<int> a(arr1, n1), b(arr2, n2);
		cout << "归并前：\n";
		a.Output(), b.Output();
		a.Merge(b);
		cout << "归并后：";
		a.Output();
	}


	// Tr 1.4 单链表实现：学籍管理系统
	void TrLinkManageSystem() {
		struct stu {
			string id; // 学号
			string name; // 姓名
			string gender; // 性别
			string major; // 专业
			string birth; // 出生日期
		};

		// 读取文件
		ifstream fin("../Homework/实验2_T4.txt");
		if (!fin) {
			cout << "文件打开失败" << endl;
			return;
		} else {
			cout << "文件打开成功" << endl;
		}

		// 存储数据
		int n;
		fin >> n;
		stu arr[n];
		for (int i = 0; i < n; i++) {
			fin >> arr[i].id >> arr[i].name >> arr[i].gender >> arr[i].major >> arr[i].birth;
		}
		LinkList<stu> a(arr, n);

		// 菜单选择
		function<void()> displayMenu = []() {
			cout << endl;
			cout << "====================" << endl;
			cout << "1. 打印" << endl;
			cout << "2. 增加一条学生信息" << endl;
			cout << "3. 删除一条学生信息" << endl;
			cout << "4. 修改一条学生信息" << endl;
			cout << "0. 保存并退出" << endl;
			cout << "请输入你的选择：";
		};

		int choice;
		while (true) {
			displayMenu();
			cin >> choice;
			switch (choice) {
				case 1: { // 打印
					Node<stu>* p = a.head;
					while (p) {
						cout << p->data.id << " " << p->data.name << " " << p->data.gender << " " << p->data.major << " "
							 << p->data.birth << endl;
						p = p->next;
					}
					break;
				}
				case 2: { // 增加一条学生信息
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
					a.Insert(n++, now);
					cout << "增加完毕" << endl;
					break;
				}
				case 3: { // 删除一条学生信息
					cout << "请输入学生学号：";
					string nowid;
					cin >> nowid;
					Node<stu>* p = a.head, * pre = nullptr;
					while (p) {
						if (p->data.id == nowid) {
							pre->next = p->next;
							cout << "删除完毕" << endl;
							n--;
							break;
						}
						pre = p;
						p = p->next;
					}
					if (!p) {
						cout << "未找到该学生" << endl;
					}
					break;
				}
				case 4: { // 修改一个学生的信息
					cout << "请输入学生学号：";
					string nowid;
					cin >> nowid;
					Node<stu>* p = a.head;
					while (p) {
						if (p->data.id == nowid) {
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
							p->data = now;
							cout << "修改完毕" << endl;
							break;
						}
						p = p->next;
					}
					if (!p) {
						cout << "未找到该学生" << endl;
					}
					break;
				}
				case 0: {
					ofstream fout("../Homework/实验2_T4.txt");
					fout << n << endl;
					Node<stu>* p = a.head;
					while (p) {
						fout << p->data.id << " " << p->data.name << " " << p->data.gender << " " << p->data.major << " "
							 << p->data.birth << endl;
						p = p->next;
					}
					fout.close();
					return;
				}
			}
		}
	}
};

#endif //CODE_TRAIL_2_H