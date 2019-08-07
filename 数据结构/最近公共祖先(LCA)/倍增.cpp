const int maxn = "Edit";
const int maxlog = "Edit";
int n, k; // k = log2(n) + 1
std::vecotr<int> g[maxn];
int anc[maxn][maxlog];
int dep[maxn];
// 从根节点开始深搜预处理
void Dfs(int u, int p, int d) {
  anc[u][0] = p;
  dep[u] = d;
  for (int &v : g[u]) {
    if (v == p) continue;
    Dfs(v, u, d + 1);
  }
}
void Swim(int &u, int h) {
  for (int i = 0; h > 0; ++i) {
    if (h & 1) u = anc[u][i];
    h >>= 1;
  }
}
int GetLCA(int u, int v) {
  if (dep[u] < dep[v]) std::swap(u, v);
  Swim(u, dep[u] - dep[v]);
  if (u == v) return v;
  for (int i = k - 1; i >= 0; --i) {
    if (anc[u][i] != anc[v][i]) {
      u = anc[u][i];
      v = anc[v][i];
    }
  }
  return anc[u][0];
}