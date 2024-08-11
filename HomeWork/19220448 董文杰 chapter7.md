## 作业七

### T1

> 若一棵 *m* 叉树中，度为1的结点有*N*1个，度为2的结点有*N*2个，……，度为*m*的结点有*Nm*个，问该树的叶子结点有多少个？

我们约定题中的度为出度，树的结点数为 $v$，边数为 $e$，则有关系式：
$$
v=e+1
$$
已知度 $\ge 1$ 的结点数 $\sum_{k=1}^m N_k$ ，则度为 $0$ 的叶子结点数 $N_0$ 为：
$$
\begin{aligned}
N_0&=v-\sum_{k=1}^m N_k\\
&= e+1-\sum_{k=1}^m N_k\\
&= \sum_{k=1}^m k\cdot N_k +1 - \sum_{k=1}^m N_k\\
&= \sum_{k=1}^m (k-1)\cdot N_k +1
\end{aligned}
$$
### T2

> 试找出分别满足下列条件的所有二叉树： （此题在纸上画，不用提交）
> （1）先序序列和中序序列相同；
> （2）中序序列和后序序列相同；
> （3）先序序列和后序序列相同。

这道题一开始可能没什么思路，也许可以随意画几个结点凑数，但是没有一般的结论。但我们从递归的角度思考本题也许会有不一样的发现。

对于一个二叉树，我们将其定义为「根、左子树、右子树」三个部分。则先序遍历是根左右，中序遍历是左根右，后序遍历是左右根。

于是对于上述三种问题，想要某种序列和另外一种序列相同，就是对应的三部分要相同。显然的只有根一定合法，但是如果左右子树同时存在就一定不可能合法，想要合法就只能删除子树，因此可得：

（1）先序 = 中序 $\to$ 根左右 = 左根右 $\to$ `根#右` = `#根右`

（2）中序 = 后序 $\to$ 左根右 = 左右根 $\to$ `左根#` = `左#根`

（3）先序 = 后序 $\to$ 根左右 = 左右根 $\to$ `根##` = `##根`

### T3

> 设有168个结点的完全二叉树，请问叶子结点、单分支结点、双分支结点各有多少个？

假设层数从 $0$ 开始，则当前完全二叉树共有 $\left \lceil \log_2(N+1) \right \rceil=8$ 层，即 $[0,7]$ 层中均有结点，其中：

- $[0, 6]$ 层是满二叉树，共 $2^{6+1}-1=127$ 个结点
- 第 $7$ 层有 $2^7=128$ 个位置。从左至右占用了 $168-127=41$ 个位置

于是可以计算出：

- 双分支结点为 $127-64+ \left \lfloor \frac{41}{2} \right \rfloor=83$ 个
- 单分支结点为 $41\%2=1$ 个
- 叶子结点为 $41+64-\left \lceil \frac{41}{2} \right \rceil=84$ 个

### T4

> 已知某二叉树的后序序列是*GEFCDBA*，中序序列是*AEGCFBD*，请画出该二叉树的二叉链表结构图，并写出先序遍历序列。

每次利用后序找到「根」将中序分解为左子树、根、右子树，然后递归分解左右子树即可。

<img src="https://dwj-oss.oss-cn-nanjing.aliyuncs.com/images/202408081604470.png" alt="image-20231107144008995" style="zoom:15%;" />

### T5

> 试编写算法求二叉树中双分支节点的个数。

遍历每一个结点判断左右结点是否存在即可，至于如何遍历，可以 dfs 也可以 bfs，其中 dfs 也可以写成递归的形式，这里以 bfs 为例。时间复杂度 $O(n)$

```cpp
template<class T>
int BinaryTree<T>::countDoubleBranchNode() {
    int cnt = 0;
    queue<BinaryTreeNode<T>*> q;
    q.push(root);
    while (q.size()) {
        auto now = q.front();
        q.pop();
        cnt += now->lchild != nullptr && now->rchild != nullptr;
        if (now->lchild) {
            q.push(now->lchild);
        }
        if (now->rchild) {
            q.push(now->rchild);
        }
    }
    return cnt;
}
```

### T6

> 试编写算法求二叉树中各个结点的平衡因子（左右子树高度之差）

回溯法解决即可。时间复杂度 $O(n)$

```cpp
template<class T>
int BinaryTree<T>::hight(BinaryTreeNode<T>* now, 
                         vector<pair<T, int>>& res) {
    if (!now) {
        return 0;
    }
    int lh = hight(now->lchild, res);
    int rh = hight(now->rchild, res);
    res.push_back({now->data, abs(lh - rh)});
    return max(lh, rh) + 1;
}
```

