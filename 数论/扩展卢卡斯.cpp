long long Pre[maxn];

long long extend_gcd(long long a, long long b, long long &x, long long &y) {
    if(!b) {
        x = 1; y = 0;
        return a;
    }
    long long d = extend_gcd(b, a % b, x, y);
    long long t = x;
    x = y; y = t - (a / b) * y;
    return d;
}

long long mul(long long a, long long b, long long P){
    long long L = a * (b >> 25LL) % P * (1LL << 25) % P;
    long long R = a * (b & ((1LL << 25) - 1)) % P;
    return (L + R) % P;
}

long long Pow(long long a, long long b, long long P) {
    long long ans = 1; a %= P;
    while(b) {
        if(b & 1) ans = mul(ans, a, P);
        a = mul(a, a, P);
        b >>= 1;
    }
    return ans;
}

long long getInv(long long a, long long p) {
    long long x, y;
    extend_gcd(a, p, x, y);
    x = (x % p + p) % p;
    return x;
}

long long CRT(long long m, long long p, long long P) {
    return mul(mul(m, (P / p), P), getInv(P / p, p), P);
}

void init(long long pi, long long pk) {
    Pre[0] = 1;
    for (int i = 1; i <= pk; i ++) {
        Pre[i] = Pre[i - 1];
        if(i % pi) Pre[i] = mul(Pre[i], i, pk);
    }
}

long long Mul(long long n, long long pi, long long pk) {
    if(n <= 1) return 1;
    long long ans = Pow(Pre[pk], n / pk, pk);
    if(n % pk) ans = mul(ans, Pre[n % pk], pk);
    return mul(ans, Mul(n / pi, pi, pk), pk);
}

long long C(long long n, long long m, long long pi, long long pk) {
    if(n < m) return 0;
    init(pi, pk);
    long long r = 0;
    for(long long i = n; i; i /= pi) r += i / pi;
    for(long long i = m; i; i /= pi) r -= i / pi;
    for(long long i = n - m; i; i /= pi) r -= i / pi;
    long long a = Mul(n, pi, pk);
    long long b = getInv(Mul(m, pi, pk), pk);
    long long c = getInv(Mul(n - m, pi, pk), pk);
    long long ans = mul(mul(a, b, pk), c, pk);
    return mul(ans, Pow(pi, r, pk), pk);
}

long long ex_lucas(long long n, long long m, long long P) {
//C_n^m %p
    long long ans = 0;
    long long p = P;
    for (int i = 2; i <= P; i ++) {
        if(p % i == 0) {
            long long pi = i, pk = 1;
            while(p % i == 0) {
                p /= i;
                pk *= i;
            }
            ans = (ans + CRT(C(n, m, pi, pk), pk, P)) % P;
        }
    }
    return ans;
}
