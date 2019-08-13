const int maxn = "Edit";
struct BitTree {
  int arr[maxn];
  void Init() {
    memset(arr, 0, sizeof(arr));
  }
  void Modify(int x, int v) {
    while (x < maxn) {
      arr[x] += v;
      x += x & (-x);
    }
  }
  int Query(int x) {
    int ret = 0;
    while (x > 0) {
      ret += arr[x];
      x -= x & (-x);
    }
    return ret;
  }
  int GetRank(int v) {
    int ret = 1;
    --v;
    while (v) {
      ret += arr[v];
      v -= v & (-v);
    }
    return ret;
  }
  int GetKth(int k) { // kth min
    int ret = 0, cnt = 0, max = log2(maxn);
    for (int i = max; i >= 0; --i) {
      ret += (1 << i);
      if (ret >= maxn || cnt += arr[ret] >= k) ret -= (1 << i);
      else cnt += arr[ret];
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
