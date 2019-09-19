// 正边权最短路
const int maxn = 1e5 + 5;
const int inf = 0x3f3f3f3f;
struct ac{
    int v, c;
    bool operator <(const ac &t) const{
        return t.c < c;
    }
};
// struct cmp{
//     bool operator() (ac &t1, ac& t2) {
//         return t1.c > t2.c; // 升序
//     }
// };
vector<ac> g[maxn];
int dis[maxn], vis[maxn], path[maxn];
void add(int u, int v, int c) {
    g[u].push_back((ac){v, c});
    g[v].push_back((ac){u, c});
}
void dfs(int now, int& len, char *str) {
    if (now == -1) return;
    dfs(path[now], len, str);
    str[len++] = '0' + now;
}
int check(int x, int y) { // 字典序最小路径
    char s1[1000], s2[1000];
    int len = 0; dfs(x, len, s1); s1[len] = 0;
    len = 0; dfs(y, len, s2); s2[len] = 0;
    return (strcmp(s1, s2) == 1);

}
void print(int now) {
    if (path[now] == -1) {
        printf("%d", now);
        return;
    }
    print(path[now]);
    printf("->%d", now);
}
int Dijkstra(int s, int e, int n) { // 堆优化  O(nlogn)
    fill(dis, dis+n+1, inf);
    fill(vis, vis+n+1, 0);
    path[s] = -1;
    dis[s] = 0;
    priority_queue<ac> que;
    que.push((ac){s, 0});
    while (!que.empty()) {
        ac f = que.top();
        que.pop();
        int u = f.v;
        if (dis[u] < f.c || vis[u]) continue;
        if (u == e) return f.c;
        vis[u] = 1;
        for (int i = 0; i < (int)g[u].size(); ++i) {
            int v = g[u][i].v;
            int c = f.c + g[u][i].c;
            if (dis[v] > c) {
                dis[v] = c;
                path[v] = u;
                que.push((ac){v, c});
            }else if (dis[v] == c && check(v, u)) path[v] = u;
        }
    }
    return -1;
}
int Dijkstra(int s, int e, int n) { // 普通 O(n^2)
    fill(dis, dis+n+1, inf);
    fill(vis, vis+n+1, 0);
    path[s] = -1;
    dis[s] = 0;
    for (int i = 1; i <= n; ++i) {
        int u = -1, MIN = inf;
        for (int j = 1; j <= n; ++j) {
            if (!vis[j] && MIN > dis[j]) {
                MIN = dis[j];
                u = j;
            }
        }
        if (u == -1) return -1;
        if (u == e) return MIN;
        vis[u] = 1;
        for (int j = 0; j < (int)g[u].size(); ++j) {
            int v = g[u][j].v;
            int c = MIN + g[u][j].c;
            if (vis[v]) continue;
            if (dis[v] > c) {
                dis[v] = c;
                path[v] = u;
            }else if(dis[v] == c && check(v, u)) path[v] = u;
        }
    }
    return -1;
}
