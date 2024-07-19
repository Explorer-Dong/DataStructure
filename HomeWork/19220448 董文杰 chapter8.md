1. 假设以邻接表表示法作为图的存储结构，设计图的深度优先遍历递归算法。

    > 思路：遍历每个连通分量，在连通分量中；一边遍历一边打标记即可
    >
    > 时间复杂度：$O(n+e)$

     ```c++
     template<class T>
     void ALGraph<T>::dfs() {
         // 辅助变量
     	vector<bool> vis(n + 1, false);
     
         // 深搜函数
     	function<void(int, vector<bool>&)> dfs = [&](int now, vector<bool>& vis) {
     		cout << now << " ";
     		vis[now] = true;
     		for (EdgeNode<T>* p = h[now].next; p; p = p->next) {
     			if (!vis[p->toid]) {
     				dfs(p->toid, vis);
     			}
     		}
     	};
     
         // 调用
     	for (int i = 1; i <= n; i++) {
     		if (!vis[i]) {
     			dfs(i, vis);
     		}
     	}
     }
     ```

2. 试基于图的广度优先搜索策略编写一算法，判别以邻接表方式存储的有向图中是否存在由顶点 $v_i$ 到顶点 $v_j$ 的路径 $(i\ne j)$。

    > 思路：其实就是 $bfs$ 遍历图即可，然后判断是否从 $v_i$ 开始能够遍历到 $v_j$
    >
    > 注意点：
    >
    > 1. 与树的 $bfs$ 的区别
    >
    >     - 树的 $bfs$ 遍历不需要标记当前结点是否遍历过，因为不会对后续的遍历产生影响 - 由于树的特性（特殊的有向无环图）当前结点不会再遍历到之前已经遍历过的结点
    >
    >     - 图的 $bfs$ 遍历需要标记当前结点是否遍历过，因为环的原因，就需要打标记，否则就会出错
    >
    > 时间复杂度：$O(n+e)$

    ```c++
    template<class T>
    bool ALGraph<T>::FindPathFromA2B(int a, int b) {
    	// 越界判断
    	if (a < 1 || a > n || b < 1 || b > n) {
    		cerr << "Wrong Input! Out of Range!\n";
    		exit(1);
    	}
    
    	// 辅助变量
    	vector<bool> vis(n + 1, false);
    	bool ok = false;
    
    	// 宽搜函数
    	auto bfs = [&](int hh) {
    		queue<int> q;
    		q.push(hh);
    
    		while (q.size()) {
    			auto now = q.front();
    			q.pop();
    			vis[now] = true;
    
    			// 搜到路径了直接结束搜索
    			if (now == b) {
    				ok = true;
    				break;
    			}
    
    			for (EdgeNode<T>* p = h[now].next; p; p = p->next) {
    				if (!vis[p->toid]) {
    					vis[p->toid] = true; // 与树的bfs唯一的不同
    					q.push(p->toid);
    				}
    			}
    		}
    	};
    
    	// 调用过程并返回答案
    	bfs(a);
    	return ok;
    }
    ```

3. 采用邻接表作存储结构，编写一个判别无向图中任意两个给定的两个顶点之间是否存在一条长度为 $k$ 的简单路径的算法。

    > 思路：基于 $dfs$ 和 $finish状态消除标记$ 即可解决
    >
    > 时间复杂度：$O(n+e)$

    ```c++
    template<class T>
    bool ALGraph<T>::FindPathFromA2BLengthK(int a, int b, int k) {
    	// 越界判断
    	if (a < 1 || a > n || b < 1 || b > n) {
    		cerr << "Wrong Input! Out of Range!\n";
    		exit(1);
    	}
    
    	// 辅助变量
    	vector<vector<int>> paths;
    	vector<int> path;
    	vector<bool> vis(n + 1, false);
    
    	// 深搜函数
    	function<void(int)> dfs = [&](int now) {
    		vis[now] = true;
    		path.push_back(now);
    
    		if (now == b && path.size() - 1 == k) {
    			paths.push_back(path);
    			path.pop_back();
    			vis[now] = false;
    			return;
    		}
    
    		for (EdgeNode<T>* p = h[now].next; p; p = p->next)
    			if (!vis[p->toid])
    				dfs(p->toid);
    
    		path.pop_back();
    		vis[now] = false;
    	};
    
    	// 调用并返回
    	dfs(a);
    	return paths.size() >= 1;
    }
    ```

