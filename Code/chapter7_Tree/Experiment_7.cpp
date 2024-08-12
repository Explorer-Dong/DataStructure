//
// Created by Wenjie Dong on 2023-11-06.
//

#include "./BinaryTree.h"
#include "./ChildSiblingTree.h"
#include "./HuffmanTree.h"

using namespace std;

/** build with pre(taged): ab#f##gh###
 *               a
 * 	         b       g
 *        #   f    h   #
 *          #  #  #  #
 */

class Experiment_7 {
public:
    // 7.1(1) create with pre(taged)
    void testCreateWithPreTaged() {
        string pre_with_tag = "ab#f##gh###";
        BinaryTree<char> tree(pre_with_tag, true);
        tree.prePrint();
    }
    
    // supplement: create with post(taged)
    void testCreateWithPostTaged() {
        string post_with_tag = "###fb##h#ga";
        BinaryTree<char> tree(post_with_tag, false);
        tree.prePrint();
    }
    
    // 7.1(2) create with pre and mid:
    void testCreateWithPreMid() {
        string pre = "abfgh";
        string mid = "bfahg";
        BinaryTree<char> tree(pre, mid, true);
        tree.prePrint();
    }
    
    // supplement: create with mid and post:
    void testCreateWithMidPost() {
        string mid = "bfahg";
        string post = "fbhga";
        BinaryTree<char> tree(mid, post, false);
        tree.prePrint();
    }
    
    // 7.1(3) print pre, mid, post, level
    void testPrint() {
        string s = "ab#f##gh###";
        BinaryTree<char> tree(s, true);
        tree.prePrint(); cout << "\n";
        tree.midPrint(); cout << "\n";
        tree.postPrint(); cout << "\n";
        tree.levelPrint(); cout << "\n";
    }
    
    // supplement: print pre without recursion TODO
    void testMidPrintUnRecur() {
    
    }
    
    // 7.1(4) count node with double branch, single branch, leaf
    void testCount() {
        string s = "ab#f##gh###";
        BinaryTree<char> tree(s, true);
        cout << tree.countLeafNode() << "\n";
    }
    
    // 7.1(5) calculate the height of each node
    void testHeight() {
        string s = "ab#f##gh###";
        BinaryTree<char> tree(s, true);
        cout << tree.hight() << "\n";
    }
    
    // 7.1(6) swap left and right child
    void testSwapChild() {
        string s = "ab#f##gh###";
        BinaryTree<char> tree(s, true);
        tree.prePrint(); cout << "\n";
        tree.swapChild();
        tree.prePrint(); cout << "\n";
    }
    
    // 7.2(1) ����ż���Ϲ������Լ��������<ai, aj>���ڲ���ajʱ��ai�Ѿ����������ṹ��
    void CreateWithOrderedPairSet() {
        /**
         * 				  1
         * 		 	 2    3    6
         *		   5  4	     7 8 9
         */
        vector<pair<int, int>> a = {
                {1, 2},
                {1, 3},
                {1, 6},
                {2, 5},
                {2, 4},
                {6, 7},
                {6, 8},
                {6, 9}
        };
        ChildSiblingTree<int> tree(a);
        tree.PreOutput();
    }
    
    /**
     * @note ��������ʵ����
     * @note ��ֻ����������ͺ���������ֱ�Ϊ �� ������ ������Ӧ�ڶ��������Ǹ� �� �ҡ��� �� �ҡ���������Զ�������Ϊ�ң��ֵܣ������ظ��ݹ鵥Ԫ
     */
    // 7.2(3) ������� & �������
    void PrePostOutput() {
        vector<pair<int, int>> a = {
                {1, 2},
                {1, 3},
                {1, 6},
                {2, 5},
                {2, 4},
                {6, 7},
                {6, 8},
                {6, 9}
        };
        ChildSiblingTree<int> tree(a);
        tree.PreOutput();
        tree.PostOutput();
    }
    
    // 7.2(4) ����ÿһ�����Ķ�
    void CountDegree() {
        vector<pair<int, int>> a = {
                {1, 2},
                {1, 3},
                {1, 6},
                {2, 5},
                {2, 4},
                {6, 7},
                {6, 8},
                {6, 9}
        };
        ChildSiblingTree<int> tree(a);
        
        tree.CountDegree();
        tree.PreOutput();
    }
    
    // 7.2(5) �������ĸ߶�
    void TreeHeight() {
        vector<pair<int, int>> a = {
                {1, 2},
                {1, 3},
                {1, 6},
                {2, 5},
                {2, 4},
                {6, 7},
                {6, 8},
                {6, 9}
        };
        
        ChildSiblingTree<int> tree(a);
        cout << "tree_height: " << tree.Height() << endl;
        cout << "tree_height: " << tree.Height_() << endl;
    }
    
    // 7.2(6) �������ÿһ��Ҷ�ӽ���·��
    void PathOfRoot2Leaf() {
        vector<pair<int, int>> a = {
                {1, 2},
                {1, 3},
                {1, 6},
                {2, 5},
                {2, 4},
                {4, 10},
                {6, 7},
                {6, 8},
                {6, 9}
        };
        ChildSiblingTree<int> tree(a);
        
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