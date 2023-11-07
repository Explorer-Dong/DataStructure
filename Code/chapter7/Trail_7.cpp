//
// Created by 董文杰 on 2023-11-06.
//

#include "BTree.h"

using namespace std;

class Trail_7 {
public:
	// 7.1 用含有标记的先序遍历序列进行构造
	void CreateWithPreOfTag() {
		/**
		 * 				a
		 * 			b		g
		 * 		 #    f   a   #
		 * 		  	#  # # #
		 */

		string pre_with_tag = "ab#f##ga###";
		BTree<char> tree(pre_with_tag);
		tree.PreOutput();
	}

	// 用含有标记的后序遍历序列进行构造 TODO*

	// 7.1 用先序和中序进行构造 TODO
	void CreateWithPreAndMid() {

	}

	// 用后序和中序进行构造 TODO*

	// 7.2 析构 TODO
	void TestDelete() {

	}

	// 7.3 四种遍历：先、中、后、层 TODO
	void Output() {

	}

	// 中序非递归遍历 TODO*

	// 7.4 统计0分支，1分支，2分支的结点的个数 TODO
	void Count() {

	}

	// 7.5 计算二叉树的高度 TODO
	void Height() {

	}

	// 7.6 交换每个结点的左右孩子 TODO
	void Swap() {

	}

	// 7.7 输出根结点到每一个根结点的路径 TODO
	void PrintPath() {

	}
};