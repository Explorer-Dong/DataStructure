#include <iostream>
#include "./BinaryTree.h"

using namespace std;

/** build with pre(taged): ab#f##gh###
 *               a
 * 	         b       g
 *        #   f    h   #
 *          #  #  #  #
 */

class Homework_7 {
public:
    // T7.5 count double branch node
    void testCountDoubleBranchNode() {
        string s = "ab#f##gh###";
        BinaryTree<char> tree(s, true);
        cout << tree.countDoubleBranchNode() << "\n";
    }
    
    // T7.6 calculate the height sub of each node
    void testCalcHightSub() {
        string s = "ab#f##gh###";
        BinaryTree<char> tree(s, true);
        auto v = tree.calcHightSub();
        for (auto [val, sub]: v) {
            cout << val << " : " << sub << "\n";
        }
    }
    
    // T7.7 count kth level node
    void testCountKthLevelNode() {
        string s = "ab#f##gh###";
        BinaryTree<char> tree(s, true);
        int cnt = tree.countKthLevelNode(3);
        cout << cnt << "\n";
    }
    
    // T7.8 get path from root to leaf
    void testGetPathFromRootToLeaf() {
        string s = "ab#f##gh###";
        BinaryTree<char> tree(s, true);
        auto paths = tree.getPathFromRootToLeaf();
        for (auto path: paths) {
            for (int i = 0; i < path.size(); i++) {
                cout << path[i];
                if (i != path.size() - 1) {
                    cout << " -> ";
                } else {
                    cout << "\n";
                }
            }
        }
    }
    
    // T7.9 get lowest common acestor
    void testGetLowestCommonAcestor() {
        string s = "ab#f##gh###";
        BinaryTree<char> tree(s, true);
        cout << tree.getLowestCommonAncestor('f', 'h');
    }
    
    // T7.10 get path from root to node
    void testGetPathFromRootToNode() {
        string s = "ab#f##gh###";
        BinaryTree<char> tree(s, true);
        auto path = tree.getPathFromRootToNode('g');
        for (int i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i != path.size() - 1) {
                cout << " -> ";
            } else {
                cout << "\n";
            }
        }
    }
    
    // T7.11 judge whether the binary tree is a complete binary tree
    void testIsCompleteBinaryTree() {
        string s = "ab#f##gh###";
        BinaryTree<char> tree(s, true);
        cout << tree.isCompleteBinaryTree() << "\n";
    }
    
    // T7.12 get the width of the binary tree
    void testGetWidth() {
        string s = "ab#f##gh###";
        BinaryTree<char> tree(s, true);
        cout << tree.width() << "\n";
    }
    
    // T7.13 link the leaf node
    void testLinkLeaf() {
        string s = "ab#f##gh###";
        BinaryTree<char> tree(s, true);
        auto head = tree.linkLeaf();
        while (head) {
            cout << head->data << " ";
            head = head->rchild;
        }
    }
};