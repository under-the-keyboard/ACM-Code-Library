struct T{
    long long p, d;
};
long long Ksm(long long a, long long b, long long p) {
    long long res = 1;
    while(b) {
        if(b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}
long long w;
T Mul_er(T a, T b, long long p) {//二次域乘法
    T ans;
    ans.p = (a.p * b.p + a.d * b.d % p * w % p) % p;
    ans.d = (a.p * b.d % p + a.d * b.p % p) % p;
    return ans;
}
T Ksm_er(T a, long long b, long long p) {//二次域快速幂
    T ans;
    ans.p = 1; ans.d = 0;
    while(b) {
        if(b & 1) ans = Mul_er(ans, a, p);
        a = Mul_er(a, a, p);
        b >>= 1;
    }
    return ans;
} 
long long Legendre(long long a, long long p) {//求勒让德符号
    return Ksm(a, (p-1)>>1, p);
}
long long Recever(long long a, long long p) {
    a %= p;
    if(a < 0) a += p;
    return a;
}
long long solve(long long n, long long p) {
    if(n % p == 0) return 0;
    if(p == 2) return 1;
    if(Legendre(n, p) + 1 == p) return -1;
    long long a = -1, t;
    while(1) {
        a = rand() % p;
        t = a * a - n;
        w = Recever(t, p);
        if(Legendre(w, p) + 1 == p) break;
    }
    T tmp;
    tmp.p = a; tmp.d = 1;
    T ans = Ksm_er(tmp, (p+1)>>1, p);
    return ans.p;
}