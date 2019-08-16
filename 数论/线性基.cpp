struct LB{
    long long b[35], nb[35], tot;
    bool flag;
    LB () {  // 初始化
        memset(b, 0, sizeof(b));
        flag = false;
    }
    LB(const LB& a) {
        for (int i = 0; i < 35; i ++) 
            b[i] = a.b[i];
        flag = a.flag;
    }
    void Ins(long long x) { //插入
        for (int i = 34; i >= 0; i --) 
            if(x & (1ll << i)) {
                if(!b[i]) { b[i] = x; return; }
                x ^= b[i];
            }
        flag = true; //能xor出0
    }
    bool Fin(long long x) {
        if(x == 0 && flag) return true;
        for (int i = 34; i >= 0; i --) 
            if(x >> i) x ^= b[i];
        return x == 0;
    }
    long long getMax(long long x) { // 得到最大值
        long long res = x;
        for (int i = 34; i >= 0; i --) 
            res = max(res, res ^ b[i]);
        return res;
    }
    long long getMin(long long x) { // 得到最大值
        long long res = x;
        for (int i = 0; i <= 34; i ++)
            if(b[i]) res ^= b[i];
        return res;
    }
    long long ReBuild() { // 重新Build 为下面的Kth
        for (int i = 34; i >= 0; i --) {
            if(b[i] == 0) continue;
            for (int j = i - 1; j >= 0; j --) {
                if(b[j] == 0) continue;
                if(b[i] & (1ll << j)) b[i] ^= b[j];
            }
        }
        for (int i = 0; i <= 34; i ++) 
            if(b[i]) nb[tot++] = b[i];
    }
    long long Kth_Max(long long k) { // 得到第k小的数，k>1,
        if(flag) k --;
        if(k == 0) return 0;
        long long res = 0;
        if(k >= (1ll << tot)) return -1;
        for (int i = 34; i >= 0; i --) 
            if(k & (1ll << i)) res ^= nb[i];
        return res;
    }
    LB Corss(LB k) { //求交集
        LB res, tmp = k;
        for (int i = 0; i < 35; i ++) {
            long long x = b[i], y = 0;
            bool vis = false;
            for (int j = 34; j >= 0; j --) {
                if(x >> j) {
                    if(k.b[j]) x ^= k.b[j], y ^= tmp.b[j];
                    else {
                        k.b[j] = x;
                        tmp.b[j] = y;
                        vis = true;
                        break;
                    }
                }
            }
            if(!vis) res.b[i] = y;
        }
        return res;
    }
    LB Merge(LB u) { //合并两个线性集
        LB w = *this;
        for (int i = 34; i >= 0; i--) {
            if(u.b[i] == 0) continue;
            w.Ins(u.b[i]);
        }
        return w;
    }
};