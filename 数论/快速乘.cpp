long long Ksc(long long a, long long b, long long mod) {//普通版
    long long ans = 0;
    while(b) {
        if(b & 1) ans = (ans + a ) % mod;
        b >>= 1;
        a = (a + a) % mod;
    }
    return ans;
}
long long Ksc(long long a, long long b, long long mod){//快速版
    long long L = a * (b >> 25ll) % mod * (1ll << 25) % mod;
    long long R = a * (b & ((1ll << 25) - 1)) % mod;
    return (L + R) % mod;
}
long long Ksc(long long a, long long b, long long mod) {//精确版
    a %= mod, b %= mod;
    return ((a * b - (long long)((long long)((long double)a / mod * b + 1e-3) * mod)) % mod + mod) % mod;
}