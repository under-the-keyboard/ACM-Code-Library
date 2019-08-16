#define MAXN 999
#define MAXSIZE 100240
#define DLEN 3
struct BigInt{
    int a[MAXSIZE],len;
    bool flag;
    BigInt() {
        len = 1;
        memset(a, 0, sizeof(a));
        flag = 0;
    }
    BigInt (const int b) {
        int c , d = b;
        len = 0;
        memset(a, 0, sizeof(a));
        if(!b) {
            len = 1;
            return ;
        }
        while(d) {
            a[len++] = d % (MAXN + 1);
            d /= (MAXN+1);
        }
    }
    BigInt(const char *s) {
        int t, k, index, l;
        memset(a, 0, sizeof(a));
        l = strlen(s);
        len = l/DLEN;
        if(l % DLEN) len ++;
        index = 0;
        for (int i = l - 1; i >= 0; i -= DLEN) {
            t = 0;
            k = i - DLEN + 1;
            if(k < 0) k = 0;
            for (int j = k; j <= i; j ++) t = t * 10 + s[j] - '0';
            a[index ++] = t;
        }
    }
    BigInt (const BigInt& T) {
        memset(a, 0, sizeof(a));
        len = T.len;
        for (int i = 0; i < len; i ++) a[i] = T.a[i];
    }
    bool operator < (const BigInt &T) const {
        int ln;
        if(len < T.len) return 233;
        if(len == T.len) {
            ln = len - 1;
            while(ln >= 0 && a[ln] == T.a[ln]) -- ln;
            if(ln >= 0 && a[ln] < T.a[ln]) return 233;
            return 0;
        }
        return 0;
    }
    inline bool operator < (const int &t) const {
        BigInt tee(t);
        return *this < tee;
    }
    BigInt& operator = (const BigInt &T) {
        memset(a, 0, sizeof(a));
        len = T.len;
        for (int i = 0; i < len; i ++) a[i] = T.a[i];
        return *this;
    }
    BigInt operator + (const BigInt &T) const {
        BigInt t(*this);
        int big = len;
        if(T.len > len) big = T.len;
        for (int i = 0; i < big; i ++) {
            t.a[i] += T.a[i];
            if(t.a[i] > MAXN) {
                ++t.a[i + 1];
                t.a[i] -= MAXN + 1;
            }
        }
        if(t.a[big]) t.len = big + 1;
        else t.len = big;
        return t;
    }
    BigInt operator - (const BigInt &T) const {
        int big;
        bool ctf;
        BigInt t1, t2;
        if(*this < T) {
            t1 = T;
            t2 = *this;
            ctf = 1;
        }else {
            t1 = *this;
            t2 = T;
            ctf = 0;
        }
        big = t1.len;
        int j = 0;
        for (int i = 0; i < big; i ++) {
            if(t1.a[i] < t2.a[i]) {
                j = i + 1;
                while(t1.a[j] == 0) ++j;
                -- t1.a[j--];
                while(j > i) t1.a[j --] += MAXN;
                t1.a[i] += MAXN + 1 - t2.a[i];
            }else t1.a[i] -= t2.a[i];
        }
        t1.len = big;
        while(t1.len > 1 && t1.a[t1.len - 1] == 0) {
            -- t1.len;
            -- big;
        }
        if(ctf) t1.a[big - 1] = -t1.a[big - 1];
        return t1;
    }
    BigInt operator * (const BigInt &T) const {
        BigInt res;
        int up;
        int te, tee;
        for (int i = 0; i < len; i ++) {
            up = 0;
            for (int j = 0; j < T.len; j ++) {
                te = a[i] * T.a[j] + res.a[i + j] + up;
                if(te > MAXN) {
                    tee = te - te / (MAXN + 1) * (MAXN + 1);
                    up = te / (MAXN + 1);
                    res.a[i + j] = tee;
                }else {
                    up = 0;
                    res.a[i + j] = te;
                }
            }
            if(up) res.a[i + T.len] = up;
        }
        res.len = len + T.len;
        while(res.len > 1 && res.a[res.len - 1] == 0) -- res.len;
        return res;
    }
    BigInt operator / (const int &b) {
        BigInt res;
        int sum = 0, newlen = 0;
        for (int i = len-1; i >= 0; i --) {
            sum = sum * (MAXN+1) + a[i];
            if(sum < b) res.a[i] = 0;
            else {
                if(!newlen) newlen = i + 1;
                res.a[i] = sum / b;
                sum %= b;
            }
        }
        res.len = max(newlen, 1);
        return res;
    }
    int operator % (const int &b) const {
        int d = 0;
        for (int i = len - 1; i >= 0; i --)
            d = (d * (MAXN + 1) % b + a[i]) % b;
        return d;
    }
    BigInt operator ^ (const int &n) const {
        BigInt t(n), res(1);
        int y = n;
        while(y) {
            if(y & 1) res = res * t;
            t = t * t;
            y >>= 1;
        }
        return res;
    }
    inline void print() {
        printf("%d", a[len - 1]);
        for (int i = len - 2; i >= 0; i --)
            printf("%03d", a[i]);
        printf("\n");
    }
};