const int maxn = "Edit";
struct SegTree {
  int n;
  long long sum[maxn * 4], lazy[maxn * 4];
  long long Unite(const long long &k1, const long long &k2) {
    return k1 + k2;
  }
  void Pull(int o) {
    sum[o] = Unite(sum[o * 2], sum[o * 2 + 1]);
  }
  void Push(int o, int l, int r) {
    int m = (l + r) / 2;
    if (lazy[o] != 0) {
      sum[o * 2] += (m - l + 1) * lazy[o];
      sum[o * 2 + 1] += (r - m) * lazy[o];
      lazy[o * 2] += lazy[o];
      lazy[o * 2 + 1] += lazy[o];
      lazy[o] = 0;
    }
  }
  void Build(int o, int l, int r, long long arr[]) {
    sum[o] = lazy[o] = 0;
    if (l == r) {
      sum[o] = arr[l];
      return;
    }
    int m = (l + r) / 2;
    Build(o * 2, l, m, arr);
    Build(o * 2 + 1, m + 1, r, arr);
    Pull(o);
  }
  void Init(int _n, long long arr[]) {
    n = _n;
    Build(1, 1, n, arr);
  }
  void Modify(int o, int l, int r, int ll, int rr, long long v) {
    if (ll <= l && rr >= r) {
      sum[o] += (r - l + 1) * v;
      lazy[o] += v;
      return;
    }
    Push(o, l, r);
    int m = (l + r) / 2;
    if (ll <= m) Modify(o * 2, l, m, ll, rr, v);
    if (rr > m) Modify(o * 2 + 1, m + 1, r, ll, rr, v);
    Pull(o);
  }
  void Modify(int ll, int rr, long long v) {
    Modify(1, 1, n, ll, rr, v);
  }
  long long Query(int o, int l, int r, int ll, int rr) {
    if (ll <= l && rr >= r) return sum[o];
    Push(o, l, r);
    int m = (l + r) / 2;
    long long ret = 0;
    if (ll <= m) ret = Unite(ret, Query(o * 2, l, m, ll, rr));
    if (rr > m) ret = Unite(ret, Query(o * 2 + 1, m + 1, r, ll, rr));
    return ret;
  }
  long long Query(int ll, int rr) {
    return Query(1, 1, n, ll, rr);
  }
};