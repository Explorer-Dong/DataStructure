## 作业八

### T1

> 假设以邻接表表示法作为图的存储结构，设计图的深度优先遍历递归算法。

以无向图为例。为了防止重边和自环，在遍历时需要额外申请空间用来记录顶点的访问状态。时间复杂度 $O(n+e)$，其中 $n$ 为顶点数，$e$ 为边数。

```cpp
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
```

### T2

> 试基于图的广度优先搜索策略编写一算法，判别以邻接表方式存储的有向图中是否存在由顶点 $v_i$ 到顶点 $v_j$ 的路径 $(i\ne j)$。

从 $v_i$ 开始 bfs 遍历直到遇到 $v_j$ 为止。时间复杂度 $O(n+e)$

```cpp
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
```

### T3

> 采用邻接表作存储结构，编写一个判别无向图中任意两个给定的两个顶点之间是否存在一条长度为 $k$ 的简单路径的算法。

从起点开始 dfs 并记录当前搜索路径中的结点数，当遇到终点并且路径长度为 k 表示找到了长度为 k 的简单路径。为了便于判定，我们记录路径上的点。时间复杂度 $O(n+e)$

```cpp
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
```

### T4

> 假设以邻接矩阵作为图的存储结构，编写算法判断在给定的有向图中是否存在一个简单有向回路。若存在，则以顶点序列的方式输出该回路（找到一条即可）。（选做题）

思路：

- 我们将此题分解为两个部分，判环与存环
- 判环：由于是有向图，判环更加简单，只需要直接判断当前遍历到的结点是否已经被标记过即可。如果被标记过了，就寻找到了一个环
- 存环：在上述判环时，如果判定到了一个环，就从那个点出发，将路径上已经被标记过的点进行存储即可

时间复杂度 $O(n^2)$

- 对于邻接矩阵，每一个结点在搜索邻接点时都是 $O(n)$，最坏的情况就是每一个点都遍历到，于是就是 $O(n^2)$

```cpp
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
```

### T5

> 假设以邻接矩阵作为图的存储结构，设计一个算法判断一个给定无向图中是否存在回路？若存在，则以顶点序列的方式输出该回路。

思路：

- 同样按照 T4 的思路，分为判环与存环
- 判环：判环相比于有向图增加了一个 trick，即在探索当前点 `now` 的可达点时，要排除当前点的上一级点 `before`。排除方法就是在 dfs 搜索时，多传递一个参数即可
- 存环：存环相比于有向图需要改变一下策略，因为对于有向图，一旦遇到已经遇到的点 `v` 之后，直接从 `v` 点开始探索已标记的点即可；但是对于无向图这种策略是错误的，因为会有环之外的点被记录进去，解决方法就是：在 dfs 搜索记录路径时，采用 「**双端队列**」的形式，在探索到已探索的点时，将路径队列进行处理即可。处理方法就是对比队列的队头与队尾，不断弹出队头直到队头与队尾相等即可。

时间复杂度 $O(n^2)$

```cpp
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
```

### T6

> 对下图所示的连通网，请分别用 $prim$ 算法和 $kruskal$ 算法构造该网的最小生成树。
>
> ![连通网](https://dwj-oss.oss-cn-nanjing.aliyuncs.com/images/202408122131699.png)

- 均使用邻接矩阵进行存储，初始化图时，所有边权均初始化为无穷大 `INF`
- $prim$ 算法时间复杂度：$O(n^2)$
- $kruskal$ 算法时间复杂度：$O(e \log e)$

$prim$ 算法

```cpp
template<class T>
T MGraph<T>::Prim(int v) {
	T length = 0;

	vector<T> d(n + 1, INF); // d[i]表示i号点到集合MST中的最短边长
	vector<bool> MST(n + 1, false);

	auto min = [&](T a, T b) {
		return a < b ? a : b;
	};

	/* 1. 选择一个点到集合MST中 */
	MST[v] = true;
	for (int i = 1; i <= n; i++)
		if (!MST[i])
			d[i] = min(d[i], edges[i][v]);

	/* 2. 迭代n-1次，选择其他的点到集合MST中 */
	for (int i = 2; i <= n; i++) {
		// 找到交叉边中的最短边min_e和其在U-MST集合中的顶点vex
		T min_e = INF;
		int vex;
		for (int j = 1; j <= n; j++)
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
		for (int j = 1; j <= n; j++)
			if (!MST[j])
				d[j] = min(d[j], edges[j][vex]);
	}

	return length;
}
```

$kruskal$ 算法

```cpp
template<class T>
vector<tuple<int, int, T>> MGraph<T>::Kruskal() {
	vector<tuple<int, int, T>> res, edges_set;

	// 获取边集
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (edges[i][j])
				edges_set.push_back({i, j, edges[i][j]});

	/* 1. 按边权升序排序 */
	sort(edges_set.begin(), edges_set.end(), [&](tuple<int, int, T>& x, tuple<int, int, T>& y){
		return get<2>(x) < get<2>(y);
	});

	/* 2. 选边构造MST */

	// 并查集
	vector<int> p(n + 1);
	for (int i = 1; i <= n; i++) {
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

		if (cnt == n - 1) {
			break;
		}
	}

	if (cnt < n - 1) {
		cerr << "unable to generate MST!\n";
		exit(1);
	}

	return res;
}
```

### T7

> 如何寻找一个图的最大生成树，也即总权重最大的生成树。

法一：

- 直接将所有的边权取相反数，然后执行两种最小生成树算法即可

法二：

- 修改 $prim$ 算法，每次选取交叉边从**最小权值交叉边**，改为每次选取**最大权值交叉边**
- 修改 $kruskal$ 算法，将边权按照**升序排序**进行选择，改为将边权按照**降序排序**进行选择

### T8

> 试利用Dijkstra算法求下图中从顶点A到其他顶点间的最短路径，写出执行过程中各步的状态。
>
> ![img](https://dwj-oss.oss-cn-nanjing.aliyuncs.com/images/202408122133428.png)



```cpp

```

## 实验八

### T1

![1](https://dwj-oss.oss-cn-nanjing.aliyuncs.com/images/202408122134645.png)



### T2

![2](https://dwj-oss.oss-cn-nanjing.aliyuncs.com/images/202408122135828.png)



### T3

![3](https://dwj-oss.oss-cn-nanjing.aliyuncs.com/images/202408122135248.png)

### T4

![4](https://dwj-oss.oss-cn-nanjing.aliyuncs.com/images/202408122135431.png)

