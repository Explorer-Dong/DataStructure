#include <iostream>
#include <tuple>
#include <vector>
#include "./MGraph.h"
#include "./ALGraph.h"

using namespace std;

class Homework_8 {
public:
    // T1 dfs for graph - adjacency list
    void testDFS() {
        vector<int> vexs = {0, 1, 2, 3, 4};
        vector<pair<int, int>> edges = {{2, 3},
                                        {1, 2},
                                        {3, 4},
                                        {1, 4},
                                        {1, 3}};
        ALGraph<int> G(undigraph, vexs, edges);
        G.dfs();
    }
    
    // T2 bfs to find path from u to v - adjacency list
    void testFindPath() {
        vector<int> vexs = {0, 1, 2, 3, 4};
        vector<pair<int, int>> edges = {{2, 3},
                                        {1, 2},
                                        {3, 4},
                                        {1, 4},
                                        {1, 3}};
        ALGraph<int> G(digraph, vexs, edges);
        int a = 2, b = 4;
        cout << G.findPathFromA2B(a, b) << endl;
    }
    
    // T3 find path from u to v with length k - adjacency list
    void testFindPathLengthK() {
        vector<int> vexs = {0, 1, 2, 3, 4, 5, 6, 7};
        vector<pair<int, int>> edges = {{1, 2},
                                        {1, 6},
                                        {2, 3},
                                        {2, 4},
                                        {2, 5},
                                        {3, 4},
                                        {3, 7},
                                        {6, 7}};
        ALGraph<int> G(undigraph, vexs, edges);
        int a = 7, b = 2, k = 3;
        auto paths = G.findPathFromA2BLengthK(a, b, k);
        for (auto path: paths) {
            for (int i = 0; i < path.size(); i++) {
                cout << path[i];
                if (i == path.size() - 1) {
                    cout << "\n";
                } else {
                    cout << " -> ";
                }
            }
        }
    }
    
    // T4 find loop in digraph - adjacency matrix
    void testFindDigraphLoop() {
        vector<int> vexs = {0, 1, 2, 3, 4};
        vector<pair<int, int>> edges = {{0, 1},
                                        {1, 2},
                                        {2, 3},
                                        {2, 4},
                                        {4, 1},
                                        {3, 0}};
        MGraph<int> G(digraph, vexs, edges);
        auto loop = G.findDigraphLoop();
        for (auto& x: loop) {
            cout << x;
            if (x == loop.back()) {
                cout << "\n";
            } else {
                cout << " -> ";
            }
        }
    }
    
    // T5 find loop in undigraph - adjacency matrix
    void testFindUndigraphLoop() {
        vector<int> vexs = {0, 1, 2, 3, 4, 5};
        vector<pair<int, int>> edges = {{0, 2},
                                        {1, 2},
                                        {1, 3},
                                        {2, 4},
                                        {3, 5},
                                        {4, 5}};
        MGraph<int> G(undigraph, vexs, edges);
        auto loop = G.findUndigraphLoop();
        for (auto& x: loop) {
            cout << x;
            if (x == loop.back()) {
                cout << "\n";
            } else {
                cout << " -> ";
            }
        }
    }
    
    // T6 prim & kruskal
    void MST() {
        vector<int> vexs = {1, 2, 3, 4, 5, 6, 7, 8};
        vector<tuple<int, int, int>> edges = {
                {1, 2, 2},
                {1, 3, 3},
                {2, 4, 2},
                {3, 4, 1},
                {4, 5, 2},
                {4, 6, 4},
                {5, 7, 5},
                {5, 6, 1},
                {6, 7, 2},
                {6, 8, 1},
                {7, 8, 1}
        };
        MGraph<int> G(undinetwork, vexs, edges);
        int length = G.Prim(1);
        cout << length << "\n";
        
        auto res = G.Kruskal();
        for (auto& x: res) {
            cout << get<0>(x) << " --> " << get<1>(x) << " weight: " << get<2>(x) << "\n";
        }
    }
};