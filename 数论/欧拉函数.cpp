int getPhi(int n) {
    int rea = n;
    for (int i = 2; i * i <= n; i ++) {
        if (n % i == 0) {
            rea = rea - rea / i;
            while(n % i == 0) n /= i;
        }
    }
    if(n > 1) rea = rea - rea / n;
    return rea;
}
int phi[maxn];//递推
void getPhi() {
    for (int i = 1; i < maxn; i ++)
        phi[i] = i;
    for (int i = 2; i < maxn; i ++) 
        if(phi[i] == i) 
            for (int j = i; j < maxn; j += i) 
                phi[j] = (phi[j] / i) * (i-1);
} 