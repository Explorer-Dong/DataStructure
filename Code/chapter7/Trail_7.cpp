//
// Created by Wenjie Dong on 2023-11-06.
//

#include "BTree.h"
#include "CSTree.h"
#include "HuffmanTree.h"

using namespace std;

class Trail_7 {
public:
	// -----------------------------ʵ��1--------------------------------


	// 7.1(1) �ú��б�ǵ�����������н��й���
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

	// �ú��б�ǵĺ���������н��й���
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

	// 7.1(1) �������������й���
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

	// �ú����������й���
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

	// 7.1(3) ���ֱ������ȡ��С��󡢲�
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

	// ����ǵݹ���� TODO*
	void MidOutputNonRecursive() {

	}

	// 7.1(4) ͳ��0��֧��1��֧��2��֧�Ľ��ĸ���
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

	// 7.1(5) ����������ĸ߶�
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

	// 7.1(6) ����ÿ���������Һ���
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

	// 7.1(7) �������㵽ÿһ��Ҷ�ӽ���·��
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


	// -----------------------------ʵ��2--------------------------------


	// 7.2(1) ����ż���Ϲ������Լ��������<ai, aj>���ڲ���ajʱ��ai�Ѿ����������ṹ��
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
	 * @note ��������ʵ����
	 * @note ��ֻ����������ͺ���������ֱ�Ϊ �� ������ ������Ӧ�ڶ��������Ǹ� �� �ҡ��� �� �ҡ���������Զ�������Ϊ�ң��ֵܣ������ظ��ݹ鵥Ԫ
	 */
	// 7.2(3) ������� & �������
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

	// 7.2(4) ����ÿһ�����Ķ�
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

	// 7.2(5) �������ĸ߶�
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

	// 7.2(6) �������ÿһ��Ҷ�ӽ���·��
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


	// -----------------------------ʵ��3--------------------------------

	/**
	 * @note aaaabcccccdd
	 * @note
	 * 	  _
	 * 	c	_
	 * 	  _	   a
	 * 	b	d
	 * @note a: 11
	 * @note b: 100
	 * @note c: 0
	 * @note d: 101
	 */

	// 7.3(1��2) �����ַ�������HuffmanTree�� & �������
	void BuildHuffmanTree() {
		string s = "aaaabcccccdd";
		HuffmanTree huff_tree(s);

		string source = "abcd";
		auto x = huff_tree.EnCode(source);
		cout << "����Ϊ��" << x << endl;
	}

	// 7.3(1��3) �����ַ�������HuffmanTree�� & �������
	void DeHuffmanCode() {
		string s = "aaaabcccccdd";
		HuffmanTree huff_tree(s);

		string secret = "000111000101";
		auto x = huff_tree.DeCode(secret);
		cout << "����Ϊ��" << x << endl;
	}
};