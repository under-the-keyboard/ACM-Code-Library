int dp[2][1<<5];
int n, m, cur;
<<<<<<< HEAD
void updata(int a, int b) {
    if(b & (1<<m)) dp[cur][b^(1<<m)] = dp[cur][b^(1<<m)] + dp[1-cur][a];
}
=======

void updata(int a, int b) {
    if(b & (1<<m)) dp[cur][b^(1<<m)] = dp[cur][b^(1<<m)] + dp[1-cur][a];
}

>>>>>>> dev
int main(int argc, char const *argv[]) {
    whhile(scanf("%d %d", &n, &m) != EOF && (n || m)) {
	    if(m > n) swap(n, m);
	    memset(dp, 0, sizeof(dp));
	    cur = 0;
	    dp[cur][(1<<m)-1] = 1;
	    for (int i = 0; i < n; i ++) {
	        for (int j = 0; j < m; j ++) {
	            cur ^= 1;
	            memset(dp[cur], 0, sizeof(dp[cur]));
	            for (int k = 0; k < (1<<m); k ++) {
	                updata(k, k<<1);
	                if(i && !(k & (1<<(m-1)))) updata(k, (k<<1)^(1<<m)^1);
	                if(j && (!(k & 1))) updata(k, (k<<1) ^ 3);
	            }
	        }
	    }
	    printf("%d", dp[cur][(1<<m)-1]);
    }
    return 0;
<<<<<<< HEAD
}
=======
}
>>>>>>> dev
