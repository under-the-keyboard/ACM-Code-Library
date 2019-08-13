struct SAM{
    int trans[maxn<<1][26], slink[maxn<<1], maxlen[maxn<<1];
    // 用来求endpos
    int indegree[maxn<<1], endpos[maxn<<1], rank[maxn<<1], ans[maxn<<1];
    // 计算所有子串的和(0-9表示)
    long sum[maxn<<1];
    int last, now, root, len;
    inline void newnode (int v) {
        maxlen[++now] = v;
    }
    inline void extend(int c) {
        newnode(maxlen[last] + 1);
        int p = last, np = now;
        // 更新trans
        while (p && !trans[p][c]) {
            trans[p][c] = np;
            p = slink[p];
        }
        if (!p) slink[np] = root;
        else {
            int q = trans[p][c];
            if (maxlen[p] + 1 != maxlen[q]) {
                // 将q点拆出nq，使得maxlen[p] + 1 == maxlen[q]
                newnode(maxlen[p] + 1);
                int nq = now;
                memcpy(trans[nq], trans[q], sizeof(trans[q]));
                slink[nq] = slink[q];
                slink[q] = slink[np] = nq;
                while (p && trans[p][c] == q) {
                    trans[p][c] = nq;
                    p = slink[p];
                } 
            }else slink[np] = q;
        }
        last = np;
        // 初始状态为可接受状态
        endpos[np] = 1;
    }
    inline void build(char *s) {
        // scanf("%s", s);
        len = strlen(s);
        root = last = now = 1;
        for (int i = 0; i < len; ++i) extend(s[i] - '0'); // extend(s[i] - '1');
    }
    // 计算所有子串的和（0-9表示）
    inline long getSum() {
    	// 拓扑排序 
        for (int i = 1; i <= now; ++i) indegree[ maxlen[i] ]++;
        for (int i = 1; i <= now; ++i) indegree[i] += indegree[i-1];
        for (int i = 1; i <= now; ++i) rank[ indegree[ maxlen[i] ]-- ] = i;
        mem(endpos, 0);
        endpos[1] = 1; // 从根节点向后求有效的入度
        for (int i = 1; i <= now; ++i) {
            int x = rank[i];
            for (int j = 0; j < 10; ++j) {
                int nex = trans[x][j];
                if (!nex) continue;
                endpos[nex] += endpos[x]; // 有效入度
                long num = (sum[x] * 10 + endpos[x] * j) % mod; 
                sum[nex] = (sum[nex] + num) % mod; // 状态转移
            }
        }
        long long ans = 0;
        for (int i = 2; i <= now; ++i) ans = (ans + sum[i]) % mod;
        return ans;
    }
    inline void getEndpos() {
        // topsort
        for (int i = 1; i <= now; ++i) indegree[ maxlen[i] ]++; // 统计相同度数的节点的个数
        for (int i = 1; i <= now; ++i) indegree[i] += indegree[i-1];  // 统计度数小于等于 i 的节点的总数
        for (int i = 1; i <= now; ++i) rank[ indegree[ maxlen[i] ]-- ] = i;  // 为每个节点编号，节点度数越大编号越靠后
        // 从下往上按照slik更新
        for (int i = now; i >= 1; --i) {
            int x = rank[i];
            endpos[slink[x]] += endpos[x];
        }
    }
    // 求不同的子串种类
    inline long long all () {
        long long ans = 0;
        for (int i = root+1; i <= now; ++i) {
            ans += maxlen[i] - maxlen[ slink[i] ];
        }
        return ans;
    }
    // 长度为K的字符串有多种，求出现次数最多的次数
    inline void get_Maxk() {
        getEndpos();
        for (int i = 1; i <= now; ++i) {
            ans[maxlen[i]] = max(ans[maxlen[i]], endpos[i]);
        }
        for (int i = len; i >= 1; --i) ans[i] = max(ans[i], ans[i+1]);
        for (int i = 1; i <= len; ++i) //cout << ans[i] << endl; 
            printf("%d\n", ans[i]);
    }
}sam;