### T7

> 一棵二叉树以二叉链表来表示，求其指定的某一层 $k(k>1)$ 上的叶子结点的个数。

遍历时增加参数为当前层数后哈希即可。时间复杂度 $O(n)$

```cpp
template<class T>
void BinaryTree<T>::dfs(BinaryTreeNode<T>* now, int depth, 
                        unordered_map<int, int>& f) {
    if (!now) {
        return;
    }
    f[depth]++;
    dfs(now->lchild, depth + 1, f);
    dfs(now->rchild, depth + 1, f);
}
```

### T8

> 试编写算法输出一棵二叉树中根结点到各个叶子结点的路径。

遍历时记录路径，遇到叶子结点保存完整路径即可，需要在回溯时弹出遍历过的结点。时间复杂度 $O(n)$

```cpp
template<class T>
void BinaryTree<T>::dfs(BinaryTreeNode<T>* now, vector<T>& path, 
                        vector<vector<T>>& res) {
    if (!now) {
        return;
    }
    path.push_back(now->data);
    if (!now->lchild && !now->rchild) {
        res.push_back(path);
        path.pop_back();
        return;
    }
    dfs(now->lchild, path, res);
    dfs(now->rchild, path, res);
    path.pop_back();
}
```

### T9

> 设计一个算法，求二叉树中两个给定结点的最近公共祖先。

方法一：**枚举**。我们可以利用 $T10$ 封装好的函数直接求解。即：求出根结点两个指定结点的路径，返回最右端的相同字符即可。每次询问的时间复杂度 $O(n)$

```cpp
template<class T>
T BinaryTree<T>::getLowestCommonAncestor(T a, T b) {
    vector<T> path_to_a = getPathFromRootToNode(a);
    vector<T> path_to_b = getPathFromRootToNode(b);
    T res;
    for (int i = 0; i < path_to_a.size(); i++) {
        if (path_to_a[i] == path_to_b[i]) {
            res = path_to_a[i];
        } else {
            break;
        }
    }
    return res;
}
```

方法二：**树上倍增**。每次询问的时间复杂度 $O(\log n)$。OJ：[P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)

> 题意：给定 $n$ 个结点，$m$ 次询问，问两个结点的最近公共祖先
>
> 思路：当然，求解 LCA 还有其他众多方法，目前只掌握了树上倍增的思路，相对于上述的对路径中所有结点逐个遍历，优化策略就是二进制遍历。当然前提是提前维护好了 `fa[i][j]` 数组，表示 $i$ 号点向上跳 $2^j$ 步后到达的结点。接着就是跳跃的过程了，我们首先需要将两个结点按照倍增的思路向上跳到同一个深度，接下来两个结点同时按照倍增的思路向上跳跃，为了确保求出最近的，我们需要确保在跳跃的步调一致的情况下，两者的祖先始终不相同，那么倍增结束后，两者的父结点就是最近公共祖先，即 `fa[x][k]` 或 `fa[y][k]`
>
> 维护 $fa$ 数组：可以发现，对于 `fa[i][j]`，我们可以通过递推的方式获得，即 `fa[i][j] = fa[fa[i][j-1]][j-1]`，当前结点向上跳跃 $2^j$ 步可以拆分为先向上 $2^{j-1}$ 步，在此基础之上再向上 $2^{j-1}$ 步。于是我们可以采用宽搜的顺序维护 $fa$ 数组。
>
> 时间复杂度：
>
> - 维护 $fa$ 数组时，对于树中的每一个结点，我们都要统计向上跳跃 $[0,\lg N]$ 的所有情况，故时间复杂度为 $O(n \log n)$
>- 跳跃时，每一次询问中，我们都需要对两个结点进行跳跃，时间复杂度是 $O(\log n)$，那么 $m$ 次询问的时间复杂度就是 $O(m\log n)$
> - 总时间复杂度就是：$O((n+m)\log n)$

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 10;

int n, Q, root;
vector<int> G[N];
int fa[N][20], dep[N];
queue<int> q;

void bfs() {
    dep[root] = 1;
    q.push(root);
    while (q.size()) {
        int now = q.front();
        q.pop();
        for (int ch : G[now]) {
            if (dep[ch]) {
                continue;
            }
            dep[ch] = dep[now] + 1;
            fa[ch][0] = now;
            for (int k = 1; k <= 19; k++) {
                fa[ch][k] = fa[fa[ch][k - 1]][k - 1];
            }
            q.push(ch);
        }
    }
}

