const int maxn = "Edit";
const int maxlog = "Edit";
int n;
int max[maxn][maxlog], min[maxn][maxlog];
void Init(int arr[]) {
  int m = log2(n) + 1;
  for (int i = 1; i <= n; ++i) max[i][0] = min[i][0] = arr[i];
  for (int j = 1; j < m; ++j) {
    for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
      max[i][j] = std::max(max[i][j - 1], max[i + (1 << (j - 1))][j - 1]);
      min[i][j] = std::min(min[i][j - 1], min[i + (1 << (j - 1))][j - 1]);
    }
  }
}
// 区间[l,r]最大值
int QueryMax(int l, int r) {
  int k = log2(r - l + 1);
  return std::max(max[l][k], max[r - (1 << k) + 1][k]);
}
// 区间[l,r]最小值
int QueryMin(int l, int r) {
  int k = log2(r - l + 1);
  return std::min(min[l][k], min[r - (1 << k) + 1][k]);
}