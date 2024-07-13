//
// Created by ���Ľ� on 2023-10-10.
//

#include "SeqList.h"
#include "LinkList.h"

using namespace std;

#ifndef CODE_TRAIL_2_H
#define CODE_TRAIL_2_H

class Experiment_2 {
//public:
//	// Tr 1.1 �˵����� SeqList
//	void TrSeqList() {
//		int arr[] = {4, 2, 1, 3, 8, 0, 123}, n = 7;
//		SeqList<int> seqList(arr, n);
//		int choice;
//
//		function<void()> DisplayMenu = []() {
//			cout << endl;
//			cout << "====================" << endl;
//			cout << "1. ��ӡ" << endl;
//			cout << "2. ɾ����Сֵ" << endl;
//			cout << "3. ɾ������ֵΪx��Ԫ��" << endl;
//			cout << "4. ɾ��ָ��ֵΪx��Ԫ��" << endl;
//			cout << "5. ɾ��ֵ��l��r֮�������Ԫ��" << endl;
//			cout << "6. ȥ��" << endl;
//			cout << "7. ����" << endl;
//			cout << "8. �������" << endl;
//			cout << "9. ����һ��" << endl;
//			cout << "0. �˳�" << endl;
//			cout << "���������ѡ��";
//		};
//
//		do {
//			DisplayMenu();
//			cin >> choice;
//			cout << "\n";
//
//			switch (choice) {
//				case 1:
//					cout << "��ӡ" << endl;
//					seqList.Output();
//					break;
//				case 2:
//					if (seqList.size > 0) {
//						int minVal = seqList.DeleteMin();
//						cout << "ɾ����Сֵ " << minVal << " ���" << endl;
//					} else {
//						cout << "��գ�����������" << endl;
//					}
//					break;
//				case 3:
//					int deleteX;
//					cout << "ɾ�����е�Ԫ��x";
//					cin >> deleteX;
//					seqList.DeleteAllX(deleteX);
//					cout << "ɾ�����" << endl;
//					break;
//				case 4:
//					int deleteValue;
//					cout << "ɾ��ָ��ֵΪx��Ԫ��";
//					cin >> deleteValue;
//					seqList.DeleteAllX(deleteValue);
//					cout << "ɾ�����" << endl;
//					break;
//				case 5:
//					int left, right;
//					cout << "ɾ��ֵ��l��r֮�������Ԫ��";
//					cout << "������l��" << endl;
//					cin >> left;
//					cout << "������r��" << endl;
//					cin >> right;
//					seqList.DeleteRange(left, right);
//					cout << "ɾ�����" << endl;
//					break;
//				case 6:
//					seqList.Unique();
//					cout << "ȥ�����" << endl;
//					break;
//				case 7:
//					int insertPos, insertValue;
//					cout << "����λ�ã�";
//					cin >> insertPos;
//					cout << "����ֵ��";
//					cin >> insertValue;
//					seqList.Insert(insertPos, insertValue);
//					cout << "�������" << endl;
//					break;
//				case 8:
//					int insertIncreasing;
//					cout << "�������";
//					cin >> insertIncreasing;
//					seqList.IncreaseInsert(insertIncreasing);
//					cout << "�������" << endl;
//					break;
//				case 9:
//					seqList.SortOnce();
//					cout << "����һ��" << endl;
//					break;
//				case 0:
//					cout << "�˳�." << endl;
//					break;
//				default:
//					cout << "δ֪���룬����������" << endl;
//			}
//		} while (choice != 0);
//	}
//
//
//	// Tr 1.1 ����
//	void TrQuickSort() {
//		int arr[] = {4, 2, 1, 3}, n = 4;
//		SeqList<int> a(arr, n);
//		a.Output();
//		a.QuickSort(0, n - 1);
//		a.Output();
//	}
//
//
//	// Tr 1.1 �鲢��������˳���
//	void TrMergeSeqList() {
//		int arr1[] = {1, 2, 3, 4}, n1 = 4;
//		int arr2[] = {0, 7, 10}, n2 = 3;
//		SeqList<int> a(arr1, n1), b(arr2, n2);
//		a.Output(), b.Output();
//		a.Merge(b);
//		a.Output();
//	}
//
//
//	// Tr 1.2 ˳���ʵ�֣���Ʒ����ϵͳ
//	void TrSeqManageSystem() {
//		struct item {
//			string code; // ��Ʒ���
//			string name; // ��Ʒ����
//			int price;   // ��Ʒ�۸�
//			int num;     // ��Ʒ����
//		};
//
//		// ��ȡ�ļ�
//		ifstream fin("../Homework/ʵ��2_T2.txt");
//		if (!fin) {
//			cout << "�ļ���ʧ��" << endl;
//			return;
//		} else {
//			cout << "�ļ��򿪳ɹ�" << endl;
//		}
//
//		// �洢����
//		int n;
//		fin >> n;
//		SeqList<item> a(n);
//		for (int i = 0; i < n; i++) {
//			fin >> a[i].code >> a[i].name >> a[i].price >> a[i].num;
//		}
//
//		// �˵�ѡ��
//		function<void()> displayMenu = []() {
//			cout << endl;
//			cout << "====================" << endl;
//			cout << "1. ��ӡ" << endl;
//			cout << "2. �޸Ŀ�� or ������¼" << endl;
//			cout << "3. ɾ��ָ�����ŵ���Ʒ" << endl;
//			cout << "4. ����Ʒ���ŶԿ����еļ�¼����" << endl;
//			cout << "0. ���沢�˳�" << endl;
//			cout << "���������ѡ��";
//		};
//		int choice;
//		while (true) {
//			displayMenu();
//			cin >> choice;
//			switch (choice) {
//				case 1: { // ��ӡ
//					for (int i = 0; i < n; i++) {
//						cout << a[i].code << " " << a[i].name << " " << a[i].price << " " << a[i].num << endl;
//					}
//					break;
//				}
//				case 2: { // �޸Ŀ�� or ������¼
//					string nowcode;
//					cout << "��������Ʒ��ţ�";
//					cin >> nowcode;
//					int j = 0;
//					for (; j < n; j++) {
//						if (a[j].code == nowcode) {
//							break;
//						}
//					}
//					if (j == n) {
//						// ������¼
//						a[n].code = nowcode;
//						cout << "��������Ʒ���ƣ�";
//						cin >> a[n].name;
//						cout << "��������Ʒ�۸�";
//						cin >> a[n].price;
//						cout << "��������Ʒ������";
//						cin >> a[n].num;
//						n++;
//					} else {
//						// �޸Ŀ��
//						cout << "��������Ʒ������";
//						cin >> a[j].num;
//					}
//					break;
//				}
//				case 3: { // ɾ��ָ�����ŵ���Ʒ
//					string nowcode;
//					cout << "��������Ʒ��ţ�";
//					cin >> nowcode;
//					int j = 0;
//					for (; j < n; j++) {
//						if (a[j].code == nowcode) {
//							break;
//						}
//					}
//					if (j == n) {
//						cout << "δ�ҵ�����Ʒ" << endl;
//					} else {
//						for (int k = j; k < n - 1; k++) {
//							a[k] = a[k + 1];
//						}
//						n--;
//					}
//					break;
//				}
//				case 4: { // ����Ʒ���ŶԿ����еļ�¼���򣬴������ַ��������ֵ�������
//					sort(a.data, a.data + n, [](item a, item b) {
//						return a.code < b.code;
//					});
//					break;
//				}
//				case 0: { // ���沢�˳�
//					ofstream fout("../Homework/ʵ��2_T2.txt");
//					fout << n << endl;
//					for (int i = 0; i < n; i++) {
//						fout << a[i].code << " " << a[i].name << " " << a[i].price << " " << a[i].num << endl;
//					}
//					fout.close();
//					return;
//				}
//			}
//		}
//	}
//
//
//	// Tr 1.3 �˵����� LinkList
//	void TrLinkList() {
//		int arr[] = {4, 2, 1, 3, 8, 0, 123}, n = 7;
//		LinkList<int> linkList(arr, n);
//		int choice;
//
//		function<void()> display = []() {
//			cout << endl;
//			cout << "====================" << endl;
//			cout << "1. ��ӡ" << endl;
//			cout << "2. ����" << endl;
//			cout << "3. ���򲢴�ӡ" << endl;
//			cout << "0. �˳�" << endl;
//			cout << "���������ѡ��";
//		};
//
//		do {
//			display();
//			cin >> choice;
//			cout << "\n";
//
//			switch (choice) {
//				case 1:
//					cout << "��ӡ" << endl;
//					linkList.Output();
//					break;
//				case 2: {
//					int insertPos, insertValue;
//					cout << "����λ�ã�";
//					cin >> insertPos;
//					cout << "����ֵ��";
//					cin >> insertValue;
////					linkList.Insert(insertPos, insertValue);
//					cout << "�������" << endl;
//					break;
//				}
//				case 3: { // ���򲢴�ӡ
//					cout << "�������" << endl;
////					linkList.SortAndOutput();
//					break;
//				}
//				case 0:
//					cout << "�˳�." << endl;
//					break;
//				default:
//					cout << "δ֪���룬����������" << endl;
//			}
//		} while (choice != 0);
//	}
//
//
//	// Tr 1.3 ԭ�����õ�����
//	void TrReverseLinkList() {
////		int arr[] = {4, 2, 1, 3, 8, 0, 123}, n = 7;
////		LinkList<int> linkList(arr, n);
////		cout << "ԭ����";
////		linkList.Output();
////
////		Node<int>* h = linkList.head;
////		function<Node<int>*(Node<int>*)> Reverse = [&](Node<int>* node) -> Node<int>* {
////			if (!node || !node->next) return node; // �ձ� or β���
////			Node<int>* tail = Reverse(node->next);
////			node->next->next = node;
////			node->next = nullptr;
////			return tail;
////		};
////		linkList.head = Reverse(linkList.head);
////
////		cout << "���ú�";
////		linkList.Output();
//	}
//
//
//	// Tr 1.3 �鲢������������
//	void TrMergeLinkList() {
//		int arr1[] = {1, 2, 3, 4}, n1 = 4;
//		int arr2[] = {0, 7, 10}, n2 = 3;
//		LinkList<int> a(arr1, n1), b(arr2, n2);
//		cout << "�鲢ǰ��\n";
//		a.Output(), b.Output();
//		a.Merge(b);
//		cout << "�鲢��";
//		a.Output();
//	}
//
//
//	// Tr 1.4 ������ʵ�֣�ѧ������ϵͳ
//	void TrLinkManageSystem() {
//		struct stu {
//			string id; // ѧ��
//			string name; // ����
//			string gender; // �Ա�
//			string major; // רҵ
//			string birth; // ��������
//		};
//
//		// ��ȡ�ļ�
//		ifstream fin("../Homework/ʵ��2_T4.txt");
//		if (!fin) {
//			cout << "�ļ���ʧ��" << endl;
//			return;
//		} else {
//			cout << "�ļ��򿪳ɹ�" << endl;
//		}
//
//		// �洢����
//		int n;
//		fin >> n;
//		stu arr[n];
//		for (int i = 0; i < n; i++) {
//			fin >> arr[i].id >> arr[i].name >> arr[i].gender >> arr[i].major >> arr[i].birth;
//		}
//		LinkList<stu> a(arr, n);
//
//		// �˵�ѡ��
//		function<void()> displayMenu = []() {
//			cout << endl;
//			cout << "====================" << endl;
//			cout << "1. ��ӡ" << endl;
//			cout << "2. ����һ��ѧ����Ϣ" << endl;
//			cout << "3. ɾ��һ��ѧ����Ϣ" << endl;
//			cout << "4. �޸�һ��ѧ����Ϣ" << endl;
//			cout << "0. ���沢�˳�" << endl;
//			cout << "���������ѡ��";
//		};
//
//		int choice;
//		while (true) {
//			displayMenu();
//			cin >> choice;
//			switch (choice) {
//				case 1: { // ��ӡ
//					Node<stu>* p = a.head;
//					while (p) {
//						cout << p->data.id << " " << p->data.name << " " << p->data.gender << " " << p->data.major << " "
//							 << p->data.birth << endl;
//						p = p->next;
//					}
//					break;
//				}
//				case 2: { // ����һ��ѧ����Ϣ
//					cout << "������ѧ����Ϣ��";
//					stu now;
//					cout << "ѧ�ţ�";
//					cin >> now.id;
//					cout << "������";
//					cin >> now.name;
//					cout << "�Ա�";
//					cin >> now.gender;
//					cout << "רҵ��";
//					cin >> now.major;
//					cout << "�������ڣ�";
//					cin >> now.birth;
////					a.Insert(n++, now);
//					cout << "�������" << endl;
//					break;
//				}
//				case 3: { // ɾ��һ��ѧ����Ϣ
//					cout << "������ѧ��ѧ�ţ�";
//					string nowid;
//					cin >> nowid;
//					Node<stu>* p = a.head, * pre = nullptr;
//					while (p) {
//						if (p->data.id == nowid) {
//							pre->next = p->next;
//							cout << "ɾ�����" << endl;
//							n--;
//							break;
//						}
//						pre = p;
//						p = p->next;
//					}
//					if (!p) {
//						cout << "δ�ҵ���ѧ��" << endl;
//					}
//					break;
//				}
//				case 4: { // �޸�һ��ѧ������Ϣ
//					cout << "������ѧ��ѧ�ţ�";
//					string nowid;
//					cin >> nowid;
//					Node<stu>* p = a.head;
//					while (p) {
//						if (p->data.id == nowid) {
//							cout << "������ѧ����Ϣ��";
//							stu now;
//							cout << "ѧ�ţ�";
//							cin >> now.id;
//							cout << "������";
//							cin >> now.name;
//							cout << "�Ա�";
//							cin >> now.gender;
//							cout << "רҵ��";
//							cin >> now.major;
//							cout << "�������ڣ�";
//							cin >> now.birth;
//							p->data = now;
//							cout << "�޸����" << endl;
//							break;
//						}
//						p = p->next;
//					}
//					if (!p) {
//						cout << "δ�ҵ���ѧ��" << endl;
//					}
//					break;
//				}
//				case 0: {
//					ofstream fout("../Homework/ʵ��2_T4.txt");
//					fout << n << endl;
//					Node<stu>* p = a.head;
//					while (p) {
//						fout << p->data.id << " " << p->data.name << " " << p->data.gender << " " << p->data.major << " "
//							 << p->data.birth << endl;
//						p = p->next;
//					}
//					fout.close();
//					return;
//				}
//			}
//		}
//	}
};

#endif //CODE_TRAIL_2_H