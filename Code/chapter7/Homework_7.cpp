//
// Created by Wenjie Dong on 2023-11-06.
//

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
        cout << tree.countSingleBranchNode() << "\n";
    }
    
    // T7.7 count kth level node
    void testCountKthLevelNode() {
    
    }
    
    // T7.8 get path from root to leaf
    void testGetPathFromRootToLeaf() {
    
    }
    
    // T7.9 get lowest common acestor
    void testGetLowestCommonAcestor() {
    
    }
    
    // T7.10 get path from root to node
    void testGetPathFromRootToNode() {
    
    }
    
    // T7.11 judge whether the binary tree is a complete binary tree
    void testIsCompleteBinaryTree() {
    
    }
    
    // T7.12 get the width of the binary tree
    void testGetWidth() {
    
    }
    
    // T7.13 link the leaf node
    void testLinkLeaf() {
    
    }
};