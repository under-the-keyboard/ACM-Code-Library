// 次短路 : 1次Dijkstra维护次短路；2次Dijkstra更新最短路；
const int maxn = 1e5 + 5;
const int inf = 0x3f3f3f3f;
struct ac{
    int v, c;
    bool operator <(const ac &t) const {
        return t.c < c;
    }
};
vector<ac> g[maxn];
int dis[2][maxn];
void add(int u, int v, int c) {
    g[u].push_back((ac){v, c});
    g[v].push_back((ac){u, c});
}
void Dijstra(int s) {
    fill(dis[0], dis[0]+maxn*2, inf);
    dis[0][s] = 0;
    priority_queue<ac> que;
    que.push((ac){s, 0});
    while (!que.empty()) {
        ac f = que.top();
        que.pop();
        int u = f.v;
        if (dis[1][u] < f.c) continue;
        for (int i = 0; i < (int)g[u].size(); ++i) {
            int v = g[u][i].v;
            int c = f.c + g[u][i].c;
            if (dis[0][v] > c) {
                swap(dis[0][v], c); // swap
                que.push((ac){v, dis[0][v]});
            }
            if (dis[0][v] < c && dis[1][v] > c) {
                dis[1][v] = c;
                que.push((ac){v, c});
            }
        }
    }
}
// k短路: 首先计算终点到其他点的距离,然后A*算法求k短路
struct ac{
    int v, c;
};
vector<ac> g[maxn];
int dis[maxn], vis[maxn];
struct cmp{
    bool operator() (ac &t1, ac& t2) {
        return t1.c > t2.c; // 升序
    }
};
struct cmp1{
    bool operator() (ac &t1, ac& t2) {
        return t1.c + dis[t1.v] > t2.c + dis[t2.v]; // 降序
    }
};
void add(int u, int v, int c) { // 有向图需要建反向图
    g[u].push_back((ac){v, c});
    g[v].push_back((ac){u, c});
}
void Dijkstra(int s) {
    fill(dis, dis+maxn, inf);
    fill(vis, vis+maxn, 0);
    dis[s] = 0;
    priority_queue<ac, vector<ac>, cmp> que;
    que.push((ac){s, 0});
    while (!que.empty()) {
        ac f = que.top();
        que.pop();
        int u = f.v;
        if (dis[u] < f.c || vis[u]) continue;
        vis[u] = 1;
        for (int i = 0; i < (int)g[u].size(); ++i) {
            int v = g[u][i].v;
            int c = f.c + g[u][i].c;
            if (dis[v] > c) {
                dis[v] = c;
                que.push((ac){v, c});
            }
        }
    }
}
int Astar(int k, int s, int e) {
    if (dis[s] == inf) return -1;
    int cnt = 0;
    priority_queue<ac, vector<ac>, cmp1> que;
    que.push((ac){s, 0});
    while (!que.empty()) {
        ac f = que.top();
        que.pop();
        int u = f.v;
        if (u == e) cnt++;
        if (cnt == k) return f.c;
        for (int i = 0; i < (int)g[u].size(); ++i) {
            que.push((ac){g[u][i].v, f.c + g[u][i].c});
        }
    }
    return -1;
}