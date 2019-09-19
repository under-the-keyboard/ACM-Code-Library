const int maxn = 1e5 + 5;
const int inf = 0x3f3f3f3f;
// prim
struct ac{
    int v, c;
};
vector<ac> g[maxn];
int vis[maxn], dis[maxn];
void init(int n) {
    for (int i = 0; i <= n; ++i) g[i].clear();
}
int prim(int s, int n) {
    fill(dis, dis+n+1, inf);
    fill(vis, vis+n+1, 0);
    int sum = 0;
    dis[s] = 0;
    for (int i = 1; i <= n; ++i) {
        int u = -1, MIN = inf;
        for (int j = 1; j <= n; ++j) {
            if (vis[j] || dis[j] >= MIN) continue;
            u = j;
            MIN = dis[j];
        }
        vis[u] = 1;
        sum += MIN;
        for (int j = 0; j < (int)g[u].size(); ++j) {
            int v = g[u][j].v;
            int c = g[u][j].c;
            if (vis[v] || dis[v] <= c) continue;
            dis[v] = c;
        }
    } 
    return sum;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int u, v, c, n;
    while (scanf("%d", &n), n) {
        init(n);
        for (int i = 0; i < (n-1)*n/2; ++i) {
            scanf("%d %d %d", &u, &v, &c);
            g[u].push_back((ac){v, c});
            g[v].push_back((ac){u, c});
        }
        printf("%d\n", prim(1, n));
    }
    return 0;
}
// kruskal
struct ac{
    int u, v, c;
    bool operator < (const ac &t) {
        return c < t.c;
    }
}edge[maxn];
int pre[maxn];
void init(int n) {
    for (int i = 0; i <= n; ++i) pre[i] = i;
}
int find(int x) {
    // return (x == pre[x]) ? x : pre[x] = find(pre[x]);
    int t = x, tmp;
    while (x != pre[x]) x = pre[x];
    while (t != pre[t]) { // 路径压缩
        tmp = pre[t];
        pre[t] = x;
        t = tmp;
    }
    return x;
}
void join(int fx, int fy) {
    if (fx == fy) return;
    if (fx > fy) swap(fx, fy);
    pre[fy] = fx;
}