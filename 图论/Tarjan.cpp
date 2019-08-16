int Stack[maxn], low[maxn], dfn[maxn], inStack[maxn], belong[maxn];
int now, len, cnt;
// now:时间戳，len：栈的大小，cnt强连通的个数
void init() {
	now = len = cnt = 0;
	mem(inStack, 0);
	mem(belong, 0);
	mem(dfn, 0);
	mem(low, 0);
}
void tarjan(int x) {
    // 打上标记，入栈
    low[x] = dfn[x] = ++now;
    Stack[++len] = x;
    inStack[x] = 1;
    for (int i = 0; i < (int)g[x].size(); ++i) {
        int y = g[x][i];
		// 没有访问过，继续递归
		// 在栈中表示可以形成一个强连通分量，更新根节点的low，继续找
        if (!dfn[y]) tarjan(y), low[x] = min(low[x], low[y]);
        else if (inStack[y]) low[x] = min(low[x], low[y]);
    }
	// 回溯，如果当前节点的dfn = low 表示栈中形成一个强连通分量
    if (dfn[x] == low[x]) {
        ++cnt; // 统计个数
        int top;
        while (Stack[len] != x) {
            top = Stack[len--];
            belong[top] = cnt;
            inStack[top] = 0; 
        }
        top = Stack[len--];
        belong[top] = cnt; // 记录每个点的隶属关系
        inStack[top] = 0;
    }
}
for (int i = 1; i <= n; ++i) {
    if (!dfn[i])  tarjan(i);
}
