struct SuffixArray{ // 下标1
    int cntA[maxn], cntB[maxn], A[maxn], B[maxn];
    int Sa[maxn], tsa[maxn], height[maxn], Rank[maxn]; // Sa[i] 排名第i的下标， Rank[i] 下标i的排名
    int n, dp[maxn][21];
    void init(char *buf, int len) { // 预处理，sa，rank，height
        n = len;
        for (int i = 0; i < 500; ++i) cntA[i] = 0;
        for (int i = 1; i <= n; ++i) cntA[(int)buf[i]]++;
        for (int i = 1; i < 500; ++i) cntA[i] += cntA[i-1];
        for (int i = n; i >= 1; --i) Sa[ cntA[(int)buf[i]]-- ] = i;
        Rank[ Sa[1] ] = 1;
        for (int i = 2; i <= n; ++i) {
            Rank[Sa[i]] = Rank[Sa[i-1]];
            if (buf[Sa[i]] != buf[Sa[i-1]]) Rank[Sa[i]]++;
        }
        for (int l = 1; Rank[Sa[n]] < n; l <<= 1) {
            for (int i = 0; i <= n; ++i) cntA[i] = 0;
            for (int i = 0; i <= n; ++i) cntB[i] = 0;
            for (int i = 1; i <= n; ++i) {
                cntA[ A[i] = Rank[i] ]++;
                cntB[ B[i] = (i + l <= n) ? Rank[i+l] : 0]++;
            }
            for (int i = 1; i <= n; ++i) cntB[i] += cntB[i-1];
            for (int i = n; i >= 1; --i) tsa[ cntB[B[i]]-- ] = i;
            for (int i = 1; i <= n; ++i) cntA[i] += cntA[i-1];
            for (int i = n; i >= 1; --i) Sa[ cntA[A[tsa[i]]]-- ] = tsa[i];
            Rank[ Sa[1] ] = 1;
            for (int i = 2; i <= n; ++i) {
                Rank[Sa[i]] = Rank[Sa[i-1]];
                if (A[Sa[i]] != A[Sa[i-1]] || B[Sa[i]] != B[Sa[i-1]]) Rank[Sa[i]]++;
            }
        }
        for (int i = 1, j = 0; i <= n; ++i) {
            if (j) --j;
            int tmp = Sa[Rank[i] - 1];
            while (i + j <= n && tmp + j <= n && buf[i+j] == buf[tmp+j]) ++j;
            height[Rank[i]] = j;
        }
    }
    void st() {
        for (int i = 1; i <= n; ++i) {
            dp[i][0] = height[i];
        }
        for (int j = 1; j <= log2(n); ++j) {
            for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
                dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    int rmq(int l, int r) {
        int len = r - l + 1;
        int x = log2(len);
        return min(dp[l][x], dp[r - (1 << x) + 1][x]);
    }
    int lcp(int x, int y) { // 最长公共前缀
        int l = Rank[x];
        int r = Rank[y];
        if (l > r) swap(l, r);
        return rmq(l+1, r);
    }
    int getnum() { // 字串的个数
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            ans += n - Sa[i] + 1 - height[i];
        }
        return ans;
    }
}S;