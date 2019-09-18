long long dfs(long long pos, long long m, long long status, bool limit) {
    if(!pos) return status == 2 && m == 0;//如果pos（位数）为0，即最后一位，并且前面对13取模的值为0
    if(!limit && dp[pos][m][status]) return dp[pos][m][status];//这时前面的所有位数遍历完，并且dp[pos][m][status]有值，即搜索过，直接输出
    long long end = limit ? num[pos] : 9;//上界，limit 表示前面的数都是极限值
    long long sum = 0;
    for (long long i = 0; i <= end; i ++) {
        long long a = m;
        long long flag = status;
        if(flag == 0 && i == 1) flag = 1;
        if(flag == 1 && i == 3) flag = 2;
        if(flag == 1 && i != 1 && i != 3) flag = 0;
        sum += dfs(pos - 1, (a * 10 + i) % 13, flag, limit && i == end);
    }
    return limit ? sum : dp[pos][m][status] = sum;
}

long long solve(long long n) {
    num[0] = 0;
    memset(dp, 0, sizeof(dp));
    while(n) {
        num[++ num[0]] = n % 10;
        n /= 10;
    }
    return dfs(num[0], 0, 0, 1);
}
