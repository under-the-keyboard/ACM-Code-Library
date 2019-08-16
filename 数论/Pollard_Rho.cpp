long long factor[1000005];
int tot;
const int S=50;
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
bool check(long long a, long long n, long long x, long long t) {
    long long ret = Ksm(a, x, n);
    long long last = ret;
    for(int i = 1; i <= t; i ++) {
        ret = Ksc(ret, ret, n);
        if(ret == 1 && last != 1 && last != n-1) return true;//是合数
        last = ret;
    }
    if(ret != 1) return true;
    return false;
}
bool Miller_Rabin(long long n) {//判素数
    if(n < 2) return false;
    if(n == 2) return true;
    if((n&1) == 0)return false;
    long long x = n - 1;
    long long t = 0;
    while((x&1) == 0) {
        x >>= 1;
        t ++;
    }
    for(int i = 0; i < S; i ++) {
        long long a = rand() % (n-1) + 1;
        if(check(a, n, x, t))//如果检查出来是合数
        return false;
    }
    return true;
}
long long gcd(long long a,long long b) {
    if(a == 0) return 1;
    if(a < 0) return gcd(-a, b);
    while(b) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}
long long pollard_rho(long long x,long long c) {
    long long i = 1, k = 2;
    long long x0 = rand() % x;
    long long y = x0;
    while(1) {
        i ++;
        x0 = (Ksc(x0, x0, x) + c) % x;
        long long d = gcd(y-x0, x);
        if(d != 1 && d != x) return d;
        if(y == x0) return x;
        if(i == k) {
            y = x0;
            k += k;
        }
    }
}
void findphi(long long n) {
    if(Miller_Rabin(n)) {
        factor[tot++] = n;
        return;
    }
    long long p = n;
    while(p >= n) {
        p=pollard_rho(p, rand()%(n-1)+1);
    }
    findphi(p);
    findphi(n/p);
}
int main() {
    long long n;
    while(scanf("%I64d",&n)!=EOF) {
        tot=0;
        findphi(n);
        for(int i=0;i<tot;i++)
        printf("%I64d",factor[i]),printf("\n");
        if(Miller_Rabin(n))printf("yes\n");
        else printf("no\n");
    }
    return 0;
}