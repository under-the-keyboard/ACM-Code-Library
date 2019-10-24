#include <bits/stdc++.h>
const int maxn = 1e5 + 5;
const long long inf = 1e18;
const int mod = 1e9 + 7;
using namespace std;
int T[maxn<<2], num[2][maxn<<2], cnt;
struct ac{
    long long v, c;
    bool operator <(const ac &t) const{
        return t.c < c;
    }
};
vector<ac> g[maxn<<2];
void add(int u, int v, int c) {
    g[u].push_back({v, c});
}
// 线段树部分
int build(int rt, int l, int r, int op) { // op=0(入树):叶子节点指向节点
    if (l == r) return num[op][rt] = l;   // op=1(出树):节点指向叶子节点
    num[op][rt] = ++cnt;
    int mid = (l + r) >> 1;
    int L = build(rt<<1, l, mid, op);
    int R = build(rt<<1|1, mid+1, r, op);
    if (op == 0) {
        add(L, num[op][rt], 0);
        add(R, num[op][rt], 0);
    }else {
        add(num[op][rt], L, 0);
        add(num[op][rt], R, 0);
    }
    return num[op][rt];
}
void update(int rt, int l, int r, int u, int ql, int qr, int c, int op) { // op=0:一对多
    if (ql > r || qr < l) return;                                         // op=1:多对一
    if (l >= ql && r <= qr) {
        if (op == 0) add(u, num[1][rt], c); // 一对多:入树的叶子节点 -> 出树的非叶子节点
        else add(num[0][rt], u, c); // 多对一:入树的非叶子节点 -> 出树的叶子节点
        return; 
    }
    int mid = (l + r) >> 1;
    update(rt<<1, l, mid, u, ql, qr, c, op);
    update(rt<<1|1, mid+1, r, u, ql, qr, c, op);
}
// Dijkstra部分
long long dis[maxn<<3];
bool vis[maxn<<3];
void Dijkstra(int s, int n) {
    fill(dis, dis+n+1, inf);
    fill(vis, vis+n+1, 0);
    dis[s] = 0;
    priority_queue<ac> que;
    que.push({s, 0});
    while (!que.empty()) {
        ac f = que.top();
        que.pop();
        int u = f.v;
        if (dis[u] < f.c || vis[u]) continue;
        vis[u] = 1;
        for (int i = 0; i < (int)g[u].size(); ++i) {
            int v = g[u][i].v;
            long long c = f.c + g[u][i].c;
            if (dis[v] > c) {
                dis[v] = c;
                que.push({v, c});
            }
        }
    }
}
build(1, 1, n, 0); // 入树
build(1, 1, n, 1); // 出树
