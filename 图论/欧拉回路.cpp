vector<pair<int,int>> g[maxn]; // 双向边
pair<int,int> edge[maxn];
int now[maxn], vis[maxn];
vector<int> tour;
void dfs(int u) {
    for (; now[u] < (int)g[u].size(); ++now[u]) {
        int v, id;
        tie(v, id) = g[u][now[u]];
        if (vis[id]) continue;
        vis[id] = 1;
        dfs(v); // return 不删标记
    }
    tour.push_back(u); // 无路可走加到tour
}
