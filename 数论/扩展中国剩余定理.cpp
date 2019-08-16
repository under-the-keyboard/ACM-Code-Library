long long M[maxn], C[maxn];
//模数， 余数
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

long long exCrt() {
    for (long long i = 2; i <= n; i ++) {
        long long M1 = M[i - 1], M2 = M[i];
        long long C1 = C[i - 1], C2 = C[i];
        long long T = gcd(M1, M2);
        long long t = (C2 - C1 % M2 + M2) % M2;
        if(t % T) return -1;
        M[i] = M1 / T * M2;
        C[i] = mul(getInv(M1 / T, M2 / T), t / T, (M2 / T));
        C[i] = C[i] * M1 + C1;
        C[i] = (C[i] % M[i] + M[i]) % M[i];
    }
    return C[n];
}

