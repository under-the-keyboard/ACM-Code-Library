struct Hash{
    long long p[maxn], hash[maxn], base = 131;
    long long getHash(int l, int r) {
        long long ans = (hash[r] - hash[l-1] * p[r-l+1]) % mod;
        return (ans + mod) % mod;
    }
    void init(string s) {
        int n = s.size();
        p[0] = 1;
        for (int i = 1; i <= n; ++i) p[i] = p[i - 1] * base % mod;
        for (int i = 1; i <= n; ++i) {
            hash[i] = (hash[i - 1] * base % mod + (s[i-1] - 'a' + 1)) % mod;
        }
    }
}hash;