int lca(int a, int b) {
    if (dep[a] < dep[b]) {
        swap(a, b);
    }
    for (int k = 19; k >= 0; k--) {
        if (dep[fa[a][k]] >= dep[b]) {
            a = fa[a][k];
        }
    }
    if (a == b) {
        return a;
    }
    for (int k = 19; k >= 0; k--) {
        if (fa[a][k] != fa[b][k]) {
            a = fa[a][k], b = fa[b][k];
        }
    }
    return fa[a][0];
}

int main() {
    cin >> n >> Q >> root;
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    bfs();
    while (Q--) {
        int a, b;
        cin >> a >> b;
        cout << lca(a, b) << "\n";
    }
    return 0;
}
```

### T10

> 若一棵二叉树中没有数据域值相同的结点，试设计算法打印二叉树中数据域值为x的结点的所有祖先结点的数据域。如果根结点的数据域值为x或不存在数据域值为x的结点，则什么也不打印。例如对下图所示的二叉树，则打印结点序列为A、C、E。
>
> ![img](https://dwj-oss.oss-cn-nanjing.aliyuncs.com/images/202408081606053.png)

和 $T8$ 类似，只是标记点为指定的点而非叶子结点。时间复杂度 $O(n)$

```cpp
template<class T>
void BinaryTree<T>::dfs(BinaryTreeNode<T>* now, vector<T>& path, 
                        vector<T>& res, T target) {
    if (!now) {
        return;
    }
    path.push_back(now->data);
    if (now->data == target) {
        res = path;
        path.pop_back();
        return;
    }
    dfs(now->lchild, path, res, target);
    dfs(now->rchild, path, res, target);
    path.pop_back();
}
```

### T11

> 已知二叉树存于二叉链表中，试编写一个算法，判断给定二叉树是否为完全二叉树。

直接进行层序遍历，如果当前不是双分支结点，那么同一层的后面的结点都只能是叶子结点。时间复杂度 $O(n)$

```cpp
template<class T>
bool BinaryTree<T>::isCompleteBinaryTree() {
    queue<BinaryTreeNode<T>*> q;
    q.push(root);
    while (q.size()) {
        bool appear = false; // pre appear not double branch node
        vector<BinaryTreeNode<T>*> level;
        while (q.size()) {
            auto now = q.front();
            q.pop();
            if (!now) {
                continue;
            }
            level.push_back(now);
            if (!now->lchild || !now->rchild) {
                appear = true;
            }
            if (appear && (now->lchild || now->rchild)) {
                return false;
            }
        }
        for (auto node: level) {
            q.push(node->lchild);
            q.push(node->rchild);
        }
    }
    return true;
}
```

### T12

> 已知二叉树存于二叉链表中，试编写一个算法计算二叉树的宽度，即同一层中结点数的最大值。

遍历统计即可，深搜宽搜均可。时间复杂度 $O(n)$

```cpp
template<class T>
int BinaryTree<T>::width() {
    int res = 0;
    queue<BinaryTreeNode<T>*> q;
    q.push(root);
    while (q.size()) {
        vector<BinaryTreeNode<T>*> level;
        while (q.size()) {
            auto now = q.front();
            q.pop();
            if (!now) {
                continue;
            }
            level.push_back(now);
        }
        res = max(res, int(level.size()));
        for (auto node: level) {
            q.push(node->lchild);
            q.push(node->rchild);
        }
    }
    return res;
}
```

### T13

> 已知二叉树存于二叉链表中，编写一个递归算法，利用叶结点中空的右链指针域rchild，将所有叶结点自左至右链接成一个单链表，算法返回最左叶结点的地址（链头）

我们只需要设置一个头指针 `head` 用来保存最左叶子结点的地址，再设置一个前驱指针 `pre` 用来保存前一个叶子结点的地址，在遍历二叉树的时候链接叶子结点即可。当然，由于我们此时改变了二叉树的结构，会导致原来的析构函数逻辑出错造成内存泄漏。时间复杂度 $O(n)$

```cpp
template<class T>
void BinaryTree<T>::dfs(BinaryTreeNode<T>* now, 
                        BinaryTreeNode<T>*& pre, 
                        BinaryTreeNode<T>*& head) {
    if (!now) {
        return;
    }
    if (!now->lchild && !now->rchild) {
        if (!head) {
            head = pre = now;
        } else {
            pre->rchild = now;
            pre = now;
        }
        return;
    }
    dfs(now->lchild, pre, head);
    dfs(now->rchild, pre, head);
}
```

## 实验七

### T1

![第七章实验 - 1](https://dwj-oss.oss-cn-nanjing.aliyuncs.com/images/202408081608105.png)

构造函数：带空指针标记的先序遍历序列

```cpp
template<class T>
BinaryTreeNode<T>* BinaryTree<T>::createWithPreTaged(string& pre_of_tag, int& i) {
    T e = pre_of_tag[i++];
    if (e == '#') {
        return nullptr;
    }
    BinaryTreeNode<T>* now = new BinaryTreeNode<T>(e);
    now->lchild = createWithPreTaged(pre_of_tag, i);
    now->rchild = createWithPreTaged(pre_of_tag, i);
    return now;
}
```

构造函数：带空指针标记的后序遍历序列

```cpp
template<class T>
BinaryTreeNode<T>* BinaryTree<T>::createWithPostTaged(string& post_of_tag, int& i) {
    T e = post_of_tag[i--];
    if (e == '#') {
        return nullptr;
    }
    BinaryTreeNode<T>* now = new BinaryTreeNode<T>(e);
    now->rchild = createWithPostTaged(post_of_tag, i);
    now->lchild = createWithPostTaged(post_of_tag, i);
    return now;
}
```

构造函数：用先序和中序序列。构造的逻辑仍然是递归，我们根据先序序列构造根结点，并在中序序列中找到对应的结点将先序序列划分为「根、左子树、右子树」三个部分，将中序序列划分为「左子树、根、右子树」三个部分，进而递归构造左右子树。当然，我们假设树中结点的值各不相同，否则无法唯一确定左右子树。为了**简化逻辑**，构造时传递的先序序列和中序序列均为重新赋值出来的参数，这导致代码在递归时的时间开销增大，因为需要不断的拷贝构造字符串。从效率角度的最佳实践是传递原始序列的引用附加指针来划定当前子树对应序列的区间。

```cpp
template<class T>
BinaryTreeNode<T>* BinaryTree<T>::createWithPreMid(string pre, string mid) {
    if (pre.size() == 0) {
        return nullptr;
    }
    BinaryTreeNode<T>* now_root = new BinaryTreeNode<T>(pre[0]);
    string mid_left, mid_right;
    for (int i = 0; i < mid.size(); i++) {
        if (mid[i] == pre[0]) {
            mid_left = mid.substr(0, i);
            mid_right = mid.substr(i + 1);
            break;
        }
    }
    int len_left = mid_left.size();
    string pre_left = pre.substr(1, len_left);
    string pre_right = pre.substr(len_left + 1);
    now_root->lchild = createWithPreMid(pre_left, mid_left);
    now_root->rchild = createWithPreMid(pre_right, mid_right);
    return now_root;
}
```

构造函数：用后序和中序序列

```cpp
template<class T>
BinaryTreeNode<T>* BinaryTree<T>::createWithMidPost(string mid, string post) {
    if (post.size() == 0) {
        return nullptr;
    }
    BinaryTreeNode<T>* now_root = new BinaryTreeNode<T>(post.back());
    string mid_left, mid_right;
    for (int i = 0; i < mid.size(); i++) {
        if (mid[i] == post.back()) {
            mid_left = mid.substr(0, i);
            mid_right = mid.substr(i + 1);
            break;
        }
    }
    int len_left = mid_left.size();
    int len_right = mid_right.size();
    string post_left = post.substr(0, len_left);
    string post_right = post.substr(len_left, len_right);
    now_root->lchild = createWithMidPost(mid_left, post_left);
    now_root->rchild = createWithMidPost(mid_right, post_right);
    return now_root;
}
```

析构函数：

```cpp
template<class T>
void BinaryTree<T>::decreate(BinaryTreeNode<T>* now) {
    if (!now) return;
    decreate(now->lchild);
    decreate(now->rchild);
    delete now;
}
```

遍历：以前序遍历为例

```cpp
template<class T>
void BinaryTree<T>::prePrint(BinaryTreeNode<T>* now) {
    if (!now) {
        return;
    }
    cout << now->data;
    prePrint(now->lchild);
    prePrint(now->rchild);
}
```

计算二叉树的高度：

```cpp
template<class T>
int BinaryTree<T>::hight(BinaryTreeNode<T>* now) {
    if (!now) {
        return 0;
    }
    return max(hight(now->lchild), hight(now->rchild)) + 1;
}
```

交换左右子树：

```cpp
template<class T>
void BinaryTree<T>::dfs(BinaryTreeNode<T>* now) {
    if (!now) {
        return;
    }
    swap(now->lchild, now->rchild);
    dfs(now->lchild);
    dfs(now->rchild);
}
```

### T2

![第七章实验 - 2](https://dwj-oss.oss-cn-nanjing.aliyuncs.com/images/202408081608671.png)

### T3

![第七章实验 - 3](https://dwj-oss.oss-cn-nanjing.aliyuncs.com/images/202408081608481.png)
