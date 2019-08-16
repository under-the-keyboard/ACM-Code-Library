// Kruskal
int n, m;
struct ac{
	int u, v, w, flag;
	bool operator <(ac t) {
		return w < t.w;
	}
}g[maxn*maxn];
vector<int> son[maxn];
int pre[maxn], dis[maxn][maxn];
int find (int x) {
	return (pre[x] == x) ? x : pre[x] = find(pre[x]);
}
void Kruskal() {
	for (int i = 0; i <= n; ++i) {
		son[i].clear();
		son[i].push_back(i);
		pre[i] = i;
	}
	sort(g, g+m);
	int sum = 0;
	int cnt = 0;
	for (int i = 0; i < m; ++i) {
		if (cnt == n+1) break;
		int fx = find(g[i].u);
		int fy = find(g[i].v);
		if (fx == fy) continue;
		g[i].flag = 1;
		sum += g[i].w;
		cnt++;
		int lenx = son[fx].size();
		int leny = son[fy].size();
		if (lenx < leny) {
			swap(lenx, leny);
			swap(fx, fy);
		}
		// 更新两点的距离最大值
		for (int j = 0; j < lenx; ++j) {
			for (int k = 0; k < leny; ++k) {
				dis[son[fx][j]][son[fy][k]] = dis[son[fy][k]][son[fx][j]] = g[i].w; 
			}
		}
		pre[fy] = fx;
		//合并子树
		for (int j = 0; j < leny; ++j) {
			son[fx].push_back(son[fy][j]);
		}
		son[fy].clear();
	}
	int ans = inf;
	for (int i = 0; i < m; ++i) {		
		if (g[i].flag) continue;
		ans = min(ans, sum + g[i].w - dis[g[i].u][g[i].v]);
	}
	printf("%d %d\n", sum, ans);
}
// Prim
int n, m;
int g[maxn][maxn], val[maxn], vis[maxn], dis[maxn];
int pre[maxn], maxd[maxn][maxn];
bool used[maxn][maxn];
void prim(int s) {
    mem(maxd, 0);
    mem(vis, 0);
    mem(used, 0);
    for (int i = 1; i <= n; ++i) {
        dis[i] = g[s][i];
        pre[i] = s;
    }
    vis[s] = 1;
    int sum = 0, cnt = 0;
    for (int i = 1; i < n; ++i) {
        int u = -1, MIN = inf;
        for (int j = 1; j <= n; ++j) {
            if (vis[j]) continue;
            if (MIN > dis[j]) {
                MIN = dis[j];
                u = j;
            }
        }
        if (u == -1) break;
        vis[u] = 1;
        sum += MIN;
        cnt++;
        used[pre[u]][u] = used[u][pre[u]] = 1;
        maxd[u][pre[u]] = maxd[pre[u]][u] = MIN;
        for (int j = 1; j <= n; ++j) {
            if (j == u) continue;
            if (vis[j]) {
                maxd[u][j] = maxd[j][u] = max(maxd[pre[u]][j], MIN);
            }
            if (vis[j] == 0 && dis[j] > g[u][j]) {
                dis[j] = g[u][j];
                pre[j] = u;
            }
        } 
    }
    if (cnt != n-1) {
    	puts("No way");
    }
    int ans = inf;
    for (int i = 1; i <= n; ++i) {
        for (int j = i+1; j <= n; ++j) {
            if (used[i][j]) continue;
            ans = min(ans, sum + g[i][j] - maxd[i][j]);
        }
    }
    printf("%d %d\n", sum, ans);
}
