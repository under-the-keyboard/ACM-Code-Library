const int maxn = 1e5 + 5;
const int inf = 0x3f3f3f3f;
const int mod = 998244353;
#define Mod(x) ((x)>=mod?(x)-mod:(x))
#define g 3

int rnk[maxn];
long long a[maxn], b[maxn];

long long Ksm(long long a, long long b) {
    long long res = 1;
    while(b) {
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

void init(int n) {
    memset(rnk, 0, sizeof(rnk));
    int lim = 0;
    while((1<<lim) < n) lim ++;
    for (int i = 0; i < n; i ++) 
        rnk[i] = (rnk[i>>1]>>1) | ((i&1) << (lim-1));
}


void ntt(long long *a, int op, int n) {
    for (int i = 0; i < n; i ++) 
        if(i < rnk[i]) swap(a[i], a[rnk[i]]);
    for (int i = 2; i <= n; i <<= 1) {
        int nw = Ksm(g, (mod-1)/i);
        if(op == -1) nw = Ksm(nw, mod-2);
        for (int j = 0, m = i >> 1; j < n; j += i)  
            for (int k = 0, w = 1; k < m; k ++) {
                int t = 1ll * a[j+k+m] * w % mod;
                a[j+k+m] = Mod(a[j+k]-t+mod);
                a[j+k] = Mod(a[j+k]+t);
                w = 1ll * w * nw % mod;
            }
    }
    if(op == -1) 
        for (int i = 0, inv = Ksm(n, mod-2); i < n; i ++)
            a[i] = 1ll * a[i] * inv % mod;
}

char s1[maxn], s2[maxn];
long long ans[maxn];

int main() {
    scanf("%s", s1);
    scanf("%s", s2);
    int len1 = strlen(s1), len2 =strlen(s2);
    int n = 1;
    while(n < len1 + len2) n <<= 1;
    init(n);
    for (int i = 0; i < len1; i ++) a[len1-i-1] = s1[i]-'0';
    for (int i = 0; i < len2; i ++) b[len2-i-1] = s2[i]-'0';
    ntt(a, 1, n); ntt(b, 1, n);
    for (int i = 0; i < n; i ++) 
        a[i] = (1ll * a[i] * b[i]) % mod;
    ntt(a, -1, n);
    for (int i = 0; i < n; i ++) 
        cout << a[i] << " ";
    cout << endl;
    for (int i = 0; i < n; i ++) {
        ans[i+1] += ans[i] / 10;
        ans[i] %= 10;
    }
    int pos = n-1;
    while(!a[pos]) pos--;
    for (int i = pos; i >= 0; i --) cout << a[i];
    cout << endl;
    return 0;
}
//三模NTT

#define long long long long 
const long long maxn = 3 * 1e6 + 10;
#define swap(x,y) x ^= y, y ^= x, x ^= y
using namespace std;
long long a[maxn], b[maxn];

long long Mul(long long a, long long b, long long mod) {
    a %= mod, b %= mod;
    return ((a * b - (long long)((long long)((long double)a / mod * b + 1e-3) * mod)) % mod + mod) % mod;
}

long long Ksm(long long a, long long p, long long mod) {
    long long base = 1;
    while(p) {
        if(p & 1) base = 1ll * a * base % mod;
        a = 1ll * a * a % mod; p >>= 1;
    }
    return base % mod;
} 

namespace NTT{

    const long long P1 = 469762049, P2 = 998244353, P3 = 1004535809, g = 3; 
    const long long PP = 1ll * P1 * P2;
    long long n, m, p, len = 1, lim;
    long long tmp1[maxn], tmp2[maxn], ans[3][maxn], r[maxn];
    long long res[maxn], tmp[maxn], base[maxn];
    /*
        传的参数n,m都比实际个数少一
        n--;m--;
        输入两个数n=1
        输入一个数n=0;
    */

    void init(long long n) { //初始化，传入alen+blen,得到最小的len
        len = 1; lim = 0;
        while(len <= n) len <<= 1, lim++;
        for(long long i = 0; i <= len; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (lim - 1));
    }

    void ntt_Mod(long long *a, const long long n, const long long type, const long long mod) { //ntt
        for(long long i = 0; i < n; i++) if(i < r[i]) swap(a[i], a[r[i]]);
        for(long long mid = 1; mid < n; mid <<= 1) {
            long long W = Ksm(type == 1 ? g : Ksm(g, mod - 2, mod) , (mod - 1) / (mid << 1), mod);
            for(long long j = 0; j < n; j += (mid << 1)) {
                long long w = 1;
                for(long long k = 0; k <mid; k++, w = 1ll * w * W % mod) {
                    long long x = a[j + k], y = 1ll * w * a[j + k + mid] % mod;
                    a[j + k] = (x + y) % mod,
                    a[j + k + mid] = (x - y + mod) % mod;
                }
            }
        }
        if(type == -1) {
            long long inv = Ksm(n, mod - 2, mod);
            for(long long i = 0; i < n; i++) 
                a[i] = 1ll * a[i] * inv % mod;
        }
    }

    void Out(long long *a, long long len) {
        for (int i = 0; i <= len; i ++) 
            cout << a[i] << " ";
        cout << endl;
    }

    int ntt_Mul(long long *a, long long *b, long long alen, long long blen, long long mod) {
        init(alen + blen);
        memcpy(tmp1, a, sizeof(tmp1)); memcpy(tmp2, b, sizeof(tmp2));
        ntt_Mod(tmp1, len, 1, P1); ntt_Mod(tmp2, len, 1, P1);
        for(long long i = 0; i <= len; i++) ans[0][i] = 1ll * tmp1[i] * tmp2[i] % P1;
        
        memcpy(tmp1, a, sizeof(tmp1)); memcpy(tmp2, b, sizeof(tmp2));
        ntt_Mod(tmp1, len, 1, P2); ntt_Mod(tmp2, len, 1, P2);
        for(long long i = 0; i <= len; i++) ans[1][i] = 1ll * tmp1[i] * tmp2[i] % P2;
        
        memcpy(tmp1, a, sizeof(tmp1)); memcpy(tmp2, b, sizeof(tmp2));
        ntt_Mod(tmp1, len, 1, P3); ntt_Mod(tmp2, len, 1, P3);
        for(long long i = 0; i <= len; i++) ans[2][i] = 1ll * tmp1[i] * tmp2[i] % P3;
        
        ntt_Mod(ans[0], len, -1, P1);
        ntt_Mod(ans[1], len, -1, P2);
        ntt_Mod(ans[2], len, -1, P3);
        
        for(long long i = 0; i <= alen + blen; i++) {
            long long t = (Mul(1ll * ans[0][i] * P2 % PP, Ksm(P2 % P1, P1 - 2, P1), PP) + 
                    Mul(1ll * ans[1][i] * P1 % PP, Ksm(P1 % P2, P2 - 2, P2), PP) ) % PP;
            long long K = ((ans[2][i] - t) % P3 + P3) % P3 * Ksm(PP % P3, P3 - 2, P3) % P3;
            a[i] = (t % mod + ((K % mod) * (PP % mod)) % mod ) % mod;         
        }
        return alen + blen;
    }

    int ntt_Ksm(long long *a, long long b, int blen, long long mod) {
        memcpy(base, a, sizeof(base));
        memset(a, 0, maxn*sizeof(a));
        a[0] = 1; int alen = 0;
        while(b) {
            if(b & 1) alen = ntt_Mul(a, base, alen, blen, mod);
            memcpy(tmp, base, sizeof(tmp));
            blen = ntt_Mul(base, tmp, blen, blen, mod);
            b >>= 1;
        }
        return alen;
    }
}

int main() {
    long long n, m, p;
    scanf("%lld %lld %lld", &n, &m, &p);
    for(long long i = 0; i <= n; i++) scanf("%lld", &a[i]);
    for(long long i = 0; i <= m; i++) scanf("%lld", &b[i]);
    NTT::ntt_Mul(a, b, n, m, p);
    for (int i = 0; i <= n + m; i ++) 
        printf("%lld ", a[i]);
    printf("\n");
    return 0;
}