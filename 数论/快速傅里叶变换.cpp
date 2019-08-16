const int maxn = 5e5 + 5;
const int inf = 0x3f3f3f3f;
const int mod = 1e9 + 7;
typedef complex<double> cp;
const double PI = acos(-1);
char sa[maxn], sb[maxn];
int n = 1, lena, lenb, res[maxn];
cp a[maxn], b[maxn], omg[maxn], inv[maxn];
void init() {
    for (int i = 0; i < n; i ++) {
        omg[i] = cp(cos(2*PI*i/n), sin(2*PI*i/n));
        inv[i] = conj(omg[i]);
    }
}
void fft(cp *a, cp *omg) {
    int lim = 0;
    while((1<<lim) < n) lim++;
    for (int i = 0; i < n; i ++) {
        int t = 0;
        for (int j = 0; j < lim; j ++)
            if((i>>j) & 1) t |= (1<<(lim-j-1));
        if(i < t) swap(a[i], a[t]);
    }
    for (int l = 2; l <= n; l *= 2) { 
        int m = l / 2;
        for (cp *p = a; p != a + n; p += l) 
            for (int i = 0; i < m; i ++) {
                cp t = omg[n/l*i] * p[i+m];
                p[i+m] = p[i] - t;
                p[i] += t;
            }
    }
}
int main() {
    scanf("%d", &n);
    scanf("%s%s", sa, sb);
    lena = lenb = n;
    n = 1;
    while(n < lena + lenb) n <<= 1;
    for (int i = 0; i < lena; i ++) 
        a[i].real(sa[lena-1-i] - '0');
    for (int i = 0; i < lenb; i ++)
        b[i].real(sb[lenb-1-i] - '0');
    init();
    fft(a, omg);fft(b, omg); 
    for (int i = 0; i < n; i ++) 
        a[i] *= b[i];
    fft(a, inv);
    for (int i = 0; i < n; i ++) {
        res[i] += floor(a[i].real()/n + 0.5);
        res[i+1] += res[i] / 10;
        res[i] %= 10;
    }
    int pos = n - 1;
    while(!res[pos]) pos--;
    for (int i = pos; i >= 0; i --) printf("%d", res[i]);
    puts("");
    return 0;
}