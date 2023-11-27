//
// Created by 董文杰 on 2023-11-06.
//

#include "BTree.h"
#include "CSTree.h"

using namespace std;

class Trail_7 {
public:
	// 7.1(1) 用含有标记的先序遍历序列进行构造
	void CreateWithPreOfTag() {
		/**
		 * 				a
		 * 			b		g
		 * 		 #    f   h   #
		 * 		  	#  # # #
		 */

		string pre_with_tag = "ab#f##gh###";
		BTree<char> tree(pre_with_tag, 1);
		tree.PreOutput();
	}


	// 用含有标记的后序遍历序列进行构造
	void CreateWithPost() {
		/**
		 * 				a
		 * 			b		g
		 * 		 #    f   h   #
		 * 		  	#  # # #
		 */

		string post_with_tag = "###fb##h#ga";
		BTree<char> tree(post_with_tag, 2);
		tree.PreOutput();
	}


	// 7.1(1) 用先序和中序进行构造
	void CreateWithPreAndMid() {
		/**
		 * 				a
		 * 			b		g
		 * 		 #    f   h   #
		 * 		  	#  # # #
		 */

		string pre = "abfgh";
		string mid = "bfahg";
		BTree<char> tree(pre, mid, 1);
		tree.MidOutput();
	}


	// 用后序和中序进行构造
	void CreateWithPostAndMid() {
		/**
		 * 				a
		 * 			b		g
		 * 		 #    f   h   #
		 * 		  	#  # # #
		 */

		string mid = "bfahg";
		string post = "fbhga";
		BTree<char> tree(mid, post, 2);
		tree.MidOutput();
	}


	// 7.1(3) 四种遍历：先、中、后、层
	void Output() {
		string pre_with_tag = "ab#f##gh###";
		BTree<char> tree(pre_with_tag, 1);
		cout << "Pre: ";
		tree.PreOutput();
		cout << "\n";
		cout << "Mid: ";
		tree.MidOutput();
		cout << "\n";
		cout << "Post: ";
		tree.PostOutput();
		cout << "\n";
		cout << "Level: ";
		tree.LevelOutput();
	}


	// 中序非递归遍历 TODO*
	void MidOutputNonRecursive() {

	}


	// 7.1(4) 统计0分支，1分支，2分支的结点的个数
	void Count() {
		string pre_with_tag = "ab#f##gh###";
		BTree<char> tree(pre_with_tag, 1);
		int cnt0 = 0, cnt1 = 0, cnt2 = 0;
		function<void(BtNode<char>*)> dfs = [&](BtNode<char>* now) {
			if (!now) {
				return;
			}
			if (!now->lchild && !now->rchild) {
				cnt0++;
			} else if (!now->lchild || !now->rchild) {
				cnt1++;
			} else {
				cnt2++;
			}
			dfs(now->lchild);
			dfs(now->rchild);
		};
		dfs(tree.root);
		cout << "cnt0: " << cnt0 << "\n";
		cout << "cnt1: " << cnt1 << "\n";
		cout << "cnt2: " << cnt2 << "\n";
	}


	// 7.1(5) 计算二叉树的高度
	void Height() {
		string pre_with_tag = "ab#f##gh###";
		BTree<char> tree(pre_with_tag, 1);
		function<int(BtNode<char>*)> Depth = [&](BtNode<char>* now) -> int {
			if (!now) {
				return 0;
			} else {
				return max(Depth(now->lchild), Depth(now->rchild)) + 1;
			}
		};
		cout << Depth(tree.root);
	}


	// 7.1(6) 交换每个结点的左右孩子
	void Swap() {
		string pre_with_tag = "ab#f##gh###";
		BTree<char> tree(pre_with_tag, 1);
		function<void(BtNode<char>*)> dfs = [&](BtNode<char>* now) -> void {
			if (!now) {
				return;
			}
			BtNode<char>* t = now->lchild;
			now->lchild = now->rchild;
			now->rchild = t;
			dfs(now->lchild);
			dfs(now->rchild);
		};
		dfs(tree.root);
		tree.PreOutput();
	}


	// 7.1(7) 输出根结点到每一个叶子结点的路径
	vector<vector<char>> PathOfRoot2Leaf(BTree<char>& tree) {
		function<void(BtNode<char>*, vector<vector<char>>&, vector<char>&)> dfs = [&](BtNode<char>* now, vector<vector<char>>& res, vector<char>& path) -> void {
			if (!now) {
				return;
			}
			path.push_back(now->data);
			if (!now->lchild && !now->rchild) {
				res.push_back(path);
			}
			dfs(now->lchild, res, path);
			dfs(now->rchild, res, path);
			path.pop_back();
		};

		vector<vector<char>> res;
		vector<char> path;
		dfs(tree.root, res, path);
		return res;
	}


	// 7.2(1) 用序偶集合构造对象，约定：对于<ai, aj>，在插入aj时，ai已经存在于树结构中
	void CreateWithOrderedPairSet() {
		/**
		 * 				  1
		 * 		 	 2    3    6
		 *		   5  4	     7 8 9
		 */
		vector<pair<int, int>> a = {
				{1, 2}, {1, 3}, {1, 6},
				{2, 5}, {2, 4},
				{6, 7}, {6, 8}, {6, 9}
		};
		CSTree<int> tree(a);
		tree.PreOutput();
	}


	/**
	 * @note 二叉链表实现树
	 * @note 树只有先序遍历和后序遍历，分别为 根 孩、孩 根，对应于二叉树就是根 左 右、左 根 右。其中右永远在最后，因为右（兄弟）属于重复递归单元
	 */
	// 7.2(3) 先序遍历 & 后序遍历
	void PrePostOutput() {
		vector<pair<int, int>> a = {
				{1, 2}, {1, 3}, {1, 6},
				{2, 5}, {2, 4},
				{6, 7}, {6, 8}, {6, 9}
		};
		CSTree<int> tree(a);
		tree.PreOutput();
		tree.PostOutput();
	}

	// 7.2(4) 计算每一个结点的度
	void CountDegree() {
		vector<pair<int, int>> a = {
				{1, 2}, {1, 3}, {1, 6},
				{2, 5}, {2, 4},
				{6, 7}, {6, 8}, {6, 9}
		};
		CSTree<int> tree(a);

		tree.CountDegree();
		tree.PreOutput();
	}

	// 7.2(5) 计算树的高度
	void TreeHeight() {
		vector<pair<int, int>> a = {
				{1, 2}, {1, 3}, {1, 6},
				{2, 5}, {2, 4},
				{6, 7}, {6, 8}, {6, 9}
		};

		CSTree<int> tree(a);
		cout << "tree_height: " << tree.Height() << endl;
		cout << "tree_height: " << tree.Height_() << endl;
	}

	// 7.2(6) 输出根到每一个叶子结点的路径
	void PathOfRoot2Leaf() {
		vector<pair<int, int>> a = {
				{1, 2}, {1, 3}, {1, 6},
				{2, 5}, {2, 4},
				{4, 10},
				{6, 7}, {6, 8}, {6, 9}
		};
		CSTree<int> tree(a);

		auto paths = tree.Path2Leaf();
		for (auto& path: paths) {
			for (auto& road: path) {
				cout << road << " ";
			}
			cout << endl;
		}
	}

	// 7.3(1)
};