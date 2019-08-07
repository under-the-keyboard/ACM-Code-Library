const int maxn = "Edit";
const int maxlog = "Edit";
int n;
std::vector<int> g[maxn];
int ele[maxn * 2], dep[maxn * 2];
int fi[maxn], fa[maxn];
int tot;
int dp[maxn * 2][maxlog];
void Dfs(int u, int p, int d) {
  ele[++tot] = u;
  fi[u] = tot;
  dep[tot] = d;
  fa[u] = p;
  for (int &v : g[u]) {
    if (v == p) continue;
    Dfs(v, u, d + 1);
    ele[++tot] = u;
    dep[tot] = d;
  }
}
void Init() {
  for(int i = 1; i <= 2 * n - 1; ++i) dp[i][0] = i;
  for (int j = 1; (1 << j) <= 2 * n - 1; ++j)
    for (int i = 1; i + (1 << j) - 1 <= 2 * n - 1; ++i)
      dp[i][j] = dep[dp[i][j - 1]] < dep[dp[i + (1 << j - 1)][j - 1]] ? dp[i][j - 1] : dp[i + (1 << (j - 1))][j - 1];
}
int Query(int l, int r) {
  if (l > r) std::swap(l, r);
  int len = log2(r - l + 1);
  return dep[dp[l][len]] <= dep[dp[r - (1 << len) + 1][len]] ? dp[l][len] : dp[r - (1 << len) + 1][len];
}
int GetLCA(int u, int v) {
  return ele[Query(fi[u], fi[v])];
}