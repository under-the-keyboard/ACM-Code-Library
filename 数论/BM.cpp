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
<<<<<<< HEAD
    vector<int> Md;  
=======
    vector<int> Md;
    
>>>>>>> dev
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
//anothers
<<<<<<< HEAD
#define maxk 100005
#define maxn 200005
const int mod = 998244353;
=======
#include<bits/stdc++.h>
#define maxk 100005
#define maxn 200005
const int mod = 998244353;
 
>>>>>>> dev
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
    inline int inv(int x) { return pw(x, mod-2); }
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
<<<<<<< HEAD
=======

>>>>>>> dev
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
<<<<<<< HEAD
=======

>>>>>>> dev
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
<<<<<<< HEAD
=======

>>>>>>> dev
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
<<<<<<< HEAD
=======

>>>>>>> dev
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
<<<<<<< HEAD
    // a(n)=f(i)*a(n-i) {1<=i<=k}
=======
    
    // a(n)=f(i)*a(n-i) {1<=i<=k}
     
>>>>>>> dev
	std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
	std::cin >> n >> k;
	for (int i = 1; i <= k; ++i) std::cin >> f[i];
	for (int i = 0; i < k; ++i) std::cin >> a[i], reduce(a[i]);
    // for (int n = 0; n <= 10; n ++) {
        // std::cout << "n: " << n << " ";
	    std::cout << Poly::solve(f, a, n, k) << '\n';
    // }
<<<<<<< HEAD
=======
    
