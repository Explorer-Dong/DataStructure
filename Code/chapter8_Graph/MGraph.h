#include <queue>
#include <limits>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

#ifndef MGRAPH_H
#define MGRAPH_H

enum GraphType { undigraph, undinetwork, digraph, dinetwork };

template<class T>
class MGraph {
private:
    GraphType kind;
    int vex_cnt, edge_cnt;
    vector<int> vexs;
    vector<vector<T>> edges;
    T INF = numeric_limits<T>::max() / 2;

public:
    MGraph(GraphType kind, vector<int>& vexs, vector<pair<int, int>>& edges);     // graph
    MGraph(GraphType kind, vector<int>& vexs, vector<tuple<int, int, T>>& edges); // network
    ~MGraph() = default;
    void dfs();
    void bfs();
    vector<int> findDigraphLoop();                 // directed graph find loop
    deque<int> findUndigraphLoop();                // undirected graph find loop
    T prim(int v);                                 // minimum spanning tree
    vector<tuple<int, int, T>> kruskal();          // minimum spanning tree
    vector<int> dijkstra(int a, int b);
    vector<tuple<int, int, vector<int>>> floyd();
};

template<class T>
MGraph<T>::MGraph(GraphType kind, vector<int>& vexs, vector<pair<int, int>>& edges)
        : kind(kind), vex_cnt(vexs.size()), edge_cnt(edges.size()), vexs(vexs) {
    this->edges.resize(vex_cnt, vector<T>(vex_cnt, INF));
    for (auto [u, v]: edges) {
        this->edges[u][v] = 1;
        if (kind == undigraph) {
            this->edges[v][u] = 1;
        }
    }
}

template<class T>
MGraph<T>::MGraph(GraphType kind, vector<int>& vexs, vector<tuple<int, int, T>>& edges)
        : kind(kind), vex_cnt(vexs.size()), edge_cnt(edges.size()), vexs(vexs) {
    this->edges.resize(vex_cnt, vector<T>(vex_cnt, INF));
    for (auto [u, v, w]: edges) {
        this->edges[u][v] = w;
        if (kind == undinetwork) {
            this->edges[v][u] = w;
        }
    }
}

template<class T>
void MGraph<T>::dfs() {
    vector<bool> vis(vex_cnt, false);
    function<void(int)> dfs = [&](int now) {
        cout << now << " ";
        vis[now] = true;
        for (int i = 0; i < vex_cnt; i++) {
            if (edges[now][i] && !vis[i]) {
                dfs(i);
            }
        }
    };
    for (int i = 0; i < vex_cnt; i++) {
        if (!vis[i]) {
            dfs(i);
        }
    }
}

template<class T>
void MGraph<T>::bfs() {
    vector<bool> vis(vex_cnt, false);
    auto bfs = [&](int hh) {
        queue<int> q;
        vis[hh] = true;
        q.push(hh);
        while (q.size()) {
            auto now = q.front();
            q.pop();
            cout << now << " ";
            for (int i = 0; i < vex_cnt; i++) {
                if (edges[now][i] && !vis[i]) {
                    vis[i] = true;
                    q.push(i);
                }
            }
        }
    };
    // for all connected components
    for (int i = 0; i < vex_cnt; i++) {
        if (!vis[i]) {
            bfs(i);
        }
    }
}

template<class T>
vector<int> MGraph<T>::findDigraphLoop() {
    vector<int> loop;
    bool find_one_loop = false;
    vector<bool> vis(vex_cnt, false);
    vector<bool> vis2(vex_cnt, false);
    
    // store loop
    function<void(int)> getLoop = [&](int now) {
        vis2[now] = true;
        loop.push_back(now);
        for (int i = 0; i < vex_cnt; i++) {
            if (edges[now][i] != INF && vis[i] && !vis2[i]) {
                getLoop(i);
            }
        }
    };
    
    // check loop
    function<void(int)> dfs = [&](int now) {
        if (find_one_loop) {
            return;
        }
        if (vis[now]) {
            find_one_loop = true;
            getLoop(now);
            return;
        }
        vis[now] = true;
        for (int i = 0; i < vex_cnt; i++) {
            if (edges[now][i] != INF) {
                dfs(i);
            }
        }
        vis[now] = false;
    };
    
    // check all connected components
    for (int i = 0; i < vex_cnt; i++) {
        if (!find_one_loop && !vis[i]) {
            dfs(i);
        }
    }
    
    return loop;
}

template<class T>
deque<int> MGraph<T>::findUndigraphLoop() {
    deque<T> loop, path;
    vector<bool> vis(vex_cnt, false);
    bool find_one_loop = false;
    
    // find loop
    function<void(int, int)> dfs = [&](int parent, int now) {
        if (find_one_loop) {
            return;
        }
        if (vis[now]) {
            find_one_loop = true;
            while (path.front() != now) {
                path.pop_front();
            }
            loop = path;
            return;
        }
        vis[now] = true;
        path.push_back(now);
        for (int i = 0; i < vex_cnt; i++) {
            if (edges[now][i] != INF && i != parent) {
                dfs(now, i);
            }
        }
        vis[now] = false;
        path.pop_back();
    };
    
    // check all connected components
    for (int i = 0; i < vex_cnt; i++) {
        if (!find_one_loop && !vis[i]) {
            dfs(-1, i);
        }
    }
    
    return loop;
}

