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
    deque<int> findUndigraphLoop();               // undirected graph find loop
    T Prim(int v);                                 // minimum spanning tree
    vector<tuple<int, int, T>> Kruskal();          // minimum spanning tree
    vector<int> Dijkstra(int a, int b);
    vector<tuple<int, int, vector<int>>> Floyd();
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
        if (kind == undigraph) {
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
T MGraph<T>::Prim(int v) {
    T length = 0;
    vector<T> d(vex_cnt, INF); // d[i]表示i号点到集合MST中的最短边长
    vector<bool> MST(vex_cnt, false);
    auto min = [&](T a, T b) {
        return a < b ? a : b;
    };
    
    /* 1. 选择一个点到集合MST中 */
    MST[v] = true;
    for (int i = 0; i < vex_cnt; i++)
        if (!MST[i])
            d[i] = min(d[i], edges[i][v]);
    
    /* 2. 迭代n-1次，选择其他的点到集合MST中 */
    for (int i = 2; i <= vex_cnt; i++) {
        // 找到交叉边中的最短边min_e和其在U-MST集合中的顶点vex
        T min_e = INF;
        int vex;
        for (int j = 1; j <= vex_cnt; j++)
            if (!MST[j] && d[j] < min_e)
                min_e = d[j], vex = j;
        
        // 加入MST集合
        MST[vex] = true;
        if (min_e == INF) {
            cerr << "unable to generate MST!\n";
            exit(1);
        } else {
            length += min_e;
        }
        
        // 迭代更新d数组
        for (int j = 1; j <= vex_cnt; j++)
            if (!MST[j])
                d[j] = min(d[j], edges[j][vex]);
    }
    
    return length;
}

template<class T>
vector<tuple<int, int, T>> MGraph<T>::Kruskal() {
    vector<tuple<int, int, T>> res, edges_set;
    
    // 获取边集
    for (int i = 0; i < vex_cnt; i++) {
        for (int j = 1; j <= vex_cnt; j++) {
            if (edges[i][j]) {
                edges_set.push_back({i, j, edges[i][j]});
            }
        }
    }
    
    /* 1. 按边权升序排序 */
    sort(edges_set.begin(), edges_set.end(), [&](tuple<int, int, T>& x, tuple<int, int, T>& y) {
        return get<2>(x) < get<2>(y);
    });
    
    /* 2. 选边构造MST */
    
    // dsu
    vector<int> p(vex_cnt);
    for (int i = 0; i < vex_cnt; i++) {
        p[i] = i;
    }
    function<int(int)> Find = [&](int now) {
        if (p[now] != now) {
            p[now] = Find(p[now]);
        }
        return p[now];
    };
    
    // 选边
    int cnt = 0; // 统计选择的边数
    for (auto& edge: edges_set) {
        int u = get<0>(edge), v = get<1>(edge);
        T weight = get<2>(edge);
        int pu = Find(u), pv = Find(v);
        if (pu != pv) {
            p[pu] = pv;
            res.push_back({u, v, weight});
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
vector<int> MGraph<T>::Dijkstra(int a, int b) {
    vector<int> res;                      // a->b 的最短路径
    vector<int> pre(vex_cnt, 0);          // SPT(shortest path tree) 中每一个结点的前驱结点
    vector<int> d(vex_cnt, INF);          // d[i] 表示源点 a 到 i 号点的最短路径长度
    vector<bool> SPT(vex_cnt, false);     // 标记 i 号点是否在 SPT 集合中
    
    d[a] = 0;
    
    // 将a号点加入SPT集合
    SPT[a] = true;
    pre[a] = -1;
    for (int j = 1; j <= vex_cnt; j++)
        if (!SPT[j] && d[j] > d[a] + edges[a][j]) {
            /**
             * @note d[j] > d[vex] + edges[vex][j] 注意爆int
             */
            pre[j] = a;
            d[j] = d[a] + edges[a][j];
        }
    
    // 迭代更新n-1次
    for (int i = 1; i <= vex_cnt - 1; i++) {
        // 1. 选择最短边对应的点vex
        int vex = -1;
        for (int j = 1; j <= vex_cnt; j++)
            if (!SPT[j] && (vex == -1 || d[j] < d[vex]))
                vex = j;
        
        // 2. 将选出的点加入SPT集合
        SPT[vex] = true;
        
        // 3. 更新V-SPT中的点到源点的最短距离 & 记录被更新的点的前驱结点为vex
        for (int j = 1; j <= vex_cnt; j++)
            if (!SPT[j] && d[j] > d[vex] + edges[vex][j]) {
                /**
                 * @note d[j] > d[vex] + edges[vex][j] 注意爆int
                 */
                pre[j] = vex;
                d[j] = d[vex] + edges[vex][j];
            }
    }
    
    // 求解最短路径
    while (b != -1) {
        res.push_back(b);
        b = pre[b];
    }
    reverse(res.begin(), res.end());
    
    return res;
}

template<class T>
vector<tuple<int, int, vector<int>>> MGraph<T>::Floyd() {
    vector<tuple<int, int, vector<int>>> res;
    int d[vex_cnt][vex_cnt]{};     // d[i][j] means i to j shortest path length
    int aft[vex_cnt][vex_cnt]{};   // aft[i][j] means i to j first pass vex
    
    // init
    for (int i = 0; i < vex_cnt; i++) {
        for (int j = 1; j <= vex_cnt; j++) {
            if (i == j) {
                d[i][j] = 0;
            } else {
                d[i][j] = INF;
            }
        }
    }
    
    // base
    for (int i = 0; i < vex_cnt; i++) {
        for (int j = 1; j <= vex_cnt; j++) {
            if (i == j) continue;
            if (edges[i][j] != INF) {
                d[i][j] = edges[i][j];
                aft[i][j] = j;
            } else {
                d[i][j] = INF;
            }
        }
    }
    
    // dp
    for (int k = 1; k <= vex_cnt; k++) {
        for (int i = 0; i < vex_cnt; i++) {
            for (int j = 1; j <= vex_cnt; j++) {
                if (d[i][k] != INF && d[k][j] != INF && d[i][k] + d[k][j] < d[i][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                    aft[i][j] = k; // aft[i][j] = aft[i][k] = k
                }
            }
        }
    }
    
    // result
    for (int i = 0; i < vex_cnt; i++) {
        for (int j = 1; j <= vex_cnt; j++) {
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