const int M = 5e6;
const int Mod = 1e9 +7;
const double eps = 0.000000001;
long long phi[M + 30], prim[M + 30], tot;
bool mark[M + 30];
map<long long, long long> m;
#define inv_2 (Mod+1)/2

long long Add(long long a, long long b) {
    long long c = (a + b) % Mod;
    if(c >= Mod) return c - Mod;
    if(c < 0) return c + Mod;
    return c;
}

void init() {
    phi[1] = 1;
    for(long long i = 2; i <= M; i ++) {
        if(!mark[i]) {
            prim[++tot] = i;
            phi[i] = i - 1;
        }
        for (long long j = 1; j <= tot; j ++) {
            if(i * prim[j] > M) break;
            mark[i * prim[j]] = 1;
            if(i % prim[j] == 0) {
                phi[i * prim[j]] = phi[i] * prim[j];
                break;
            }
            phi[i *prim[j]] = phi[i] * phi[prim[j]];
        }
    }
    for (int i = 1; i <= M; i ++) phi[i] = Add(phi[i-1], phi[i]);
}

long long getPhi(long long n) {
    if(n <= M) return phi[n];
    if(m[n]) return m[n];
    long long ans;
    ans = 1LL * n % Mod * (n % Mod + 1) % Mod * inv_2 % Mod;
    for (long long l = 2, r; l <= n; l = r + 1) {
        r = n/(n/l);
        ans = (ans - (r - l + 1) % Mod * getPhi(n/l) % Mod + Mod) % Mod;
    }
    return m[n] = ans;
}
long long solve(long long n) {
    long long ans = 0;
    for (long long l = 1, r; l <= n; l = r + 1) {
        r = n/(n/l);
        ans = Add(ans, 1ULL * (n/l) % Mod * (n/l) % Mod * (Add(getPhi(r) % Mod, -getPhi(l-1) % Mod)  ) % Mod);
    }
    return ans;
}

int main()
{
    init();
    long long n;
    cin >> n;
    m.clear();
    cout << solve(n) << endl;
    return 0;
}
/*
gcd之和
gcd(i,j)(1<=i<=n)(1<=j<=m)
 
 * /