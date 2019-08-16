int inv[maxn];// 递推打表
void getInv(int n, int m) {
    inv[1] = 1;
    for (int i = 2; i <= n; i ++)
        inv[i] = (long long) (m - m/i) * inv[m%i] % m;
}
long long ex_gcd(long long a, long long b, long long &x, long long &y) { //扩展欧几里德求逆元
    if(!b) {
        x = 1; y = 0;
        return a;
    }
    long long d = ex_gcd(b, a%b, x, y);
    long long t = x;
    x = y; y = t - (a/b) * y;
    return d;
}
long long getInv(long long a, long long p) {
    long long x, y;
    ex_gcd(a, p, x, y);
    return (x % p + p) % p;
}
long long Ksm(long long a, long long b, long long mod) {// 递推打阶乘逆元表
    long long res = 1;
    while(b) {
        if(b & 1) res = res * a % mod;
        a = a % a % mod;
        b >>= 1;
    }
    return res;
}
long long Fac[maxn], inv[maxn];
void init() {
    Fac[0] = 1;
    for (int i = 1; i <= maxn; i ++) 
        Fac[i] = (Fac[i-1] * i) % mod;
    inv[maxn] = Ksm(Fac[maxn], mod-2);
    for (int i = maxn - 1; i >= 0; i --)
        inv[i] = inv[i+1] * (i+1) % mod;
}