//
// Created by 董文杰 on 2023-11-06.
//

#include "bits/stdc++.h"
#include "BTree.h"

using namespace std;

/**
 * 				a
 * 			b		g
 * 		 #    f   h   #
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

	// 计算当前结点到叶子结点的最远距离
	int Depth(BtNode<char>* now) {
		if (!now) {
			return 0;
		}
		return max(Depth(now->lchild), Depth(now->rchild)) + 1;
	};

	// T7.6 计算每一个结点的左右子树高度之差
	vector<pair<string, int>> CalcHeightSub(BTree<char>& tree) {
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

	// T7.9 返回两个给定结点的最近公共祖先 LCA
	char LeastCommonAncestor(BTree<char>& tree, char x, char y) {
		vector<char> a = PathOfRoot2X(tree, x);
		vector<char> b = PathOfRoot2X(tree, y);
		int i = 0, j = 0;
		int m = a.size(), n = b.size();
		while (i < m && j < n && a[i] == a[j]) {
			i++, j++;
		}

		if (i) {
			return a[i - 1];
		} else {
			return '#';
		}
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

	// T7.11 判断给定的二叉树是否是完全二叉树
	bool Judge(BTree<char>& tree) {
		// 计算深度 O(logn)
		auto level = [&](BtNode<char>* now) {
			int cnt = 0;
			while (now) {
				now = now->lchild;
				cnt++;
			}
			return cnt;
		};

		// 计算结点数 O(n)
		function<int(BtNode<char>*)> CntNode = [&](BtNode<char>* now) {
			if (!now) return 0;
			return 1 + CntNode(now->lchild) + CntNode(now->rchild);
		};

		// 判断
		function<bool(BtNode<char>*)> dfs = [&](BtNode<char>* now) {
			if (!now) return true;

			int l = level(now->lchild), r = level(now->rchild);

			if (l < r) {
				return false;
			} else if (l == r) {
				if (CntNode(now->lchild) == (1 << l) - 1) {
					return dfs(now->rchild);
				} else {
					return false;
				}
			} else if (l > r + 1) {
				return false;
			} else { // l == r + 1
				if (CntNode(now->rchild) == (1 << r) - 1) {
					return dfs(now->lchild);
				} else {
					return false;
				}
			}
		};

		return dfs(tree.root);
	}

	// T7.12 计算二叉树的同一层中结点的最大个数
	int CountWidth(BTree<char>& tree) {
		unordered_map<int, int> a;
		function<void(BtNode<char>*, int)> dfs = [&](BtNode<char>* now, int dep) {
			if (!now) return;
			a[dep]++;
			dfs(now->lchild, dep + 1);
			dfs(now->rchild, dep + 1);
		};

		dfs(tree.root, 1);
		int res = -1;
		for (auto& x: a) {
			res = max(res, x.second);
		}
		return res;
	}

	// T7.13 链接叶子结点
	BtNode<char>* LinkLeaf(BTree<char>& tree) {
		BtNode<char>* h = nullptr, * p = nullptr;

		function<void(BtNode<char>*)> dfs = [&](BtNode<char>* now) {
			if (!now) return;

			if (!now->lchild && !now->rchild) {
				if (!h) {
					h = now;
					p = now;
				} else {
					p->rchild = now;
					p = now;
				}
			}

			dfs(now->lchild);
			dfs(now->rchild);
		};

		// 尾处理
		if (p) p->rchild = nullptr;

		dfs(tree.root);
		return h;
	}
};
