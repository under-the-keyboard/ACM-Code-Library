#define random(a, b) (((double)rand()/RAND_MAX)*(b-a)+a)

long long Ksc(long long a, long long b, long long mod) {
    a %= mod, b %= mod;
    return ((a * b - (long long)((long long)((long double)a / mod * b + 1e-3) * mod)) % mod + mod) % mod;
}

long long Ksm(long long a, long long b, long long mod) {
    long long res = 1;
    while(b) {
        if(b & 1) res = Ksc(res, a, mod);
        a = Ksc(a, a, mod);
        b >>= 1;
    }
    return res;
}

bool Miller_Rabin(long long n) {
    if(n <= 2) {
        if(n == 2) return true;
        return false;
    }
    if(n % 2 == 0) return false;
    long long u = n - 1;
    while(u % 2 == 0) u /= 2;
    int S = 100;
    srand((long long)time(0));
    for (int i = 1; i <= S; i ++){
        long long a = rand() % (n - 2)+ 2;
        long long x = Ksm(a, u, n);
        while(u < n) {
            long long y = Ksm(x, 2, n);
            if(y == 1 && x != 1 && x != n - 1)
                return false;
            x = y;
            u = u * 2;
        }
        if(x != 1) return false;
    }
    return true;
}