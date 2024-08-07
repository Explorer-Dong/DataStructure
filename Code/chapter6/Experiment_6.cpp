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
	// 菜单选择测试广义表的功能：打印、计算深度、计算长度
	void ShowGList() {
		auto displayMenu = []() {
			cout << endl;
			cout << "====================" << endl;
			cout << "1. 打印广义表" << endl;
			cout << "2. 打印广义表的长度" << endl;
			cout << "3. 打印广义表的深度" << endl;
			cout << "0. 退出" << endl;
			cout << "请输入你的选择：";
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
					cout << "广义表为：\n";
					g.Output();
					break;
				}
				case 2: {
					cout << "广义表的长度为：\n";
					cout << g.Length();
					cout << "\n";
					break;
				}
				case 3: {
					cout << "广义表的深度为：\n";
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

	// 替换元素 ori 为 x
	void TrReplace() {
		char s[] = "((a, (), b), g, a, f)";
		GList<char>  g(s);
		g.Output();
		g.Replace('a', 'h');
		g.Output();
	}

	// 删除指定值为 x 的元素
	void TrDelete() {
		char s[] = "((a, (), b), g, a, f)";
		GList<char>  g(s);
		cout << "删除前：";
		g.Output();
		cout << "删除 a\n";
		g.Delete('a');
		cout << "删除后：";
		g.Output();
	};
};

#endif // INC_3__DATASTRUCTURES_GLIST_H