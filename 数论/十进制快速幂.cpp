const int maxn = 1e6 + 5; //矩阵
long long mod;
struct Matrix{
    long long mat[2][2];
    Matrix() {memset(mat, 0, sizeof(mat));};
    void init() {
        mat[0][0] = mat[1][1] = 1;
    }
    void init(long long a, long long b) {
        mat[0][0] = 0; mat[0][1] = b;
        mat[1][0] = 1; mat[1][1] = a;
    }
    void operator = (Matrix x) {
        for (int i = 0; i <= 1; i ++)
            for (int j = 0; j <= 1; j ++)
                mat[i][j] = x.mat[i][j];
    }
};
void Print(Matrix x) {
    for (int i = 0; i <= 1; i ++) {
        for (int j = 0; j <= 1; j ++)
            cout << x.mat[i][j] << " ";
        cout << endl;
    }
}
Matrix operator * (Matrix x, Matrix y) {
    Matrix t;
    for (int i = 0; i <= 1; i ++)
        for (int j = 0; j <= 1; j ++)
            for (int k = 0; k <= 1; k ++)
                t.mat[i][j] = (t.mat[i][j] + x.mat[i][k] * y.mat[k][j]) % mod;
    return t;
}
Matrix Ksm(Matrix x, long long b) {
    Matrix t; t.init();
    while(b) {
        if(b & 1) t = t * x;
        x = x * x;
        b >>= 1;
    }
    return t;
}
int main() {
    long long x0, x1, a, b;
    scanf("%lld %lld %lld %lld", &x0, &x1, &a, &b);
    char s[maxn];
    scanf("%s%lld", s, &mod);
    int len = strlen(s);
    reverse(s, s+len);
    Matrix t, ans; t.init(a, b);
    ans.mat[0][0] = x0; ans.mat[0][1] = x1;
    Matrix res;
    res.init();
    for (int i = 0; i < len; i ++) {
        res = res * Ksm(t, s[i]-'0');
        t = Ksm(t, 10);
    }
    ans = ans * res;
    printf("%lld\n", ans.mat[0][0]);
    return 0;
}