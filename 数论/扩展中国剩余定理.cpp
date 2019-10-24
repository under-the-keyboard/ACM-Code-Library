long long M[maxn], C[maxn];//模数， 余数
long long mul(long long a, long long b, long long p) {
    if(b < 0) b = -b;
    long long ans = 0;
    while(b) {
        if(b & 1) ans = (ans + a) % p;
        a = (a + a) % p;
        b >>= 1;
    }
    return ans;
}
long long gcd(long long a, long long b) {
    return !b ? a : gcd(b, a %b);
}
long long exgcd(long long a, long long b, long long &x, long long &y) {
    if(!b) {
        x = 1;
        y = 0;
        return a;
    }
    long long d = exgcd(b, a % b, x, y);
    long long t = x;
    x = y;
    y = t - (a / b) * y;
    return d;
}
long long getInv(long long a, long long p) {
    long long x, y;
    exgcd(a, p, x, y);
    x = (x % p + p) % p;
    return x;
}
long long exCrt(long long *c_, long long *m_, int n) {// a,m from 1~n
    long long x, y, k;
    long long M = m_[1], ans = c_[1];
    for (int i = 2; i <= n; i ++) {
        long long a = M, b = m_[i], c = (c_[i] - ans % b + b) % b;
        long long gcd = exgcd(a, b, x, y), bg = b / gcd;
        if(c % gcd) return -1;
        x = Ksc(x, c/gcd, bg);
        ans += x * M;
        M *= bg;
        ans = (ans % M + M) % M; 
    }
    return (ans % M + M) % M;
}