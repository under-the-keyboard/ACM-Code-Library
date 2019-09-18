int SG[maxn], S[maxn];
int f[maxn];

void ff() {
    f[0] = 1;
    for (int i = 1; i <= 10; i ++)
        f[i] = f[i-1] * 2;
}
/*
f是每一次走的步数
*/

void getSG(int n) {
    ff();
    for (int i = 1; i <= n; i ++) {
        memset(S, 0, sizeof(S));
        for (int j = 0; f[j] <= i && j <= 10; j ++) 
            S[SG[i-f[j]]] = 1;
        for (int j = 0; ; j ++) 
            if(!S[j]) {
                SG[i] = j;
                break;
            }
    }
}

int main() { 
    int n;
    getSG(1000);
    while(cin >> n) {
        if(SG[n]) cout << "Kiki\n";
        else cout << "Cici\n";
    }   
    return 0;
}
