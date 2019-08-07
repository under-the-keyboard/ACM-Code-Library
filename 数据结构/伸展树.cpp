const int inf = "Edit"
const int maxn = "Edit";
struct SplayTree {
  int rt, tot;
  int fa[maxn], son[maxn][2];
  int val[maxn], cnt[maxn];
  int sz[maxn];
  bool lazy[maxn];
  void Pull(int o) {
    sz[o] = sz[son[o][0]] + sz[son[o][1]] + cnt[o];
  }
  void Push(int o) {
    if (lazy[o]) {
      std::swap(son[o][0], son[o][1]);
      if (son[o][0]) lazy[son[o][0]] ^= 1;
      if (son[o][1]) lazy[son[o][1]] ^= 1;
      lazy[o] = 0;
    }
  }
  bool Get(int o) {
    return o == son[fa[o]][1];
  }
  void Clear(int o) {
    son[o][0] = son[o][1] = fa[o] = val[o] = sz[o] = cnt[o] = 0;
  }
  void Rotate(int o) {
    int p = fa[o], q = fa[p], ck = Get(o);
    son[p][ck] = son[o][ck ^ 1];
    fa[son[o][ck ^ 1]] = p;
    son[o][ck ^ 1] = p;
    fa[p] = o; fa[o] = q;
    if (q) son[q][p == son[q][1]] = o;
    Pull(p); Pull(o);
  }
  void Splay(int o) {
    for (int f = fa[o]; f = fa[o], f; Rotate(o))
      if (fa[f]) Rotate(Get(o) == Get(f) ? f : o);
    rt = o;
  }
  // 旋转o节点到节点tar
  void Splay(int o, int tar = 0) {
    for (int cur = fa[o]; (cur = fa[o]) != tar; Rotate(o)) {
      Pull(fa[cur]); Pull(cur); Pull(o);
      if (fa[cur] != tar) {
        if (Get(o) == Get(cur)) Rotate(cur);
        else Rotate(o);
      }
    }
    if (!tar) rt = o;
  }
  void Insert(int x) {
    if (!rt) {
      val[++tot] = x;
      cnt[tot]++;
      rt = tot;
      Pull(rt);
      return;
    }
    int cur = rt, f = 0;
    while (true) {
      if (val[cur] == x) {
        cnt[cur]++;
        Pull(cur); Pull(f);
        Splay(cur);
        break;
      }
      f = cur;
      cur = son[cur][val[cur] < x];
      if (!cur) {
        val[++tot] = x;
        cnt[tot]++;
        fa[tot] = f;
        son[f][val[f] < x] = tot;
        Pull(tot); Pull(f);
        Splay(tot);
        break;
      }
    }
  }
  int GetRank(int x) {
    int ans = 0, cur = rt;
    while (true) {
      if (x < val[cur]) cur = son[cur][0];
      else {
        ans += sz[son[cur][0]];
        if (x == val[cur]) {
          Splay(cur);
          return ans + 1;
        }
        ans += cnt[cur];
        cur = son[cur][1];
      }
    }
  }
  int GetKth(int k) {
    int cur = rt;
    while (true) {
      if (son[cur][0] && k <= sz[son[cur][0]]) cur = son[cur][0];
      else {
        k -= cnt[cur] + sz[son[cur][0]];
        if (k <= 0) return cur;
        cur = son[cur][1];
      }
    }
  }
  // 获取以r为根节点Splay Tree中的第k大个元素在Splay Tree中的位置
  int Kth(int r, int k) {
    Pull(r);
    int tmp = sz[son[r][0]] + 1;
    if (tmp == k) return r;
    if (tmp > k) return Kth(son[r][0], k);
    else return Kth(son[r][1], k - tmp);
  }
  // Insert之后求前驱后继
  int GetPrev() {
    int cur = son[rt][0];
    while (son[cur][1]) cur = son[cur][1];
    return cur;
  }
  int GetNext() {
    int cur = son[rt][1];
    while (son[cur][0]) cur = son[cur][0];
    return cur;
  }
  // 获取Splay Tree中以o为根节点子树的最小值位置
  int GetMin(int o) {
    Pull(o);
    while (son[o][0]) {
      o = son[o][0];
      Pull(o);
    }
    return o;
  }
  // 获取Splay Tree中以o为根节点子树的最大值位置
  int GetMax(int o) {
    Pull(o);
    while (son[o][1]) {
      o = son[o][1];
      Pull(o);
    }
    return o;
  }
  void Delete(int x) {
    GetRank(x);
    if (cnt[rt] > 1) {
      cnt[rt]--;
      Pull(rt);
      return;
    }
    if (!son[rt][0] && !son[rt][1]) {
      Clear(rt);
      rt = 0;
      return;
    }
    if (!son[rt][0]) {
      int cur = rt;
      rt = son[rt][1];
      fa[rt] = 0;
      Clear(cur);
      return;
    }
    if (!son[rt][1]) {
      int cur = rt;
      rt = son[rt][0];
      fa[rt] = 0;
      Clear(cur);
      return;
    }
    int p = GetPrev(), cur = rt;
    Splay(p);
    fa[son[cur][1]] = p;
    son[p][1] = son[cur][1];
    Clear(cur);
    Pull(rt);
  }
  /* 维护数组操作 */
  // 翻转Splay Tree中l~r区间
  void Reverse(int l, int r) {
    int o = Kth(rt, l), Y = Kth(rt, r);
    Splay(o, 0); Splay(Y, o);
    lazy[son[Y][0]] ^= 1;
  }
  // 建立Splay Tree
  void Build(int l, int r, int o) {
    if (l > r) return;
    int m = (l + r) >> 1;
    Build(l, m - 1, m);
    Build(m + 1, r, m);
    fa[m] = o;
    val[m] = /* 节点权值 */;
    lazy[m] = 0;
    Push(m);
    if (m < o) son[o][0] = m;
    else son[o][1] = m;
  }
  // 输出Splay Tree
  void Print(int o) {
    Pull(o);
    if (son[o][0]) Print(son[o][0]);
    // 哨兵节点判断
    if (val[o] != -inf && val[o] != inf) printf("%d ", val[o]);
    if (val[son[o][1]]) Print(son[o][1]);
  }
};