template<class T>
T MGraph<T>::prim(int v) {
    T length = 0;
    vector<T> d(vex_cnt, INF); // d[i] means min edge from i to MST
    vector<bool> MST(vex_cnt, false);
    auto min = [&](T a, T b) {
        return a < b ? a : b;
    };
    
    /* 1. choose v as the first point */
    MST[v] = true;
    for (int j = 0; j < vex_cnt; j++) {
        if (!MST[j]) {
            d[j] = min(d[j], edges[j][v]);
        }
    }
    
    /* 2. choose n-1 edges */
    for (int i = 0; i < vex_cnt - 1; i++) {
        // find the shortest edge min_e and its corresponding point vex
        int vex = -1;
        for (int j = 0; j < vex_cnt; j++) {
            if (!MST[j] && (vex == -1 || d[j] < d[vex])) {
                vex = j;
            }
        }
        
        // add vex to MST
        MST[vex] = true;
        
        // add min_e to length
        if (d[vex] == INF) {
            cerr << "unable to generate MST!\n";
            exit(1);
        } else {
            length += d[vex];
        }
        
        // dp method to update d
        for (int j = 0; j < vex_cnt; j++) {
            if (!MST[j]) {
                d[j] = min(d[j], edges[j][vex]);
            }
        }
    }
    
    return length;
}

template<class T>
vector<tuple<int, int, T>> MGraph<T>::kruskal() {
    vector<tuple<int, int, T>> res;
    vector<tuple<T, int, int>> edges_set;
    
    // store all edges
    for (int i = 0; i < vex_cnt; i++) {
        for (int j = 0; j < vex_cnt; j++) {
            if (edges[i][j] != INF) {
                edges_set.push_back({edges[i][j], i, j});
            }
        }
    }
    
    /* 1. sort with edge weight */
    sort(edges_set.begin(), edges_set.end());
    
    class DSU {
    public:
        vector<int> p;
        
        DSU(int n) {
            p.resize(n);
            for (int i = 0; i < n; i++) {
                p[i] = i;
            }
        }
        
        int findParent(int now) {
            if (p[now] != now) {
                p[now] = findParent(p[now]);
            }
            return p[now];
        }
        
        void unionSet(int u, int v) {
            p[findParent(u)] = findParent(v);
        }
        
        bool sameSet(int u, int v) {
            return findParent(u) == findParent(v);
        }
    };
    
    /* 2. choose n-1 edges */
    int cnt = 0; // count of edges
    DSU dsu(vex_cnt);
    for (auto [w, u, v]: edges_set) {
        if (!dsu.sameSet(u, v)) {
            res.push_back({u, v, w});
            dsu.unionSet(u, v);
            cnt++;
        }
        if (cnt == vex_cnt - 1) {
            break;
        }
    }
    if (cnt < vex_cnt - 1) {
        cerr << "unable to generate MST!\n";
        exit(1);
    }
    
    return res;
}

template<class T>
vector<int> MGraph<T>::dijkstra(int a, int b) {
    vector<int> res;                      // a->b shortest path
    vector<int> pre(vex_cnt, 0);          // pre[i] means i's previous point
    vector<int> d(vex_cnt, INF);          // d[i] means a to i shortest path length
    vector<bool> SPT(vex_cnt, false);     // SPT[i] means i is in SPT
    
    // join a to SPT
    d[a] = 0;
    SPT[a] = true;
    pre[a] = -1;
    for (int j = 0; j < vex_cnt; j++) {
        if (!SPT[j] && d[j] > d[a] + edges[a][j]) {
            pre[j] = a;
            d[j] = d[a] + edges[a][j];
        }
    }
    
    // choose n-1 points
    for (int i = 1; i <= vex_cnt - 1; i++) {
        // 1. choose the shortest edge
        int vex = -1;
        for (int j = 0; j < vex_cnt; j++) {
            if (!SPT[j] && (vex == -1 || d[j] < d[vex])) {
                vex = j;
            }
        }
        
        // 2. join vex to SPT
        SPT[vex] = true;
        
        // 3. update the shortest path from vex to other points
        // record the previous point of the updated point as vex
        for (int j = 0; j < vex_cnt; j++) {
            if (!SPT[j] && d[j] > d[vex] + edges[vex][j]) {
                pre[j] = vex;
                d[j] = d[vex] + edges[vex][j];
            }
        }
    }
    
    // get path
    while (b != -1) {
        res.push_back(b);
        b = pre[b];
    }
    reverse(res.begin(), res.end());
    
    return res;
}

template<class T>
vector<tuple<int, int, vector<int>>> MGraph<T>::floyd() {
    vector<tuple<int, int, vector<int>>> res;
    // d[i][j] means i to j shortest path length
    vector<vector<int>> d(vex_cnt, vector<int>(vex_cnt, INF));
    // aft[i][j] means i to j first pass vex
    vector<vector<int>> aft(vex_cnt, vector<int>(vex_cnt, -1));
    
    // init
    for (int i = 0; i < vex_cnt; i++) {
        for (int j = 0; j < vex_cnt; j++) {
            if (i == j) {
                d[i][j] = 0;
            } else if (edges[i][j] != INF) {
                d[i][j] = edges[i][j];
                aft[i][j] = j;
            }
        }
    }
    
    // dp
    for (int k = 0; k < vex_cnt; k++) {
        for (int i = 0; i < vex_cnt; i++) {
            for (int j = 0; j < vex_cnt; j++) {
                if (d[i][k] != INF && d[k][j] != INF && d[i][k] + d[k][j] < d[i][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                    aft[i][j] = k; // aft[i][j] = aft[i][k] = k
                }
            }
        }
    }
    
    // result
    for (int i = 0; i < vex_cnt; i++) {
        for (int j = 0; j < vex_cnt; j++) {
            if (d[i][j] != INF && d[i][j]) {
                vector<int> path;
                path.push_back(i);
                int next = aft[i][j];
                while (next != j) {
                    path.push_back(next);
                    next = aft[next][j];
                }
                path.push_back(j);
                res.push_back({i, j, path});
            }
        }
    }
    
    return res;
}

#endif //MGRAPH_H