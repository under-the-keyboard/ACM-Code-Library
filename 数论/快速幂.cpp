long long p;
long long mul(long long a, long long b) {
    long long ans = 0;
    while(b) {
        if(b & 1) ans = (ans + a ) % p;
        b >>= 1;
        a = (a + a) % p;
    }
    return ans;
}
long long pow(long long a, long long b) {
    long long res = 1;
    long long base = a;
    while(b) {
        if(b & 1) res = mul(res, base) % p;
        base = mul(base, base) % p;
        b >>= 1;
    }
    return res;
}
