const int maxn = "Edit";
std::vector<int> g[maxn];
int in[maxn], out[maxn];
int ele[maxn];
int dfs_clock;
void DfsSeq(int u, int p) {
  in[u] = ++dfs_clock;
  ele[dfs_clock] = u;
  for (int &v : g[u]) {
    if (v == p) continue;
    DfsSeq(v, u);
  }
  out[u] = dfs_clock;
}