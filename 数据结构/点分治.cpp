const int maxn = "Edit";
struct Edge { int v, c; };
std::vector<Edge> g[maxn];
int sum, rt;
int sz[maxn], max[maxn];
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
void GetInfo(int u, int p) {
  /* ... */;
  for (auto &e : g[u]) {
    int v = e.v, c = e.c;
    if (v == p || vis[v]) continue;
    dis[v] = /* dis[u] + c */;
    GetInfo(v, u);
  } 
}
int Cal(int u, int c) {
  dis[u] = /* ... */;
  /* ... */
  GetInfo(u, 0);
  return /* ... */;
}
void Dfs(int u) {
  /* + Cal */
  vis[u] = true;
  for (auto &e : g[u]) {
    int v = e.v, c = e.c;
    if (vis[v]) continue;
    /* - Cal */
    rt = 0;
    sum = sz[v];
    max[rt] = n;
    FindRoot(v, u);
    Dfs(rt);
  }
}
