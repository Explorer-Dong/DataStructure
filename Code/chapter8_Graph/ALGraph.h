#include <iostream>
#include <vector>
#include <functional>

using namespace std;

#ifndef ALGRAPH_H
#define ALGRAPH_H

template<class T>
struct EdgeNode {
    int toid;       // edge to
    T info;         // edge info
    EdgeNode* next; // next edge
    
    EdgeNode(int toid) : toid(toid) {}
    
    EdgeNode(int toid, T info) : toid(toid), info(info) {}
};

template<class T>
struct VexNode {
    int id;            // vertex id (default 0 ~ n-1)
    T info;            // vertex info
    EdgeNode<T>* next; // first edge
};

template<class T>
class ALGraph {
private:
    GraphType kind;
    int vex_cnt, edge_cnt;
    vector<VexNode<T>> head;
    void add(int u, int v);         // add graph edge
    void add(int u, int v, T info); // add network edge

public:
    ALGraph() : vex_cnt(0), edge_cnt(0), head(0) {}
    
    ALGraph(GraphType kind, vector<int>& vexs, vector<pair<int, int>>& edges);         // graph
    ALGraph(GraphType kind, vector<int>& vexs, vector<tuple<int, int, T>>& edges);     // network
    ~ALGraph();
    void dfs();
    void bfs();
    bool findPathFromA2B(int a, int b);
    vector<vector<int>> findPathFromA2BLengthK(int a, int b, int k);
};

template<class T>
ALGraph<T>::ALGraph(GraphType kind, vector<int>& vexs, vector<pair<int, int>>& edges)
        : kind(kind), vex_cnt(vexs.size()), edge_cnt(edges.size()), head(vex_cnt) {
    // init head
    for (int i = 0; i < vex_cnt; i++) {
        head[i].id = i;
        head[i].next = nullptr;
    }
    // add edge
    for (auto [u, v]: edges) {
        add(u, v);
        if (kind == undigraph) {
            add(v, u);
        }
    }
}

template<class T>
ALGraph<T>::ALGraph(GraphType kind, vector<int>& vexs, vector<tuple<int, int, T>>& edges)
        : kind(kind), vex_cnt(vexs.size()), edge_cnt(edges.size()), head(vex_cnt) {
    // init head
    for (int i = 0; i < vex_cnt; i++) {
        head[i].id = i;
        head[i].next = nullptr;
    }
    // add edge
    for (auto [u, v, w]: edges) {
        add(u, v, w);
        if (kind == undinetwork) {
            add(v, u, w);
        }
    }
}

template<class T>
ALGraph<T>::~ALGraph() {
    for (int i = 0; i < vex_cnt; i++) {
        EdgeNode<T>* edge = head[i].next;
        while (edge) {
            EdgeNode<T>* now = edge;
            edge = edge->next;
            delete now;
        }
    }
}

template<class T>
void ALGraph<T>::add(int u, int v) {
    EdgeNode<T>* edge = new EdgeNode<T>(v);
    edge->next = head[u].next;
    head[u].next = edge;
}

template<class T>
void ALGraph<T>::add(int u, int v, T info) {
    EdgeNode<T>* edge = new EdgeNode<T>(v, info);
    edge->next = head[u].next;
    head[u].next = edge;
}

template<class T>
void ALGraph<T>::dfs() {
    vector<bool> vis(vex_cnt, false);
    
    // lambda dfs
    function<void(int)> dfs = [&](int now) {
        cout << now << " ";
        vis[now] = true;
        for (EdgeNode<T>* p = head[now].next; p; p = p->next) {
            if (!vis[p->toid]) {
                dfs(p->toid);
            }
        }
    };
    
    for (int i = 0; i < vex_cnt; i++) {
        if (!vis[i]) {
            cout << "Connected Component: ";
            dfs(i);
            cout << endl;
        }
    }
}

template<class T>
void ALGraph<T>::bfs() {
    vector<bool> vis(vex_cnt, false);
    
    // lambda bfs
    auto bfs = [&](int start) {
        queue<int> q;
        vis[start] = true;
        q.push(start);
        while (q.size()) {
            auto now = q.front();
            q.pop();
            cout << now << " ";
            for (EdgeNode<T>* p = head[now].next; p; p = p->next) {
                if (!vis[p->toid]) {
                    vis[p->toid] = true;
                    q.push(p->toid);
                }
            }
        }
    };
    
    for (int i = 0; i < vex_cnt; i++) {
        if (!vis[i]) {
            cout << "Connected Component: ";
            bfs(i);
            cout << endl;
        }
    }
}

template<class T>
bool ALGraph<T>::findPathFromA2B(int a, int b) {
    if (a < 0 || a >= vex_cnt || b < 0 || b >= vex_cnt) {
        cerr << "Wrong Input! Out of Range!\n";
        exit(1);
    }
    
    vector<bool> vis(vex_cnt, false);
    auto bfs = [&](int start) -> bool {
        queue<int> q;
        vis[start] = true;
        q.push(start);
        while (q.size()) {
            auto now = q.front();
            q.pop();
            
            // find path
            if (now == b) {
                return true;
            }
            
            for (EdgeNode<T>* p = head[now].next; p; p = p->next) {
                if (!vis[p->toid]) {
                    vis[p->toid] = true;
                    q.push(p->toid);
                }
            }
        }
        return false;
    };
    
    return bfs(a);
}

template<class T>
vector<vector<int>> ALGraph<T>::findPathFromA2BLengthK(int a, int b, int k) {
    if (a < 0 || a >= vex_cnt || b < 0 || b >= vex_cnt) {
        cerr << "Wrong Input! Out of Range!\n";
        exit(1);
    }
    
    vector<bool> vis(vex_cnt, false);
    vector<vector<int>> paths;
    vector<int> path;
    
    // lambda function
    function<void(int)> dfs = [&](int now) {
        vis[now] = true;
        path.push_back(now);
        if (now == b && path.size() - 1 == k) {
            // store path length k to paths
            paths.push_back(path);
            vis[now] = false;
            path.pop_back();
            return;
        }
        for (EdgeNode<T>* p = head[now].next; p; p = p->next) {
            if (!vis[p->toid]) {
                dfs(p->toid);
            }
        }
        vis[now] = false;
        path.pop_back();
    };
    
    dfs(a);
    
    return paths;
}

#endif //ALGRAPH_H