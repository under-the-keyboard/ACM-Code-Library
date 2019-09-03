const int maxn = "Edit";
struct Edge { int v, c; };
std::vector<Edge> g[maxn];
int sum, rt;
int max[maxn], sz[maxn];
bool vis[maxn];
void FindRoot(int u, int p) {
  sz[u] = 1; max[u] = 0;
  for (auto &e : g[u]) {
    int v = e.v;
    if (v == p || vis[v]) continue;
    FindRoot(v, u);
    sz[u] += sz[v];
    max[u] = std::max(max[u], sz[v]);
  }
  max[u] = std::max(max[u], sum - max[u]);
  if (max[u] < max[rt]) rt = u;
}
void Dfs(int u) {
  /* Solve */
  vis[u] = true;
  for (auto &e : g[u]) {
    int v = e.v, c = e.c;
    if (vis[v]) continue;
    /* Solve */
    rt = 0;
    sum = sz[v];
    max[rt] = n;
    FindRoot(v, u);
    Dfs(rt);
  }
}
