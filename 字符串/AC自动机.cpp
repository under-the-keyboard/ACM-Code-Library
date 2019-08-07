char s[maxn];
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
    inline void insert(char s[]) {
        int now = root;
        for (int i = 0; s[i]; ++i) {
            if (nex[now][s[i]-'a'] == -1) 
                nex[now][s[i]-'a'] = newnode();
            now = nex[now][s[i]-'a'];
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
    inline LL query(char s[]) {
        int now = root;
        LL cnt = 0;
        for (int i = 0; s[i]; ++i) {
            now = nex[now][s[i]-'a'];
            int tmp = now;
            while (tmp != root && end[tmp] != -1) {
                cnt += end[tmp];
                end[tmp] = -1; // 统计种类，加速
                tmp = fail[tmp];
            }
        }
        return cnt;
    }
}ac;