>>>>>>> dev
	return 0;
}
//////////////////////////////////////////////////////////
class Linear_Seq
{
using VI = vector<int64_t> ;
public:
    static const int N = 50010;///多项式系数最大值
    int64_t res[N],base[N],c[N],md[N],COEF[N]/**COEF是多项式系数*/,Mod;
    vector<int> Md;
<<<<<<< HEAD
=======
 
>>>>>>> dev
    inline static int64_t gcdEx(int64_t a, int64_t b, int64_t&x, int64_t& y)
    {
        if(!b) {x=1;y=0;return a;}
        int64_t d = gcdEx(b,a%b,y,x);
        y -= (a/b)*x;
        return d;
    }
<<<<<<< HEAD
=======
 
>>>>>>> dev
    static int64_t Inv(int64_t a, int64_t Mod) {
        int64_t x, y;
        return gcdEx(a, Mod, x, y)==1?(x%Mod+Mod)%Mod:-1;
    };
<<<<<<< HEAD
=======
 
>>>>>>> dev
    inline void mul(int64_t *a,int64_t *b,int k) {
        fill(c,c+2*k,0) ;
        for(int i(0);i<k;++i)if(a[i])for(int j(0);j<k;++j)
            c[i+j]=(c[i+j]+a[i]*b[j])%Mod;
        for (int i(2*k-1);i>=k;--i) if (c[i])for(size_t j(0);j<Md.size();++j)
            c[i-k+Md[j]]=(c[i-k+Md[j]]-c[i]*md[Md[j]])%Mod;
        copy(c,c+k,a) ;
    }
    int solve(int64_t n,VI a,VI b) { // a 系数 b 初值 b[n+1]=a[0]*b[n]+...
        int64_t ans(0),cnt(0);
        int k(a.size());
        for(int i(0);i<k;++i) md[k-i-1]=-a[i];
        md[k]=1 ;  Md.clear() ;
        for(int i(0);i<k;++i) {
            res[i] = base[i] = 0;
            if (md[i]) Md.push_back(i);
        }
        res[0]=1;
        while ((1LL<<cnt)<=n) ++ cnt;
        for (int p(cnt);~p;-- p) {
            mul(res,res,k);
            if ((n>>p)&1) {
                for (int i(k-1);~i;--i) res[i+1]=res[i];  res[0]=0;
                for(size_t j(0);j<Md.size();++j)
                    res[Md[j]]=(res[Md[j]]-res[k]*md[Md[j]])%Mod;
            }
        }
        for(int i(0);i<k;++i) ans=(ans+res[i]*b[i])%Mod;
        return ans+(ans<0?Mod:0);
    }
<<<<<<< HEAD
=======
 
>>>>>>> dev
    ///1-st***********模数是质数用这里*******************/
    VI BM(VI s) {
        VI C(1,1),B(1,1);
        int L(0),m(1),b(1);
        for(size_t n(0);n<s.size();++n) {
            int64_t d(0);
            for(int i(0);i<=L;++i) d=(d+(int64_t)C[i]*s[n-i])%Mod;
            if (!d) ++m;
            else {
                int64_t c(Mod-d*Inv(b,Mod)%Mod);
                while (C.size()<B.size()+m) C.push_back(0);
                for (size_t i(0);i<B.size();++i)
                    C[i+m]=(C[i+m]+c*B[i])%Mod;
                if (2*L<=(int)n) {
                    VI Y(C); L=n+1-L; B=Y; b=d; m=1;
                } else ++m;
            }
        }
        /** //下边这样写能够输出递推式的系数.
        printf("F[n] = ") ;
        for(size_t i(0);i<C.size();++i) {
            COEF[i+1] = min(C[i],Mod-C[i]) ;
            if(i>0) {
                if(i != 1) printf(" + ") ;
                printf("%lld*F[n-%d]",COEF[i+1],i+1) ;
                putchar(i+1==C.size()?'\n':' ') ;
            }
        }
        */
        return C;
    }
    ///1-ed*************模数是质数用这里*******************/
<<<<<<< HEAD
=======
 
>>>>>>> dev
    ///2-st*************模数非质数用这里*******************/
    inline static void extand(VI &a, size_t d, int64_t value = 0) {
        if (d <= a.size()) return; a.resize(d, value);
    }
    static int64_t CRT(const VI &c, const VI &m) {
        int n(c.size());
        int64_t M(1), ans(0);
        for (int i = 0; i < n; ++i) M *= m[i];
        for (int i = 0; i < n; ++i) {
            int64_t x,y,tM(M / m[i]);
            gcdEx(tM, m[i], x, y);
            ans = (ans + tM * x * c[i] % M) % M;
        }
        return (ans + M) % M;
    }
<<<<<<< HEAD
=======
 
>>>>>>> dev
    static VI ReedsSloane(const VI &s, int64_t Mod) {
        auto L = [](const VI &a, const VI &b) {
            int da = (a.size()>1||(a.size()== 1&&a[0]))?a.size()-1:-1000;
            int db = (b.size()>1||(b.size()== 1&&b[0]))?b.size()-1:-1000;
            return max(da, db + 1);
        };
        auto prime_power = [&](const VI &s, int64_t Mod, int64_t p, int64_t e) {
            // linear feedback shift register Mod p^e, p is prime
            vector<VI> a(e), b(e), an(e), bn(e), ao(e), bo(e);
            VI t(e), u(e), r(e), to(e, 1), uo(e), pw(e + 1);;
            pw[0] = 1;
            for (int i(pw[0] = 1); i <= e; ++i) pw[i] = pw[i - 1] * p;
            for (int64_t i(0); i < e; ++i) {
                a[i] = {pw[i]}; an[i] = {pw[i]};
                b[i] = {0}; bn[i] = {s[0] * pw[i] % Mod};
                t[i] = s[0] * pw[i] % Mod;
                if (!t[i]) {t[i] = 1; u[i] = e;}
                else for (u[i] = 0; t[i] % p == 0; t[i] /= p, ++u[i]);
            }
            for (size_t k(1);k < s.size(); ++k) {
                for (int g(0); g < e; ++g) {
                    if (L(an[g], bn[g]) > L(a[g], b[g])) {
                        ao[g] = a[e-1-u[g]]; bo[g] = b[e-1-u[g]];
                        to[g] = t[e-1-u[g]]; uo[g] = u[e-1-u[g]];
                        r[g] = k - 1;
                    }
                }
                a = an; b = bn;
                for (int o(0); o < e; ++o) {
                    int64_t d(0);
                    for (size_t i(0); i < a[o].size() && i <= k; ++i)
                        d = (d + a[o][i] * s[k - i]) % Mod;
                    if (d == 0) {t[o] = 1;u[o] = e;}
                    else {
                        for (u[o]=0, t[o]=d;!(t[o]%p);t[o]/=p ,++u[o]);
                        int g (e-1-u[o]);
                        if (!L(a[g], b[g])) {
                            extand(bn[o], k + 1);
                            bn[o][k] = (bn[o][k] + d) % Mod;
                        } else {
                            int64_t coef = t[o]*Inv(to[g],Mod)%Mod*pw[u[o]-uo[g]]%Mod;
                            int m(k-r[g]);
                            extand(an[o],ao[g].size()+m); extand(bn[o],bo[g].size()+m);
                            auto fun = [&](vector<VI> &vn,vector<VI> &vo,bool f) {
                                for (size_t i(0);i < vo[g].size(); ++i) {
                                    vn[o][i+m] -= coef*vo[g][i]%Mod;
                                    if (vn[o][i + m]<0) vn[o][i+m] += Mod*(f?1:-1);
                                }
                                while (vn[o].size() && !vn[o].back()) vn[o].pop_back();
                            } ;
                            fun(an,ao,1) ;fun(bn,bo,-1) ;
                        }
                    }
                }
            }
            return make_pair(an[0], bn[0]);
        };
        vector<tuple<int64_t, int64_t, int> > fac;
        for (int64_t i(2); i*i <= Mod; ++i)
            if (!(Mod % i)) {
                int64_t cnt(0),pw(1);
                while (!(Mod % i)) {Mod /= i; ++cnt; pw *= i;}
                fac.emplace_back(pw, i, cnt);
            }
        if (Mod > 1) fac.emplace_back(Mod, Mod, 1);
        vector<VI> as;
        size_t n = 0;
        for (auto &&x: fac) {
            int64_t Mod, p, e;
            VI a, b;
            std::tie(Mod, p, e) = x;
            auto ss = s;
            for (auto &&x: ss) x %= Mod;
            std::tie(a, b) = prime_power(ss, Mod, p, e);
            as.emplace_back(a);
            n = max(n, a.size());
        }
        VI a(n),c(as.size()),m(as.size());
        for (size_t i(0); i < n; ++i) {
            for (size_t j(0); j < as.size(); ++j) {
                m[j] = std::get<0>(fac[j]);
                c[j] = i < as[j].size() ? as[j][i] : 0;
            }
            a[i] = CRT(c, m);
        }
        return a;
    }
    ///2-ed***********模数非质数用这里*******************/
<<<<<<< HEAD
=======
 
>>>>>>> dev
    int64_t solve(VI a,int64_t n,int64_t Mod,bool prime=true) {
        VI c; this->Mod = Mod ;
        if(prime) c = BM(a);///如果已经知道系数了,直接输入到c就行了,不用调用BM().
        else c = ReedsSloane(a,Mod);
        c.erase(c.begin());
        for(size_t i(0);i<c.size();++i) c[i] = (Mod-c[i])%Mod;
        return solve(n,c,VI(a.begin(),a.begin()+c.size()));
    }
}BMEX;
///BMEX.slove(初始值vector[从0开始],要得到的项数,模数,模数是不是质数)
/////////////////////////////////////////////////////////////////////////
// given first m items init[0..m-1] and coefficents trans[0..m-1] or
// given first 2 *m items init[0..2m-1], it will compute trans[0..m-1]
// for you. trans[0..m] should be given as that
//      init[m] = sum_{i=0}^{m-1} init[i] * trans[i]
struct LinearRecurrence {
  using vec = vector<ll>;
<<<<<<< HEAD
=======
 
>>>>>>> dev
  static void extand(vec &a, ll d, ll value = 0) {
    if (d <= a.size()) return;
    a.resize(d, value);
  }
<<<<<<< HEAD
=======
 
>>>>>>> dev
  static vec BerlekampMassey(const vec &s, ll mod) {
    std::function<ll(ll)> inverse = [&](ll a) {
      return a == 1 ? 1 : (ll)(mod - mod / a) * inverse(mod % a) % mod;
    };
    vec A = {1}, B = {1};
    ll b = s[0];
    for (size_t i = 1, m = 1; i < s.size(); ++i, m++) {
      ll d = 0;
      for (size_t j = 0; j < A.size(); ++j) {
        d += A[j] * s[i - j] % mod;
      }
      if (!(d %= mod)) continue;
      if (2 * (A.size() - 1) <= i) {
        auto temp = A;
        extand(A, B.size() + m);
        ll coef = d * inverse(b) % mod;
        for (size_t j = 0; j < B.size(); ++j) {
          A[j + m] -= coef * B[j] % mod;
          if (A[j + m] < 0) A[j + m] += mod;
        }
        B = temp, b = d, m = 0;
      } else {
        extand(A, B.size() + m);
        ll coef = d * inverse(b) % mod;
        for (size_t j = 0; j < B.size(); ++j) {
          A[j + m] -= coef * B[j] % mod;
          if (A[j + m] < 0) A[j + m] += mod;
        }
      }
    }
    return A;
  }
<<<<<<< HEAD
=======
 
>>>>>>> dev
  static void exgcd(ll a, ll b, ll &g, ll &x, ll &y) {
      if (!b) x = 1, y = 0, g = a;
      else {
          exgcd(b, a % b, g, y, x);
          y -= x * (a / b);
      }
  }
  static ll crt(const vec &c, const vec &m) {
      ll n = c.size();
      ll M = 1, ans = 0;
      for (ll i = 0; i < n; ++i) M *= m[i];
      for (ll i = 0; i < n; ++i) {
          ll x, y, g, tm = M / m[i];
          exgcd(tm, m[i], g, x, y);
          ans = (ans + tm * x * c[i] % M) % M;
      }
      return (ans + M) % M;
  }
  static vec ReedsSloane(const vec &s, ll mod) {
      auto inverse = [] (ll a, ll m) {
          ll d, x, y;
          exgcd(a, m, d, x, y);
          return d == 1 ? (x % m + m) % m : -1;
      };
      auto L = [] (const vec &a, const vec &b) {
          ll da = (a.size() > 1 || (a.size() == 1 && a[0])) ? (ll)a.size() - 1 : -1000;
          ll db = (b.size() > 1 || (b.size() == 1 && b[0])) ? (ll)b.size() - 1 : -1000;
          return max(da, db + 1);
      };
      auto prime_power = [&] (const vec &s, ll mod, ll p, ll e) {
          // linear feedback shift register mod p^e, p is prime
          vector<vec> a(e), b(e), an(e), bn(e), ao(e), bo(e);
          vec t(e), u(e), r(e), to(e, 1), uo(e), pw(e + 1);;
<<<<<<< HEAD
=======
 
>>>>>>> dev
          pw[0] = 1;
          for (ll i = pw[0] = 1; i <= e; ++i) pw[i] = pw[i - 1] * p;
          for (ll i = 0; i < e; ++i) {
              a[i] = {pw[i]}, an[i] = {pw[i]};
              b[i] = {0}, bn[i] = {s[0] * pw[i] % mod};
              t[i] = s[0] * pw[i] % mod;
              if (t[i] == 0) {
                  t[i] = 1, u[i] = e;
              } else {
                  for (u[i] = 0; t[i] % p == 0; t[i] /= p, ++u[i]);
              }
          }
          for (ll k = 1; k < s.size(); ++k) {
              for (ll g = 0; g < e; ++g) {
                  if (L(an[g], bn[g]) > L(a[g], b[g])) {
                      ao[g] = a[e - 1 - u[g]];
                      bo[g] = b[e - 1 - u[g]];
                      to[g] = t[e - 1 - u[g]];
                      uo[g] = u[e - 1 - u[g]];
                      r[g] = k - 1;
                  }
              }
              a = an, b = bn;
              for (ll o = 0; o < e; ++o) {
                  ll d = 0;
                  for (ll i = 0; i < a[o].size() && i <= k; ++i) {
                      d = (d + a[o][i] * s[k - i]) % mod;
                  }
                  if (d == 0) {
                      t[o] = 1, u[o] = e;
                  } else {
                      for (u[o] = 0, t[o] = d; t[o] % p == 0; t[o] /= p, ++u[o]);
                      ll g = e - 1 - u[o];
                      if (L(a[g], b[g]) == 0) {
                          extand(bn[o], k + 1);
                          bn[o][k] = (bn[o][k] + d) % mod;
                      } else {
                          ll coef = t[o] * inverse(to[g], mod) % mod * pw[u[o] - uo[g]] % mod;
                          ll m = k - r[g];
                          extand(an[o], ao[g].size() + m);
                          extand(bn[o], bo[g].size() + m);
                          for (ll i = 0; i < ao[g].size(); ++i) {
                              an[o][i + m] -= coef * ao[g][i] % mod;
                              if (an[o][i + m] < 0) an[o][i + m] += mod;
                          }
                          while (an[o].size() && an[o].back() == 0) an[o].pop_back();
                          for (ll i = 0; i < bo[g].size(); ++i) {
                              bn[o][i + m] -= coef * bo[g][i] % mod;
                              if (bn[o][i + m] < 0) bn[o][i + m] -= mod;
                          }
                          while (bn[o].size() && bn[o].back() == 0) bn[o].pop_back();
                      }
                  }
              }
          }
          return make_pair(an[0], bn[0]);
      };
<<<<<<< HEAD
=======
 
>>>>>>> dev
      vector<tuple<ll, ll, ll>> fac;
      for (ll i = 2; i * i <= mod; ++i) if (mod % i == 0) {
              ll cnt = 0, pw = 1;
              while (mod % i == 0) mod /= i, ++cnt, pw *= i;
              fac.emplace_back(pw, i, cnt);
          }
      if (mod > 1) fac.emplace_back(mod, mod, 1);
      vector<vec> as;
      ll n = 0;
      for (auto &&x: fac) {
          ll mod, p, e;
          vec a, b;
          tie(mod, p, e) = x;
          auto ss = s;
          for (auto &&x: ss) x %= mod;
          tie(a, b) = prime_power(ss, mod, p, e);
          as.emplace_back(a);
          n = max(n, (ll) a.size());
      }
      vec a(n), c(as.size()), m(as.size());
<<<<<<< HEAD
=======
 
>>>>>>> dev
      for (ll i = 0; i < n; ++i) {
          for (ll j = 0; j < as.size(); ++j) {
              m[j] = get<0>(fac[j]);
              c[j] = i < as[j].size() ? as[j][i] : 0;
          }
          a[i] = crt(c, m);
      }
      return a;
  }
<<<<<<< HEAD
  LinearRecurrence(const vec &s, const vec &c, ll mod):
      init(s), trans(c), mod(mod), m(s.size()) {}
=======
 
