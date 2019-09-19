struct Hash{
/*  mod
    53,         97,         	193,         389,       769,
    1543,       3079,         	6151,        12289,     24593,
    49157,      98317,        	196613,      393241,    786433,
    1572869,    3145739,      	6291469,     12582917,  25165843,
    50331653,   100663319,	201326611,   402653189, 805306457, 
    1610612741,	3221225473,	4294967291, 23333333333333333
    base 131 233
*/
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
long long mul(long long x, long long y, long long mod) {
    x %= mod; y %= mod;
    long long tmp = (long long)((long double)x*y/mod+1e-8)*mod;
    return (x*y-tmp+mod)%mod;
}
long long f[26]={34183,13513,152993,13591,19687,350869,111187,766091,769297,
633469,752273,298651,617191,880421,136067,1408397,726899,458921,2133701,
2599847,2730947,4696343,10267237,18941059,34078909,69208409};
