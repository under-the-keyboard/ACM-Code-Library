long long  exgcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long ans = exgcd(b, a % b, x, y);
    long long temp = x;
    x = y;
    y = temp - (a / b) * y;
    return ans;
}
long long inv(long long a) {
    long long x, y;
    long long t = exgcd(a, M, x, y);
    if (t != 1) {
        return -1;
    }
    return (x % M + M) % M;
}
 
long long fac[maxn];
void getfac() {
    fac[0] = 1;
    for (int i = 1; i < maxn; i++) {
        fac[i] = fac[i - 1] * i % M;
    }
}
long long C(long long n, long long m) {
    if (n < 0 || m < 0|| n < m) {
        return 0;
    }
    return fac[n] * inv(fac[m]) % M * inv(fac[n - m]) % M;
}

long long lucas(long long n, long long m) {
    if (m == 0) {
        return 1;
    }
    return (lucas(n / M, m / M) * C(n % M, m % M)) % M;
}
