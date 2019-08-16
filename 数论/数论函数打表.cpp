int phi[maxn], prime[maxn], tot;//线性打欧拉函数
bool vis[maxn];
void init() {
    phi[1] = 1;
    for (int i = 2; i < maxn; i ++) {
        if(!vis[i]) {
            prime[++tot] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= tot; j ++) {
            if(i * prime[j] >= maxn) break;
            vis[i*prime[j]] = 1;
            if(i % prime[j] == 0) {
                phi[i*prime[j]] = phi[i] * prime[j];
                break;
            }
            phi[i*prime[j]] = phi[i] * phi[prime[j]];
        }
    }
}
bool vis[maxn];
int mu[maxn], prime[maxn];
void Mobius() {//线性打莫比乌斯函数
    mu[1] = 1;
    int tot = 0;
    for (int i = 2; i < maxn; i ++) {
        if(!vis[i]) {
            prime[tot++] = i;
            mu[i] = -1;
        }
        for (int j = 0; j < tot; j ++) {
            if(i * prime[j] >= maxn) break;
            vis[i*prime[j]] = true;
            if(i % prime[j] == 0) {
                mu[i*prime[j]] = 0;
                break;
            }
            mu[i*prime[j]] = -mu[j];
        }
    }
}