//N 个人, 第K 淘汰
long long Josephus(long long N, long long K) {
    if(N == 1) return 0;
    if(N < K) {
        long long ret = 0;
        for (long long i = 2; i <= N; i ++)
            ret = (ret + K) % i;
        return ret;
    }
    long long ret = Josephus(N - N/K, K);
    if(ret < N % K) ret = ret - N % K + N;
    else ret = ret - N % K + (ret - N % K) / (K - 1);
    return ret;
}
