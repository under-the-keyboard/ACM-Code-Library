// 强联通分量
int dfn[maxn], low[maxn], Stack[maxn], inStack[maxn], belong[maxn], in[maxn], ts, cnt, len;
void init(int n) {
    for (int i = 1; i <= n; ++i) g[i].clear();
    ts = cnt = len = 0;
    fill(dfn, dfn+n+1, 0);
    fill(in, in+n+1, 0);
    fill(inStack, inStack+n+1, 0);
}
void tarjan(int u) {
    dfn[u] = low[u] = ++ts;
    inStack[u] = 1;
    Stack[len++] = u;
    for (int i = 0; i < (int)g[u].size(); ++i) {
        int v = g[u][i];
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }else if (inStack[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        cnt++;
        while (1) {
            int top = Stack[--len];
            belong[top] = cnt;
            inStack[top] = 0;
            if (top == u) break;
        }
    }
}
for (int i = 1; i <= n; ++i) {
    if (dfn[i]) continue;
    tarjan(i);
}
// 双连通分量
vector<int> g[maxn];
int dfn[maxn], low[maxn], Stack[maxn], inStack[maxn];
int len, cnt, ts;
void init(int n) {
    len = cnt = ts = 0;
    for (int i = 1; i <= n; ++i) g[i].clear();
    fill(dfn, dfn+n+1, 0);
}
void tarjan(int u, int fa) {
    dfn[u] = low[u] = ++ts;
    Stack[len++] = u;
    for (int i = 0; i < (int)g[u].size(); ++i) {
        int v = g[u][i];
        if (v == fa) continue;
        if (!dfn[v]) {
            // Stack[len++] = {u, v};
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (dfn[u] <= low[v]) {
                fill(inStack, inStack+n+1, 0);
                inStack[u] = 1; 
                while (1) {
                    int top = Stack[--len];
                    inStack[top] = 1; // 记录每次的连通分量中的点
                    if (top == v) break; // top.u == u && top.v == top.v
                }
                // other check()
            }
        }else low[u] = min(low[u], dfn[v]);
    }
}
