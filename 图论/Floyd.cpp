// Floyd 负边、任意两点间最短路
const int maxn = 1e3 + 5;
const int inf = 0x3f3f3f3f;
int path[maxn][maxn], g[maxn][maxn];
int min(int &x, int &y) {return x < y ? x : y;}
void Floyd(int n) { // 路径
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (g[i][j] > g[i][k] + g[k][j]) {
                    path[i][j] = k;
                    g[i][j] = g[i][k] + g[k][j];
                }
            }
        }
    }
}
void print(int u, int v) { // 输出路径 s -> print(s, e) -> e
    int t = path[u][v];
    if (t == -1) return;
    print(u, t);
    printf("->%d", t);
    print(t, v);
}
for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
        g[i][j] = i == j ? 0 : inf; 
        path[i][j] = -1;
    }
}

const int maxn = 1e3 + 5;
const int inf = 0x3f3f3f3f;
int min(int &x, int &y) {return x < y ? x : y;}
int path[maxn][maxn], g[maxn][maxn]; // 字典序最小路径
void Floyd(int n) {
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (i != k && g[i][j] > g[i][k] + g[k][j]) {
                    path[i][j] = path[i][k];
                    g[i][j] = g[i][k] + g[k][j];
                }else if (i != k && g[i][j] == g[i][k] + g[k][j] && path[i][j] > path[i][k]) {
                    path[i][j] = path[i][k];
                }
            }
        }
    }
}
void print(int u, int v) {
    printf("%d", u);
    if (u != v) printf("->");
    else {puts(""); return;}
    print(path[u][v], v);
}
for (int i = 1; i <= n; ++i) { // 初始化
    for (int j = 1; j <= n; ++j) {
        scanf("%d", &g[i][j]);
        if (g[i][j] == -1) g[i][j] = inf;
        else path[i][j] = j;
    }
}