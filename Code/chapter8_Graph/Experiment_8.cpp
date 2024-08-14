#include <iostream>
#include <vector>
#include "./MGraph.h"
#include "./ALGraph.h"

using namespace std;

class Experiment_8 {
public:
    // 8.1 (1) build undirected graph based on adjacency matrix
    void testMbuild() {
        vector<int> vexs = {0, 1, 2, 3, 4, 5, 6, 7, 8};
        vector<pair<int, int>> edges = {{1, 2},
                                        {1, 3},
                                        {0, 4},
                                        {3, 5},
                                        {3, 6},
                                        {3, 8},
                                        {5, 6},
                                        {4, 7},
                                        {8, 7}};
        MGraph<int> G(undigraph, vexs, edges);
        
        // supplement: undirected network
        vector<int> vexs2 = {0, 1, 2, 3, 4, 5, 6, 7, 8};
        vector<tuple<int, int, int>> edges2 = {{1, 2, 2},
                                               {1, 0, 4},
                                               {3, 4, 1},
                                               {3, 5, 3},
                                               {3, 6, 6},
                                               {3, 8, 7},
                                               {5, 6, 5},
                                               {4, 7, 8},
                                               {8, 7, 9}};
        MGraph<int> G2(undinetwork, vexs2, edges2);
    }
    
    // 8.1(2) build undirected graph based on adjacency list
    void testALbuild() {
        vector<int> vexs = {0, 1, 2, 3, 4};
        vector<pair<int, int>> edges = {{1, 2},
                                        {1, 3},
                                        {1, 0},
                                        {2, 3},
                                        {3, 4}};
        ALGraph<int> G(undigraph, vexs, edges);
        
        // supplement: undirected network
        vector<int> vexs2 = {0, 1, 2, 3, 4};
        vector<tuple<int, int, double>> edges2 = {{1, 2, 2.5},
                                                  {1, 0, 4.0},
                                                  {1, 4, 1.6},
                                                  {2, 3, 3.9},
                                                  {3, 4, 6.2}};
        ALGraph<double> G2(undinetwork, vexs, edges);
    }
    
    // 8.1(3) dfs based on MGraph
    void testMdfs() {
        vector<int> vexs = {0, 1, 2, 3, 4};
        vector<pair<int, int>> edges = {{2, 3},
                                        {1, 2},
                                        {3, 0},
                                        {1, 4},
                                        {1, 3}};
        MGraph<int> G(undigraph, vexs, edges);
        G.dfs();
    }
    
    // 8.1(3) dfs based on ALGraph
    void testALdfs() {
        vector<int> vexs = {0, 1, 2, 3, 4};
        vector<pair<int, int>> edges = {{2, 3},
                                        {1, 2},
                                        {3, 0},
                                        {1, 4},
                                        {1, 3}};
        ALGraph<int> G(undigraph, vexs, edges);
        G.dfs();
    }
    
    // 8.1(3) bfs based on MGraph
    void testMbfs() {
        vector<int> vexs = {0, 1, 2, 3, 4};
        vector<pair<int, int>> edges = {{2, 3},
                                        {1, 0},
                                        {3, 4},
                                        {1, 4},
                                        {1, 3}};
        MGraph<int> G(undigraph, vexs, edges);
        G.bfs();
    }
    
    // 8.1(3) bfs based on ALGraph
    void testALbfs() {
        vector<int> vexs = {0, 1, 2, 3, 4};
        vector<pair<int, int>> edges = {{2, 3},
                                        {1, 2},
                                        {3, 4},
                                        {1, 4},
                                        {1, 0}};
        ALGraph<int> G(undigraph, vexs, edges);
        G.bfs();
    }
    
    // 8.2(1) prim based on MGraph
    void testPrim() {
        vector<int> vexs = {0, 1, 2, 3};
        vector<tuple<int, int, double>> edges = {{1, 2, 5.5},
                                                 {1, 3, 4.0},
                                                 {2, 3, 10.0}};
        MGraph<double> G(undinetwork, vexs, edges);
        cout << G.prim(1) << "\n";
    }
    
    // 8.2(2) kruskal based on MGraph
    void testKruskal() {
        vector<int> vexs = {0, 1, 2, 3};
        vector<tuple<int, int, double>> edges = {{1, 2, 5.5},
                                                 {1, 3, 4.0},
                                                 {2, 3, 10.0}};
        MGraph<double> G(undinetwork, vexs, edges);
        vector<tuple<int, int, double>> MST_edges = G.kruskal();
        for (auto [u, v, w]: MST_edges) {
            cout << u << " " << v << " " << w << "\n";
        }
    }
    
    // 8.3(1) dijkstra - O(n^2)
    void testDijkstra() {
        vector<int> vexs = {0, 1, 2, 3, 4, 5};
        vector<tuple<int, int, int>> edges = {
                {1, 2, 10},
                {1, 4, 30},
                {1, 5, 100},
                {2, 3, 50},
                {3, 5, 10},
                {4, 3, 20},
                {4, 5, 60}
        };
        MGraph<int> G(dinetwork, vexs, edges);
        vector<int> path = G.dijkstra(1, 3);
        for (auto& road: path) {
            cout << road << " ";
        }
    }
    
    // 8.3(2) floyd - O(n^3)
    void testFloyd() {
        vector<int> vexs = {0, 1, 2, 3, 4, 5};
        vector<tuple<int, int, int>> edges = {{1, 2, 10},
                                              {1, 4, 30},
                                              {1, 5, 100},
                                              {2, 3, 50},
                                              {3, 5, 10},
                                              {4, 3, 20},
                                              {4, 5, 60}};
        MGraph<int> G(dinetwork, vexs, edges);
        vector<tuple<int, int, vector<int>>> paths = G.floyd();
        for (auto& [u, v, path]: paths) {
            cout << u << " " << v << ": ";
            for (auto& road: path) {
                cout << road << " ";
            }
            cout << "\n";
        }
    }
};