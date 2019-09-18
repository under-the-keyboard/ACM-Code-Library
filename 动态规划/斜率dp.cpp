/*
序列C_i，分为m段，每段权值(\sum C_i)^2+M
求最小权值和
*/

long long dp[maxn], q[maxn];
long long sum[maxn];
long long head, tail, n, m;
long long getDp(long long i, long long j) {
    return dp[j] + m + (sum[i] - sum[j]) * (sum[i] - sum[j]);
}
long long getUp(long long j) {
    return dp[j] + sum[j] * sum[j];
}
long long getDown(long long j) {
    return 2 * sum[j];
}
double Calc(long long x, long long y) {
    if(getDown(x) == getDown(y)) return -1e9;
    return 1.0 * (getUp(x) - getUp(y)) / (getDown(x) - getDown(y));
}
int main() { 
    while(~scanf("%lld %lld", &n, &m)) {
        for (long long i = 1; i <= n; i ++)
            scanf("%lld", &sum[i]);
        sum[0] = dp[0] = 0;
        for (long long i = 1; i <= n; i ++)
            sum[i] += sum[i-1];
        head = tail = 1;
        for (long long i = 1; i <= n; i ++) {
            while(head < tail && Calc(q[head+1], q[head]) <= 1.0 * sum[i])
                head ++;
            dp[i] = getDp(i, q[head]);
            while(head < tail && Calc(i, q[tail]) <= Calc(q[tail], q[tail-1])) tail --;
            q[++tail] = i;
        }
        printf("%lld\n", dp[n]);
    }
    return 0;
}