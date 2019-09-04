const int maxn = "Edit";
const int maxa = "Edit";
// 动态莫队算法求区间不同数字数量（支持单点修改）
struct MoCap {
  int n, m;
  int block;
  int arr[maxn];
  struct Query { int l, r, t, id; };
  Query qry[maxn];
  struct Update { int pos, val; };
  Update upd[maxn];
  int qrytot, updtot;
  int cnt[maxa];
  int cur;
  int ans[maxn];
  void Add(int idx) {
    cur += (++cnt[arr[idx]] == 1);
  }
  void Sub(int idx) {
    cur -= (--cnt[arr[idx]] == 0);
  }
  void Modify(int t, int i) {
    if (upd[t].pos >= qry[i].l && upd[t].pos <= qry[i].r) Sub(upd[t].pos);
    std::swap(upd[t].val, arr[upd[t].pos]);
    if (upd[t].pos >= qry[i].l && upd[t].pos <= qry[i].r) Add(upd[t].pos);
  }
  void Solve() {
    scanf("%d%d", &n, &m);
    block = std::pow(n, 2. / 3);
    for (int i = 1; i <= n; ++i) scanf("%d", &arr[i]);
    for (int i = 1; i <= m; ++i) {
      char op; getchar();
      scanf("%c", &op);
      if (op == 'Q') {
        int l, r; scanf("%d%d", &l, &r);
        qry[++qrytot] = (Query){l, r, updtot, qrytot};
      }
      else {
        int p, v; scanf("%d%d", &p, &v);
        upd[++updtot] = (Update){p, v};
      }
    }
    std::sort(qry + 1, qry + qrytot + 1, [&](Query k1, Query k2) {
      if (k1.l / block != k2.l / block) return k1.l < k2.l;
      if (k1.r / block != k2.r / block) return k1.r < k2.r;
      return k1.t < k2.t;
    });
    int l = 1, r = 0, t = 0;
    for (int i = 1; i <= qrytot; ++i) {
      while (l < qry[i].l) Sub(l++);
      while (l > qry[i].l) Add(--l);
      while (r < qry[i].r) Add(++r);
      while (r > qry[i].r) Sub(r--);
      while (t < qry[i].t) Modify(++t, i);
      while (t > qry[i].t) Modify(t--, i);
      ans[qry[i].id] = cur;
    }
    for (int i = 1; i <= qrytot; ++i) printf("%d\n", ans[i]);
  }
}mo;

