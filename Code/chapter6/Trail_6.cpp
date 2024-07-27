//
// Created by Wenjie Dong on 2023-10-30.
//

#include <iostream>
#include "GList.h"

using namespace std;

#ifdef INC_3__DATASTRUCTURES_GLIST_H
#define INC_3__DATASTRUCTURES_GLIST_H

class Trail_6 {
public:
	// �˵�ѡ����Թ����Ĺ��ܣ���ӡ��������ȡ����㳤��
	void ShowGList() {
		auto displayMenu = []() {
			cout << endl;
			cout << "====================" << endl;
			cout << "1. ��ӡ�����" << endl;
			cout << "2. ��ӡ�����ĳ���" << endl;
			cout << "3. ��ӡ���������" << endl;
			cout << "0. �˳�" << endl;
			cout << "���������ѡ��";
		};

		char s[] = "((a, (), b), g, a, f)";
		GList<char> g(s);

		int choice;
		while (true) {
			displayMenu();
			cin >> choice;
			cout << "\n";
			switch (choice) {
				case 1: {
					cout << "�����Ϊ��\n";
					g.Output();
					break;
				}
				case 2: {
					cout << "�����ĳ���Ϊ��\n";
					cout << g.Length();
					cout << "\n";
					break;
				}
				case 3: {
					cout << "���������Ϊ��\n";
					cout << g.Depth();
					cout << "\n";
					break;
				}
				case 0: {
					return;
				}
			}
		}
	}

	// �滻Ԫ�� ori Ϊ x
	void TrReplace() {
		char s[] = "((a, (), b), g, a, f)";
		GList<char>  g(s);
		g.Output();
		g.Replace('a', 'h');
		g.Output();
	}

	// ɾ��ָ��ֵΪ x ��Ԫ��
	void TrDelete() {
		char s[] = "((a, (), b), g, a, f)";
		GList<char>  g(s);
		cout << "ɾ��ǰ��";
		g.Output();
		cout << "ɾ�� a\n";
		g.Delete('a');
		cout << "ɾ����";
		g.Output();
	};
};

#endif // INC_3__DATASTRUCTURES_GLIST_H