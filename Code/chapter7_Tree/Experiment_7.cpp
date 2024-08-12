#include "./BinaryTree.h"
#include "./ChildSiblingTree.h"
#include "./HuffmanTree.h"

using namespace std;

class Experiment_7 {
public:
    /** @brief binary tree
     * @note build with pre(taged): ab#f##gh###
     *               a
     * 	         b       g
     *        #   f    h   #
     *          #  #  #  #
     */
    
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
        tree.prePrint();
        cout << "\n";
        tree.midPrint();
        cout << "\n";
        tree.postPrint();
        cout << "\n";
        tree.levelPrint();
        cout << "\n";
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
        tree.prePrint();
        cout << "\n";
        tree.swapChild();
        tree.prePrint();
        cout << "\n";
    }
    
    /** @brief child sibling tree
     * @note create child sibling tree with binary tree
     *               1
     *          2    3    6
     *        5  4      7 8 9
     */
    
    vector<pair<int, int>> edges = {{1, 2},
                                    {1, 3},
                                    {1, 6},
                                    {2, 5},
                                    {2, 4},
                                    {6, 7},
                                    {6, 8},
                                    {6, 9}};
    
    // 7.2(1) create child sibling tree with ordered pair set
    void testCreateWithOrderedPairSet() {
        ChildSiblingTree<int> tree(edges);
        tree.prePrint();
    }
    
    // 7.2(3) print pre and post order
    void testPrintChileSiblingTree() {
        ChildSiblingTree<int> tree(edges);
        tree.prePrint();
        tree.postPrint();
    }
    
    // 7.2(4) count degree of each node
    void testCountDegree() {
        ChildSiblingTree<int> tree(edges);
        tree.countDegree();
        tree.prePrint();
    }
    
    // 7.2(5) calculate the height of the tree
    void testTreeHeight() {
        ChildSiblingTree<int> tree(edges);
        cout << "tree_height: " << tree.height() << endl;
    }
    
    // 7.2(6) get path from root to leaf
    void testGetPathFromRootToLeaf() {
        ChildSiblingTree<int> tree(edges);
        auto paths = tree.getPathFromRootToLeaf();
        for (auto& path: paths) {
            for (auto& road: path) {
                cout << road << " ";
            }
            cout << endl;
        }
    }
    
    /** @brief Huffman Tree
     * @note aaaabcccccdd
     * 	  _
     * 	c   _
     * 	  _	  a
     * 	b   d
     * @note a: 11
     * @note b: 100
     * @note c: 0
     * @note d: 101
     */
    
    string info = "aaaabcccccdd";
    
    // 7.3(1,2) create HuffmanTree and encode
    void testBuildHuffmanTreeAndEncode() {
        HuffmanTree tree(info);
        string source = "abcd";
        auto [dict, secret] = tree.encode(source);
        for (auto [c, code]: dict) {
            cout << c << " " << code << "\n";
        }
        cout << secret << "\n";
    }
    
    // 7.3(1,3) create HuffmanTree and decode
    void testDecode() {
        HuffmanTree tree(info);
        string secret = "111000101";
        auto source = tree.decode(secret);
        cout << source << "\n";
    }
};