map<long long, long long> Hash;

long long Mul(long long a, long long b, long long p) {
    long long L = a * (b >> 25LL) % p * (1LL << 25) % p;
    long long R = a * (b & ((1LL << 25) - 1)) % p;
    return (L + R) % p;
}

long long Pow(long long a, long long b, long long p) {
    a %= p;
    long long res = 1;
    while(b) {
        if(b & 1) res = Mul(res, a, p);
        a = Mul(a, a, p);
        b >>= 1;
    }
    return res;
}
/*
get ans for a^ans = b % p
*/
long long BSGS(long long a, long long b, long long p) {
    long long m = sqrt(p) + 1;
    long long res = 1;
    for (int j = 0; j <= m; j ++) {
        Hash[Mul(b, res, p)] = j;
        res = Mul(res, a, p);
    }
    for (int i = 1; i <= m; i ++) {
        long long k = Pow(a, i * m, p);
        if(Hash.count(k))
            return i * m - Hash[k];
    }
}

/*
A^{iS-j} =B mod p
A^{iS} = B*A^{j} mod p

A^{iS+j} = B mod p
*/