const int maxn = "Edit";
int n;
long long val[maxn];
int fa[maxn], dep[maxn];
int sz[maxn], son[maxn];
int rk[maxn], top[maxn];
int id[maxn];
int dfs_clock;
std::vector<int> g[maxn];
void Dfs1(int u, int p, int d) {
  fa[u] = p;
  dep[u] = d;
  sz[u] = 1;
  for (int &v : g[u]) {
    if (v == p) continue;
    Dfs1(v, u, d + 1);
    sz[u] += sz[v];
    if (sz[v] > sz[son[u]]) son[u] = v;
  }
}
Dfs2(int u, int tp) {
  top[u] = tp;
  id[u] = ++dfs_clock;
  rk[dfs_clock] = u;
  if (!son[u]) return;
  Dfs2(son[u], tp);
  for (int &v : g[u]) {
    if (v == son[u] || v == fa[u]) continue;
    Dfs2(v, v);
  }
}
long long Modify(int u, int v, long long c) {
  while (top[u] != top[v]) {
    if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
    /* modify c from [id[top[u]], id[u]] in val */
    u = fa[top[u]];
  }
  if (id[u] > id[v]) std::swap(u, v);
  /* modify c from [id[u], id[v]] in val */
}
long long Query(int u, int v) {
  long long ret = 0;
  while (top[u] != top[v]) {
    if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
    ret += /* query from [id[top[u]], id[u]] in val */
    u = fa[top[u]];
  }
  if (id[u] > id[v]) std::swap(u, v);
  ret += /* query from [id[u], id[v]] in val */
  return ret;
}