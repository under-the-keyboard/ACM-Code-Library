const int maxn = "Edit";
struct BitTree2D {
  int tree[4][maxn][maxn];
  void Modify(int x, int y, int v) {
    for (int i = x; i < maxn; i += i & (-i)) {
      for (int j = y; j < maxn; j += j & (-j)) {
        tree[0][i][j] += v;
        tree[1][i][j] += v * y;
        tree[2][i][j] += v * x;
        tree[3][i][j] += v * x * y;
      }
    }
  }
  int Query(int x, int y) {
    int ret = 0;
    for (int i = x; i > 0; i -= i & (-i)) {
      for (int j = y; j > 0; j -= j & (-j)) {
        ret += tree[0][i][j] * (x + 1) * (y + 1);
        ret -= tree[1][i][j] * (x + 1);
        ret -= tree[2][i][j] * (y + 1);
        ret += tree[3][i][j];
      }
    }
    return ret;
  }
};
