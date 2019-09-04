const int maxn = "Edit";
const int maxa = "Edit";
// 静态莫队算法求区间不同数字数量
struct MoCap {
  int n, m;
  int block;
  int arr[maxn];
  struct Query { int l, r, id; };
  Query qry[maxn];
  int cnt[maxa];
  int cur;
  int ans[maxn];
  void Add(int idx) {
    cur += (++cnt[arr[idx]] == 1);
  }
  void Sub(int idx) {
    cur -= (--cnt[arr[idx]] == 0);
  }
  void Solve() {
    scanf("%d%d", &n, &m);
    block = std::pow(n, 2. / 3);
    for (int i = 1; i <= n; ++i) scanf("%d%d", &arr[i]);
    for (int i = 1; i <= m; ++i) {
      scanf("%d%d", &qry[i].l, &qry[i].r);
      qry[i].id = i;
    }
    std::sort(qry + 1, qry + m + 1, [&](Query k1, Query k2) {
      if (k1.l / block != k2.l / block) return k1.l < k2.l;
      return k1.r < k2.r;
    });
    int l = 1, r = 0;
    for (int i = 1; i <= m; ++i) {
      while (l < qry[i].l) Sub(l++);
      while (l > qry[i].l) Add(--l);
      while (r < qry[i].r) Add(++r);
      while (r > qry[i].r) Sub(r--);
      ans[qry[i].id] = cur;
    }
    for (int i = 1; i <= m; ++i) printf("%d\n", ans[i]);
  }
}mo;