  LinearRecurrence(const vec &s, const vec &c, ll mod):
      init(s), trans(c), mod(mod), m(s.size()) {}
 
>>>>>>> dev
  LinearRecurrence(const vec &s, ll mod, bool is_prime = true): mod(mod) {
      vec A;
      if(is_prime) A = BerlekampMassey(s,mod);
      else A = ReedsSloane(s, mod);
      if (A.empty()) A = {0};
      m = A.size() - 1;
      trans.resize(m);
      for (ll i = 0; i < m; ++i) {
          trans[i] = (mod - A[i + 1]) % mod;
      }
      reverse(trans.begin(), trans.end());
      init = {s.begin(), s.begin() + m};
  }
<<<<<<< HEAD
=======
 
>>>>>>> dev
  ll calc(ll n) {
      if (mod == 1) return 0;
      if (n < m) return init[n];
      vec v(m), u(m << 1);
<<<<<<< HEAD
=======
 
>>>>>>> dev
      ll msk = !!n;
      for (ll m = n; m > 1; m >>= 1LL) msk <<= 1LL;
      v[0] = 1 % mod;
      for (ll x = 0; msk; msk >>= 1LL, x <<= 1LL) {
          fill_n(u.begin(), m * 2, 0);
          x |= !!(n & msk);
          if (x < m) u[x] = 1 % mod;
          else { // can be optimized by fft/ntt
              for (ll i = 0; i < m; ++i) {
                  for (ll j = 0, t = i + (x & 1); j < m; ++j, ++t) {
                      u[t] = (u[t] + v[i] * v[j]) % mod;
                  }
              }
              for (ll i = m * 2 - 1; i >= m; --i) {
                  for (ll j = 0, t = i - m; j < m; ++j, ++t) {
                      u[t] = (u[t] + trans[j] * u[i]) % mod;
                  }
              }
          }
          v = {u.begin(), u.begin() + m};
      }
      ll ret = 0;
      for (ll i = 0; i < m; ++i) {
          ret = (ret + v[i] * init[i]) % mod;
      }
      return ret;
  }
<<<<<<< HEAD
=======
 
>>>>>>> dev
  vec init, trans;
  ll mod;
  ll m;
};
ll mod = 9882443533;
<<<<<<< HEAD
=======

>>>>>>> dev
ll Recever(ll a) {
	a %= mod;
	if(a < mod) a += mod;
	return a;
}
<<<<<<< HEAD
vector<ll> a, f;
=======

vector<ll> a, f;

>>>>>>> dev
int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i ++) {
		ll x; scanf("%lld", &x);
		f.push_back(x);
	}
	reverse(f.begin(), f.end());
	for (int i = 1; i <= m; i ++) {
		ll x; scanf("%lld", &x);
		a.push_back(x);
	}
    LinearRecurrence lr(a, f, mod);
	printf("%lld\n", lr.calc(n));
	return 0;
}