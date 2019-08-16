const int maxn = "Edit";
struct BitTree {
  int tree[maxn];
  void Init() {
    memset(tree, 0, sizeof(tree));
  }
  void Modify(int x, int v) {
    for (int i = x; i < maxn; i += i & (-i))
      tree[i] += v;
  }
  int Query(int x) {
    int ret = 0;
    for (int i = x; i > 0; i -= i & (-i))
      ret += tree[i];
    return ret;
  }
  int GetRank(int v) {
    int ret = 1;
    --v;
    for (int i = v; i > 0; i -= i & (-i))
      ret += tree[i];
    return ret;
  }
  int GetKth(int k) { // kth min
    int ret = 0, cnt = 0, max = log2(maxn);
    for (int i = max; i >= 0; --i) {
      ret += (1 << i);
      if (ret >= maxn || cnt += tree[ret] >= k) ret -= (1 << i);
      else cnt += tree[ret];
    }
    return ++ret;
  }
  int GetPrev(int v) {
    return GetKth(GetRank(v) - 1);
  }
  int GetNext(int v) {
    return GetKth(GetRank(v) + 1);
  }
};