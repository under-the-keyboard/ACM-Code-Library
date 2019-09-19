#define ll long long
const int maxn = 1e6;
const ll mod = 998244353;
struct Matrix{
    ll mat[2][2];
    Matrix() {memset(mat, 0, sizeof(mat));};
    void init() {
        mat[0][0] = mat[1][1] = 1;
    } 
    void init(ll a, ll b) {
        mat[0][0] = 0; mat[0][1] = b;
        mat[1][0] = 1; mat[1][1] = a;
    }
    void operator = (Matrix x) {
        for (int i = 0; i <= 1; i ++)
            for (int j = 0; j <= 1; j ++)
                mat[i][j] = x.mat[i][j];
    }
};
Matrix operator * (Matrix x, Matrix y) {
    Matrix t;
    for (int i = 0; i <= 1; i ++)
        for (int j = 0; j <= 1; j ++)
            for (int k = 0; k <= 1; k ++)
                t.mat[i][j] = (t.mat[i][j] + x.mat[i][k] * y.mat[k][j]) % mod;
    return t;
}
Matrix pre[4][2*maxn+10];
ll Ksm(ll b) {
    Matrix t; t.init();
    int cnt = 0;
    while(b && cnt < 3) {
        ++ cnt;
        ll pt = b % maxn;
        if(cnt == 3) pt = b;
        t = t * pre[cnt][pt];
        b /= maxn;
    }
    Matrix ans; 
    ans.mat[0][0] = 0; ans.mat[0][1] = 1;
    ans = ans * t;
    return ans.mat[0][0];
}
void init() {
    Matrix t; t.init(3, 2);
    pre[1][1] = t; pre[1][0].init();
    for (int i = 2; i <= maxn; i ++) pre[1][i] = pre[1][i-1] * pre[1][1];
    pre[2][1] = pre[1][maxn]; pre[2][0].init();
    for (int i = 2; i <= maxn; i ++) pre[2][i] = pre[2][i-1] * pre[2][1];
    pre[3][1] = pre[2][maxn]; pre[3][0].init();
    for (int i = 2; i <= 2* maxn; i ++) pre[3][i] = pre[3][i-1] * pre[3][1];
}
int main() {
    init();
    ll n, q;
    scanf("%lld %lld", &n, &q);
    ll ans = 0;
    for (int i = 1; i <= n; i ++) {
        ll a = Ksm(q);
        q = q ^ (a * a);
        ans ^= a;
    }
    printf("%lld\n", ans);
    return 0;
}