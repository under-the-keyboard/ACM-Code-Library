struct Trie{
    int nex[maxn][26], fail[maxn], end[maxn];
    int root, p;
    inline int newnode() {
        for (int i = 0; i < 26; ++i) {
            nex[p][i] = -1;
        }
        end[p++] = 0;
        return p - 1;
    }
    inline void init() {
        p = 0;
        root = newnode();
    }
    inline void insert(char *buf) {
        int now = root;
        for (int i = 0; buf[i]; ++i) {
            if (nex[now][buf[i]-'a'] == -1) 
                nex[now][buf[i]-'a'] = newnode();
            now = nex[now][buf[i]-'a'];
        }
        end[now]++;
    } 
    inline void build() {
        queue<int> que;
        fail[root] = root;
        for (int i = 0; i < 26; ++i) {
            if (nex[root][i] == -1)
                nex[root][i] = root;
            else {
                fail[nex[root][i]] = root;
                que.push(nex[root][i]);
            }
        }
        while (!que.empty()) {
            int now = que.front();
            que.pop();
            for (int i = 0; i < 26; ++i) {
                if (nex[now][i] == -1) 
                    nex[now][i] = nex[fail[now]][i];
                else {
                    fail[nex[now][i]] = nex[fail[now]][i];
                    que.push(nex[now][i]);
                }
            }
        }
    }
    long long num[maxn], dp[maxn]; // num记录节点i匹配的个数, dp辅助得到所有适配数量
    long long dfs(int now) {
        if (now == root) return 0;
        if (dp[now] != -1) return dp[now];
        return dp[now] = end[now] + dfs(fail[now]);
    }
    inline void solve(char *buf) { 
        fill(num, num+maxn, 0);
        fill(dp, dp+maxn, -1);
        int now = root;
        for (int i = 0; buf[i]; ++i) {
            now = nex[now][buf[i]-'a'];
            num[i] = dfs(now);
        }   
    }
    inline long long query(char *buf) {
        int now = root;
        long long cnt = 0;
        for (int i = 0; buf[i]; ++i) {
            now = nex[now][buf[i]-'a'];
            int tmp = now;
            while (tmp != root && end[tmp] != -1) {
                cnt += end[tmp];
                end[tmp] = -1; // 统计种类，加速
                tmp = fail[tmp];
            }
        }
        return cnt;
    }
}L, R;