4. 假设以邻接矩阵作为图的存储结构，编写算法判断在给定的有向图中是否存在一个简单有向回路。若存在，则以顶点序列的方式输出该回路（找到一条即可）。（选做题）

    > 思路：
    >
    > - 我们将此题分解为两个部分，判环与存环
    > - 判环：由于是有向图，判环更加简单，只需要直接判断当前遍历到的结点是否已经被标记过即可。如果被标记过了，就寻找到了一个环
    > - 存环：在上述判环时，如果判定到了一个环，就从那个点出发，将路径上已经被标记过的点进行存储即可
    >
    > 时间复杂度：$O(n^2)$ 
    >
    > - 对于邻接矩阵，每一个结点在搜索邻接点时都是 $O(n)$，最坏的情况就是每一个点都遍历到，于是就是 $O(n^2)$

    ```c++
    template<class T>
    vector<T> MGraph<T>::FindLoop() {
    	vector<T> loop;
    
    	bool ok = false;
    	vector<bool> vis(n + 1, false), vis2(n + 1, false);
    
    	// 存环
    	function<void(int)> GetPath = [&](int now) {
    		vis2[now] = true;
    		loop.push_back(now);
    
    		for (int i = 1; i <= n; i++)
    			if (edges[now][i] && vis[i] && !vis2[i])
    				GetPath(i);
    	};
    
    	// 判环
    	function<void(int)> dfs = [&](int now) {
    		if (ok) {
    			return;
    		}
    
    		if (vis[now]) {
    			ok = true;
    			GetPath(now);
    			return;
    		}
    
    		vis[now] = true;
    
    		for (int i = 1; i <= n; i++)
    			if (edges[now][i])
    				dfs(i);
    
    		vis[now] = false;
    	};
    
    	// 遍历连通分量
    	for (int i = 1; i <= n; i++)
    		if (!ok)
    			dfs(i);
    
    	return loop;
    }
    ```

5. 假设以邻接矩阵作为图的存储结构，设计一个算法判断一个给定无向图中是否存在回路？若存在，则以顶点序列的方式输出该回路。

    > 思路：
    >
    > - 同样按照 $T4$ 的思路，分为判环与存环
    > - 判环：判环相比于有向图增加了一个 $trick$，即在探索当前点 `now` 的可达点时，要排除当前点的上一级点 `before`。排除方法就是在 $dfs$ 搜索时，多传递一个参数即可
    > - 存环：存环相比于有向图需要改变一下策略，因为对于有向图，一旦遇到已经遇到的点 `v` 之后，直接从 `v` 点开始探索已标记的点即可；但是对于无向图这种策略是错误的，因为会有环之外的点被记录进去，解决方法就是：在 $dfs$ 搜索记录路径时，采用**双端队列**的形式，在探索到已探索的点时，将路径队列进行处理即可。处理方法就是对比队列的队头与队尾，不断弹出队头直到队头与队尾相等即可。
    > - 时间复杂度：$O(n^2)$

    ```c++
    template<class T>
    deque<T> MGraph<T>::FindLoop_un() {
    	deque<T> loop;
    
    	vector<bool> vis(n + 1, false);
    	deque<T> path;
    	bool ok = false;
    
    	// 深搜函数
    	function<void(int, int)> dfs = [&](int before, int now) {
    		if (ok) return;
    
    		if (vis[now]) {
    			ok = true;
    			while (path.front() != now) path.pop_front();
    			loop = path;
    			return;
    		}
    
    		vis[now] = true;
    		path.push_back(now);
    
    		for (int i = 1; i <= n; i++)
    			if (edges[now][i] && i != before)
    				dfs(now, i);
    
    		vis[now] = false;
    		path.pop_back();
    	};
    
    	// 选择探索起点 - 任意选择一个点即可
    	dfs(-1, 1);
    
    	return loop;
    }
    ```

6. 对下图所示的连通网，请分别用 $prim$ 算法和 $kruskal$ 算法构造该网的最小生成树。

    <img src="https://s2.loli.net/2023/12/05/akYgwmrEnPIdbsZ.png" alt="image-20231205135602397" style="zoom:50%;" />

    > - 均使用邻接矩阵进行存储，初始化图时，所有边权均初始化为无穷大 `INF`
    > - $prim$ 算法时间复杂度：$O(n^2)$
    > - $kruskal$ 算法时间复杂度：$O(e \log e)$

    $prim$ 算法

    ```c++
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

    ```c++
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

7. 如何寻找一个图的最大生成树，也即总权重最大的生成树。

    法一：

    - 直接将所有的边权取相反数，然后执行两种最小生成树算法即可

    法二：

    - 修改 $prim$ 算法，每次选取交叉边从**最小权值交叉边**，改为每次选取**最大权值交叉边**
    - 修改 $kruskal$ 算法，将边权按照**升序排序**进行选择，改为将边权按照**降序排序**进行选择
