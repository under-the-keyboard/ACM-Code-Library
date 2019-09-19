int dp[maxn][maxn][2], f[maxn][maxn];
int main() {
    string aa, bb;
    cin >> aa >> bb;
    memset(dp, 0, sizeof(dp));
    memset(f, 0, sizeof(f));
    for (int i = 1; i <= aa.size(); i ++) {
        for (int j = 1; j <= bb.size(); j ++) {
            if(aa[i - 1] == bb[j - 1]) f[i][j] = f[i - 1][j - 1] + 1;
            else f[i][j] = 0;
        }
    }
    for (int i = 1; i <= aa.size(); i ++) {
        for (int j = 1; j <= bb.size(); j ++) {
            if(f[i][j] >= 3) {
                dp[i][j][1] = max(dp[i][j][1], dp[i - 3][j - 3][0] + 3);
                if(f[i][j] > 3) dp[i][j][1] = max(dp[i][j][1], dp[i - 1][j - 1][1] + 1);
            }
            dp[i][j][0] = max(max(dp[i - 1][j][0], dp[i][j - 1][0]), dp[i][j][1]);
        }
    }
    cout << dp[aa.size()][bb.size()][0] << endl;
    return 0;
}
//O(nlogn)
b[1] = h[0];
len = 1;
for (int i = 1; i < cnt; i ++) {
    if(h[i] >= b[len]) b[++len] = h[i];
    else {
        int pos = upper_bound(b+1, b+1+len, h[i] - b;
        b[pos] = h[i];
    }
}
printf("%d\n", len);