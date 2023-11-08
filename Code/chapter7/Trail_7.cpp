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
		 * 		 #    f   h   #
		 * 		  	#  # # #
		 */

		string pre_with_tag = "ab#f##gh###";
		BTree<char> tree(pre_with_tag);
		tree.PreOutput();
	}


	// 用含有标记的后序遍历序列进行构造 TODO*
	void CreateWithPost() {

	}


	// 7.1 用先序和中序进行构造 TODO
	void CreateWithPreAndMid() {

	}


	// 用后序和中序进行构造 TODO*
	void CreateWithPostAndMid() {

	}


	// 7.2 析构 TODO
	void TestDelete() {

	}


	// 7.3 四种遍历：先、中、后、层
	void Output() {
		string pre_with_tag = "ab#f##gh###";
		BTree<char> tree(pre_with_tag);
		tree.PreOutput();
		cout << "\n";
		tree.MidOutput();
		cout << "\n";
		tree.PostOutput();
		cout << "\n";
		tree.LevelOutput();
	}


	// 中序非递归遍历 TODO*
	void MidOutputNonRecursive() {

	}


	// 7.4 统计0分支，1分支，2分支的结点的个数
	void Count() {
		string pre_with_tag = "ab#f##gh###";
		BTree<char> tree(pre_with_tag);
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


	// 7.5 计算二叉树的高度
	void Height() {
		string pre_with_tag = "ab#f##gh###";
		BTree<char> tree(pre_with_tag);
		function<int(BtNode<char>*)> Depth = [&](BtNode<char>* now) -> int {
			if (!now) {
				return 0;
			} else {
				return max(Depth(now->lchild), Depth(now->rchild)) + 1;
			}
		};
		cout << Depth(tree.root);
	}


	// 7.6 交换每个结点的左右孩子
	void Swap() {
		string pre_with_tag = "ab#f##gh###";
		BTree<char> tree(pre_with_tag);
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


	// 7.7 输出根结点到每一个叶子结点的路径
	vector<vector<char>> PathOfRoot2Leaf(BTree<char>& tree) {
		function<void(BtNode<char>*, vector<vector<char>>&, vector<char>&)> dfs = [&](BtNode<char>* now, vector<vector<char>>& res, vector<char>& path) ->void {
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
};