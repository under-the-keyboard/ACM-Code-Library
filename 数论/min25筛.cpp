const int maxn = 1e6 + 5;
const int inf = 0x3f3f3f3f;
const int Mod = 1e9 + 7;
const double eps = 1e-8;
typedef pair<int, int> psi;
#define inv_2 (Mod+1)/2
#define inv_6 (Mod+1)/6
long long sqr, m, w[maxn], g[maxn], h[maxn];
long long sumg[maxn], sumh[maxn], id1[maxn], id2[maxn];
long long prim[maxn], tot;
bool mark[maxn];

long long Add(long long a, long long b) {
    return (a + b) % Mod;
}

long long Sup(long long a, long long b) {
    return (a - b + Mod) % Mod;
}

long long Pow(long long a, long long b) {
    long long res = 1;
    while(b) {
        if(b & 1) res = res * a % Mod;
        a = a * a % Mod;
        b >>= 1;
    }
    return res;
}

void init(long long n) {
    mark[1] = 1;
    for (long long i = 2; i <= n; i ++) {
        if(!mark[i]) {
            prim[++tot] = i;
            sumg[tot] = (sumg[tot-1] + i * i) % Mod;
            sumh[tot] = (sumh[tot-1] + i) % Mod;
        }
        for (long long j = 1; j <= tot; j ++) {
            if(i * prim[j] > n) break;
            mark[i * prim[j]] = 1;
            if(i % prim[j] == 0) break;
        }
    }
}

void GetW(long long n) {
    for (long long i = 1, j; i <= n; i = j + 1) {
        j = n / (n / i);
        w[++m] = n / i;
        long long t = w[m] % Mod;
        g[m] = t * (t + 1) % Mod * ((2LL * t + 1) % Mod) % Mod * inv_6 % Mod;
        g[m] --;
        h[m] = t * (t + 1) % Mod * inv_2 % Mod;
        h[m] --;
        if(w[m] <= sqr) id1[w[m]] = m;
        else id2[n/w[m]] = m;
    }
}

void GetG(long long n) {
    for (long long i = 1; i <= tot; i ++) {
        for (long long j = 1; j <= m && prim[i] * prim[i] <= w[j]; j ++) {
            long long d = w[j] / prim[i];
            long long id = d <= sqr ? id1[d] : id2[n/d];
            g[j] = Sup(g[j], prim[i] * prim[i] % Mod * ((g[id] - sumg[i-1] + Mod) % Mod) % Mod);
            h[j] = Sup(h[j], prim[i] * ((h[id] - sumh[i-1] + Mod) % Mod) % Mod);
        }
    }
}

long long S(long long x, long long y, long long n) {
    if(x <= prim[y-1] || x <= 1) return 0;
    long long id = x <= sqr ? id1[x] : id2[n/x];
    long long res = (g[id] - h[id] + Mod - sumg[y-1] + sumh[y-1] + Mod) % Mod;
    for (long long i = y; i <= tot && prim[i] * prim[i] <= x; i ++) {
        long long t = prim[i];
        for (long long j = 1; t <= x; j ++, t = t * prim[i]) {
            long long p1 = t % Mod;
            res = Add(res, p1 * (p1 - 1) % Mod * (S(x/t, i+1, n) + (j != 1)) % Mod);
        }
    }
    return res % Mod;
}

int main(int argc, char *args[]) {
    long long n;
    scanf("%lld", &n);
    sqr = sqrt(n);
    init(sqr);
    GetW(n);
    GetG(n);
    printf("%lld\n", (S(n, 1, n) + 1) % Mod);
    return 0;
}


