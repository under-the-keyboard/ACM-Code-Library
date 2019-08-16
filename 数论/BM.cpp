//BM模板
//a[n] = f[1]a[n-1] + f[2]a[n-2] + f[3]a[n-3] + ...+ f[k]a[n-k]
//有限项
const long long mod = 998244353;
#define sz(x) ((int)(x).size())
typedef vector<long long> VI;

long long Ksm(long long a, long long b) {
    long long res = 1; a %= mod;
    assert(b >= 0);
    while(b) {
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int _, n;
namespace Linear_Seq{
    const int N = 10010;
    long long res[N], base[N], _c[N], _md[N];
    vector<int> Md;
    
    void Mul(long long *a, long long *b, int k) {
        for (int i = 0; i < k+k; i ++) _c[i] = 0;
        for (int i = 0; i < k; i ++)
            if(a[i]) for (int j = 0; j < k; j ++)
                _c[i+j] = (_c[i+j] + a[i]*b[j]) % mod;
        for (int i = k + k - 1; i >= k; i --) 
            if(_c[i]) for (int j = 0; j < sz(Md); j ++)
                _c[i-k+Md[j]] = (_c[i-k+Md[j]] - _c[i] * _md[Md[j]]) % mod;
        for (int i = 0; i < k; i ++)
            a[i] = _c[i];
    }

    int solve(long long n, VI a, VI b) {
        long long ans = 0, pnt = 0;
        int k = sz(a);
        assert(sz(a) == sz(b));
        for (int i = 0; i < k; i ++) _md[k-1-i] = -a[i];
        _md[k] = 1; Md.clear();
        for (int i = 0; i < k; i ++)  
            if(_md[i]) Md.push_back(i);
        for (int i = 0; i < k; i ++) res[i] = base[i] = 0;
        res[0] = 1;
        while((1ll<<pnt) <= n) pnt ++;
        for (int p = pnt; p >= 0; p --) {
            Mul(res, res, k);
            if((n>>p) & 1) {
                for (int i = k-1; i >= 0; i --) res[i+1] = res[i];
                res[0] = 0;
                for (int j = 0; j < sz(Md); j ++) 
                    res[Md[j]] = (res[Md[j]] - res[k] * _md[Md[j]]) % mod; 
            }
        }
        for (int i = 0; i < k; i ++) ans = (ans + res[i] * b[i]) % mod;
        if(ans < 0) ans += mod;
        return ans;
    }

    VI BM(VI s) {
        VI C(1, 1), B(1, 1);
        int L = 0, m = 1, b = 1;
        for (int n = 0; n < sz(s); n ++) {
            long long d = 0;
            for (int i = 0; i < L + 1; i ++) d = (d + (long long)C[i] * s[n-i]) % mod;
            if (d == 0) ++m;
            else if(2 * L <= n) {
                VI T = C;
                long long c = mod - d * Ksm(b, mod-2) % mod;
                while(sz(C) < sz(B) + m) C.push_back(0);
                for (int i = 0; i < sz(B); i ++) C[i+m] = (C[i+m] + c * B[i]) % mod;
                L = n + 1 - L; B = T; 
                b = d; m = 1;
            }else {
                long long c = mod - d * Ksm(b, mod-2) % mod;
                while(sz(C) < sz(B) + m) C.push_back(0);
                for (int i = 0; i < sz(B); i ++) C[i+m] = (C[i+m] + c * B[i]) % mod;
                ++ m;
            }
        }
        return C;
    }

    int Gao(VI a, long long n) { //得到第n项
        VI c = BM(a);
        c.erase(c.begin());
        for (int i = 0; i < sz(c); i ++) c[i] = (mod-c[i]) % mod;
        return solve(n, c, VI(a.begin(), a.begin()+sz(c)));
    }
};
using namespace Linear_Seq;


void solve() { //预处理前3k项
    long long n, k;
    scanf("%lld %lld", &n, &k);
    VI v, f;
    f.push_back(0);
    for (int i = 0; i < k; i ++) { //f只有k项
        long long x;
        scanf("%lld", &x);
        f.push_back(x);
    }
    for (int i = 0; i < k; i ++) { //a的前k项
        long long x;
        scanf("%lld", &x);
        v.push_back(x);
    }
    for (int i = k; i <= 2 * k; i ++) {//a的前3k项
        long long x = 0;
        for (int j = 1; j <= k; j ++) 
            x = (x + f[j] * v[i-j]) % mod;
        v.push_back(x);
    }
    printf("%lld\n", Gao(v, n));
}

int main() {
    solve();
    return 0;
}
//另一个板子
#include<bits/stdc++.h>
#define maxk 100005
#define maxn 200005
const int mod = 998244353;
 
#define mul(x, y) static_cast<long long> (x) * (y) % mod
 
namespace Math {
	inline int pw(int base, int p) {
		static int res; res = 1;
        while(p) {
            if(p & 1) res = mul(res, base);
            base = mul(base, base);
            p >>= 1;
        }
		return res;
	}
	inline int inv(int x) { return pw(x, mod - 2); }
}
inline void reduce(int &x) { x += x >> 31 & mod; }
 
namespace Poly {
#define N maxn
	int lim, s, rev[N], Wn[N];
	inline void init(const int n) { //初始化
		lim = 1, s = -1; 
        while (lim < n) lim <<= 1, ++s;
		for (register int i = 1; i < lim; ++i) 
            rev[i] = rev[i >> 1] >> 1 | (i & 1) << s;
		const int t = Math::pw(3, (mod - 1) / lim); *Wn = 1; 
        for (register int *i = Wn + 1; i != Wn + lim; ++i) 
            *i = mul(*(i - 1), t);
	}
	inline void FFT(int *A, const int op = 1) { //FFT
		for (register int i = 1; i < lim; ++i) 
            if (i < rev[i]) std::swap(A[i], A[rev[i]]);
		for (register int mid = 1; mid < lim; mid <<= 1) {
			const int t = lim / mid >> 1;
			for (register int i = 0; i < lim; i += mid << 1)
				for (register int j = 0; j < mid; ++j) {
					const int X = A[i + j], Y = mul(A[i + j + mid], Wn[t * j]);
					reduce(A[i + j] += Y - mod), reduce(A[i + j + mid] = X - Y);
				}
		}
		if (!op) {
			const int ilim = Math::inv(lim);
			for (register int *i = A; i != A + lim; ++i) *i = mul(*i, ilim);
			std::reverse(A + 1, A + lim);
		}
	}
 
	void INV(int *A, int *B, int n) {  //多项式A求逆到B，[0,n-1]
		if (n == 1) { *B = Math::inv(*A); return ; }
		static int C[N], D[N];
		const int len = n + 1 >> 1;
		INV(A, B, len), init(len * 3);
		std::memcpy(C, A, n << 2), std::memset(C + n, 0, lim - n << 2);
		std::memcpy(D, B, len << 2), std::memset(D + len, 0, lim - len << 2);
		FFT(C), FFT(D);
		for (int i = 0; i < lim; ++i) D[i] = (2 - mul(D[i], C[i]) + mod) * D[i] % mod;
		FFT(D, 0);
		std::memcpy(B + len, D + len, n - len << 2);
	}
 
	int G[N], INVG[N];
	void DIV(int *A, int *Q, int n, int m) {
		static int C[N];
		const int len = n - m + 1;
		std::reverse_copy(A, A + n, C), std::memset(C + len, 0, lim - len << 2);
		FFT(C);
		for (int i = 0; i < lim; ++i) Q[i] = mul(C[i], INVG[i]);
		FFT(Q, 0), std::reverse(Q, Q + len);
	}
	void DIV_MOD(int *A, int *R, int n, int m) {
		static int Q[N];
		const int len = n - m + 1;
		DIV(A, Q, n, m), std::memset(Q + len, 0, lim - len << 2);
		FFT(Q);
		for (int i = 0; i < lim; ++i) R[i] = mul(G[i], Q[i]);
		FFT(R, 0);
		for (int i = 0; i < m; ++i) reduce(R[i] = A[i] - R[i]);
	}
 
	void POW(int *A, int p, int m) {
		if (!p) return ;
		POW(A, p >> 1, m);
		static int T[N];
		std::memcpy(T, A, m << 2), std::memset(T + m, 0, lim - m << 2);
		FFT(T);
		for (int i = 0; i < lim; ++i) T[i] = mul(T[i], T[i]);
		FFT(T, 0);
		if (p & 1) {
			for (int i = 2 * m - 1; ~i; --i) T[i] = T[i - 1];
			T[0] = 0;
		}
		DIV_MOD(T, A, 2 * m, m + 1);
	}
 
	int solve(int *f, int *a, int n, int k) { //a为递推式0~k-1项，f为转移数组1~k项
		static int A[maxn], B[maxn];
		for (int i = 1; i <= k; ++i) reduce(G[k - i] = -f[i]);
		G[k] = A[0] = 1;
		std::reverse_copy(G, G + k + 1, B), B[k] = 0;
		INV(B, INVG, k), init(k << 1);
		FFT(G), FFT(INVG);
		Poly::POW(A, n, k);
		int ans = 0;
		for (int i = 0; i < k; ++i) reduce(ans += mul(A[i], a[i]) - mod);
		return ans;
	}
#undef N
}
 
int n, k;
int f[maxk], a[maxk];
int main() {
	/* 能求线性递推和mod 998244353的多项是求逆，其他的好
	像可以求，但是不会，先打个板子，以后再说把*/
    // int n;
    // scanf("%d", &n);
    // for (int i = 0; i < n; i ++) 
    //     scanf("%d", &a[i]);
    // Poly::INV(a, f, n);
    // for (int i = 0; i < n; i ++) 
    //     printf("%d ", f[i]);
    // printf("\n");
    
    // a(n)=f(i)*a(n-i) {1<=i<=k}
     
	std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
	std::cin >> n >> k;
	for (int i = 1; i <= k; ++i) std::cin >> f[i];
	for (int i = 0; i < k; ++i) std::cin >> a[i], reduce(a[i]);
    // for (int n = 0; n <= 10; n ++) {
        // std::cout << "n: " << n << " ";
	    std::cout << Poly::solve(f, a, n, k) << '\n';
    // }
    
	return 0;
}