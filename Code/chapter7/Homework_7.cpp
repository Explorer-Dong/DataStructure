//
// Created by 董文杰 on 2023-11-06.
//

#include "bits/stdc++.h"
#include "BTree.h"

using namespace std;

/**
 * 				a
 * 			b		g
 * 		 #    f   a   #
 * 		  	#  # # #
 */

//string pre_with_tag = "ab#f##gh###";
//BTree<char> tree(pre_with_tag);

class Homework_7 {
public:
	// T7.5 计算双分支结点的个数
	int CountTwobranch(BTree<char>& tree) {
		function<void(BtNode<char>*, int&)> dfs = [&](BtNode<char>* now, int& res) -> void {
			if (!now) {
				return;
			}
			if (now->lchild && now->rchild) {
				res++;
			}
			dfs(now->lchild, res);
			dfs(now->rchild, res);
		};

		int res = 0;
		dfs(tree.root, res);
		return res;
	}

	// T7.6 计算每一个结点的左右子树高度之差
	vector<pair<string, int>> CalcHeightSub(BTree<char>& tree) {
		// 计算当前结点到叶子结点的最远距离
		function<int(BtNode<char>*)> Depth = [&](BtNode<char>* now) -> int {
			if (!now) {
				return 0;
			}
			return max(Depth(now->lchild), Depth(now->rchild)) + 1;
		};

		// 计算每一个结点的左右子树的高度差
		function<void(BtNode<char>*, vector<pair<string, int>>&)> dfs = [&](BtNode<char>* now, vector<pair<string, int>>& res) -> void {
			if (!now) {
				return;
			}
			res.push_back({to_string(now->data) + ":", abs(Depth(now->lchild) - Depth(now->rchild))});
			dfs(now->lchild, res);
			dfs(now->rchild, res);
		};

		vector<pair<string, int>> res;
		dfs(tree.root, res);
		return res;
	}

	// T7.7 计算第k(k>1)层上的叶子结点的个数
	int CountKLevel(BTree<char>& tree, int k) {
		function<void(BtNode<char>*, int, int&)> dfs = [&](BtNode<char>* now, int dep, int& res) -> void {
			if (!now) {
				return;
			}
			if (dep == k) {
				res++;
			}
			dfs(now->lchild, dep + 1, res);
			dfs(now->rchild, dep + 1, res);
		};

		int res = 0;
		dfs(tree.root, 0, res);
		return res;
	}

	// T7.8 返回根结点到每一个叶子结点的路径
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

	// T7.9 返回两个给定结点的最近公共祖先 LCA TODO
	void LeastCommonAncestor() {

	}

	// T7.10 返回根结点到指定结点的路径
	vector<char> PathOfRoot2X(BTree<char>& tree, char x) {
		vector<char> res, path;

		function<void(BtNode<char>*, vector<char>&)> dfs = [&](BtNode<char>* now, vector<char>& path) {
			if (!now) {
				return;
			}
			path.push_back(now->data);
			if (now->data == x) {
				path.pop_back();
				res = path;
			}
			dfs(now->lchild, path);
			dfs(now->rchild, path);
			path.pop_back();
		};

		dfs(tree.root, path);
		return res;
	}
};









