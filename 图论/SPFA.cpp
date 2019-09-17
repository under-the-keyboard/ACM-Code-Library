// 判断负环，求负边最短路
int dis[maxn], cnt[maxn], vis[maxn];
vector<pair<int,int> > g[maxn];
int spfa(int s, int n) { // 普通
    memset(dis, inf, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    memset(cnt, 0, sizeof(cnt));
    queue<int> que;
    que.push(s);
    dis[s] = 0;
    vis[s] = 1;
    cnt[s] = 1;
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        vis[u] = 0;
        for (int i = 0; i < (int)g[u].size(); ++i) {
            int v = g[u][i].first;
            int c = g[u][i].second;
            if (dis[v] > dis[u] + c) {
                dis[v] = dis[u] + c;
                if (vis[v]) continue;
                vis[v] = 1;
                que.push(v);
                if (++cnt[v] > n) return 1;
            }
        }
    }
    return 0;
}
int spfa(int s, int n) { // 优化
    memset(dis, inf, sizeof(dis));
    memset(cnt, 0, sizeof(cnt));
    memset(vis, 0, sizeof(vis));
    int sum = 0, in = 1; // long long
    deque<int> que;
    que.push_back(s);
    dis[s] = 0;
    vis[s] = 1;
    cnt[s] = 1;
    while (!que.empty()) {
        int u = que.front();
        while (dis[u] * in > sum) { // LLL优化
            que.pop_front();
            que.push_back(u);
            u = que.front();            
        }
        que.pop_front();
        vis[u] = 0;
        in--;
        sum -= dis[u];
        for (int i = 0; i < (int)g[u].size(); ++i) {
            int v = g[u][i].first;
            int c = g[u][i].second;
            if (dis[v] > dis[u] + c) {  
                dis[v] = dis[u] + c;
                if (vis[v]) continue;
                if (!que.empty() && dis[v] <= dis[que.front()]) que.push_front(v); // SLF优化
                else que.push_back(v);
                vis[v] = 1;
                in++;
                sum += dis[v];
                if (++cnt[v] > n) return 1; // 判断负环
            }
        }
    }
    return 0;
}
