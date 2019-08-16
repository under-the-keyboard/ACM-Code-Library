//普通版
long long Ksc(long long a, long long b, long long mod) {
    long long ans = 0;
    while(b) {
        if(b & 1) ans = (ans + a ) % mod;
        b >>= 1;
        a = (a + a) % mod;
    }
    return ans;
}
//快速版
long long Ksc(long long a, long long b, long long mod){
    long long L = a * (b >> 25ll) % mod * (1ll << 25) % mod;
    long long R = a * (b & ((1ll << 25) - 1)) % mod;
    return (L + R) % mod;
}
//精确版
long long Ksc(long long a, long long b, long long mod) {
    a %= mod, b %= mod;
    return ((a * b - (long long)((long long)((long double)a / mod * b + 1e-3) * mod)) % mod + mod) % mod;
}