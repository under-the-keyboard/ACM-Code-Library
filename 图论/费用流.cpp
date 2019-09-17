// SPFA
int path[maxn], dis[maxn], head[maxn], vis[maxn], cnt;
void init() {
    cnt = 0;
    memset(head, -1, sizeof(head));
}
struct ac{
    int v, c, cost, nex;
}edge[maxn << 10]; // 根据题目要求计算 
void addedge(int u, int v, int c, int cost) {
    // 正向建边
    edge[cnt] = {v, c, cost, head[u]};
    head[u] = cnt++;
    // 反向建边
    edge[cnt] = {u, 0, -cost, head[v]};
    head[v] = cnt++;
}
int spfa(int s, int e) {
    memset(vis, 0, sizeof(vis));
    memset(dis, inf, sizeof(dis)); // 记录从s点出发到每个点的费用和最小值
    memset(path, -1, sizeof(path)); // 记录更新当前点的边在edge中的下标
    queue<int> que;
    que.push(s);
    dis[s] = 0;
    vis[s] = 1;
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        vis[u] = 0;
        // 遍历u的所有出边
        for (int i = head[u]; i != -1; i = edge[i].nex) {
            int v = edge[i].v;
            int c = edge[i].c;
            int cost = edge[i].cost;
            // 判断是否更新v点
            if (dis[v] > dis[u] + cost && c > 0) {
                dis[v] = dis[u] + cost; // 更新最小费用
                path[v] = i;
                if (vis[v]) continue;
                vis[v] = 1;
                que.push(v);
            }
        }
    }
    return dis[e] != inf; // 判断s能否到达e
}
int MincostMaxflow(int s, int e, int &cost) {
    int maxflow = 0;
    while (spfa(s, e)) { // 搜先spfa看是否存在增广路，如果存在求一条费用和最小的一条
        int flow = inf; 
        // 遍历增广路上的边，取最小的流量flow
        // path存的是那条边更新到这个点, i = 这个点在edge中的下标
        // edge[i^1].v 通过反向边得到前驱节点
        for (int i = path[e]; i != -1; i = path[edge[i^1].v]) {
            flow = min(flow, edge[i].c); // 取最小的流量
        }
        // 得到最小流量flow之后，更改正反向的流量
        for (int i = path[e]; i != -1; i = path[edge[i^1].v]) {
            edge[i].c -= flow;
            edge[i^1].c += flow;
            cost += flow * edge[i].cost;
        }
        maxflow += flow;
    }
    return maxflow; // 返回最大流
}
// Dijkstra + 链式
#define pii pair<int,int>
int preE[maxn], preV[maxn], dis[maxn], head[maxn], vis[maxn], h[maxn], cnt;
void init() {
    cnt = 0;
    memset(head, -1, sizeof(head));
}
struct ac{
    int v, c, cost, nex;
}edge[maxn << 2];
void addedge(int u, int v, int c, int cost) {
    edge[cnt] = {v, c, cost, head[u]};
    head[u] = cnt++;
    edge[cnt] = {u, 0, -cost, head[v]};
    head[v] = cnt++;
}
int Dijkstra(int s, int e) {
    memset(dis, inf, sizeof(dis));
    preE[s] = -1, dis[s] = 0;
    priority_queue<pii, vector<pii>, greater<pii> >que;
    que.push(pii(0, s));
    while (!que.empty()) {
        pii top = que.top();
        que.pop();
        int u = top.second;
        if (dis[u] < top.first) continue;
        for (int i = head[u]; i != -1; i = edge[i].nex) {
            int v = edge[i].v;
            int cost = edge[i].cost;
            int c = edge[i].c;
            if (c > 0 && dis[v] > dis[u] + cost + h[u] - h[v]) {
                dis[v] = dis[u] + cost + h[u] - h[v];
                preE[v] = i;
                preV[v] = u;
                que.push(pii(dis[v], v));
            }
        }
    }
    return dis[e] != inf;
}
int MincostMaxflow(int s, int e, int &cost) {
    int maxflow = 0;
    memset(h, 0, sizeof(h));
    while (Dijkstra(s, e)) { 
        for (int i = 0; i <= e; ++i) h[i] += dis[i];
        int flow = inf; 
        for (int i = e; i != s; i = preV[i]) {
            flow = min(flow, edge[preE[i]].c); // 取最小的流量
        }
        for (int i = e; i != s; i = preV[i]) {
            edge[preE[i]].c -= flow;
            edge[preE[i]^1].c += flow;
        }
        cost += flow * h[e];
        maxflow += flow;
    }
    return maxflow; // 返回最大流
}
// Dijkstra + vector
#define pii pair<int,int>
int preE[maxn], preV[maxn], dis[maxn], h[maxn];
struct ac{
    int v, c, cost, nex;
};
vector<ac> g[maxn];
void init() {
    for (int i = 0; i < maxn; ++i) g[i].clear();
}
void addedge(int u, int v, int c, int cost) {
    g[u].push_back({v, c, cost, (int)g[v].size()});
    g[v].push_back({u, 0, -cost, (int)g[u].size()-1});
}
int Dijkstra(int s, int e) {
    priority_queue<pii, vector<pii>, greater<pii> >que;
    que.push(pii(0, s));
    memset(dis, inf, sizeof(dis));
    dis[s] = 0;
    while (!que.empty()) {
        pii top = que.top();
        que.pop();
        int u = top.second;
        if (dis[u] < top.first) continue;
        for (int i = 0; i < (int)g[u].size(); ++i) {
            int v = g[u][i].v;
            int cost = g[u][i].cost;
            int c = g[u][i].c;
            if (c > 0 && dis[v] > dis[u] + cost + h[u] - h[v]) {
                dis[v] = dis[u] + cost + h[u] - h[v];
                preE[v] = i;
                preV[v] = u;
                que.push(pii(dis[v], v));
            }
        }
    }
    return dis[e] != inf;
}
int MincostMaxflow(int s, int e, int &cost) {
    int maxflow = 0;
    memset(h, 0, sizeof(h));
    while (Dijkstra(s, e)) { 
        for (int i = 0; i <= e; ++i) h[i] += dis[i];
        int flow = inf; 
        for (int i = e; i != s; i = preV[i]) {
            flow = min(flow, g[preV[i]][preE[i]].c);
        }
        for (int i = e; i != s; i = preV[i]) {
            ac& t = g[preV[i]][preE[i]]; 
            t.c -= flow;
            g[i][t.nex].c += flow;
        }
        cost += flow * h[e];
        maxflow += flow;
    }
    return maxflow;
}
