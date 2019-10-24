<<<<<<< HEAD
=======
#include<bits/stdc++.h>
>>>>>>> dev
#define ljc 167772161 /*原根是3*/ 
#define int long long
#define ll long long
using namespace std;
int n,m,k,r[800006],lim,w[800006],a[800006],b[800006],inv[800006];
inline ll fast_pow(ll a,ll b,ll p){
    ll t=1;a%=p;
    while (b){
        if (b&1) t=t*a%p;
        b>>=1;a=a*a%p;
    }
    return t;
}
inline void NTT(ll f[],int lim,int id){
    for (int i=0;i<lim;i++){
        if (i<r[i]) swap(f[r[i]],f[i]);
    }
    w[0]=1;
    for (int len=1;len<lim;len<<=1){
        ll gen=fast_pow(3,(ljc-1)/(len<<1)*id+ljc-1,ljc);
        for (int i=1;i<len;i++) w[i]=w[i-1]*gen%ljc;
        for (int i=0;i<lim;i+=len<<1){
            ll *f1=f+i,*f2=f1+len;
            for (int j=0;j<len;j++){
                ll x=f1[j]%ljc,y=f2[j]*w[j]%ljc;
                f1[j]=(x+y)%ljc;f2[j]=(x-y+ljc)%ljc;
            }
        }
    }
    if (id==1) return;
    ll Inv=fast_pow(lim,ljc-2,ljc);
    for (int i=0;i<lim;i++) f[i]=f[i]*Inv%ljc;
}
signed main(){
    cin>>n;n++;
    inv[0]=inv[1]=1;
    for (int i=2;i<n;i++) inv[i]=(ljc-(ljc/i)*inv[ljc%i]%ljc)%ljc;
    for (int i=1;i<n;i++) inv[i]=inv[i-1]*inv[i]%ljc;
    for (int i=0,one=1;i<n;one=ljc-one,i++){
        a[i]=one*inv[i]%ljc;b[i]=fast_pow(i,n-1,ljc)*inv[i]%ljc;
    }
    int lim=1,len=0;
    while (lim<=(n<<1)) lim<<=1,len++;
    for (int i=0;i<lim;i++) r[i]=(r[i>>1]>>1)|((i&1)<<(len-1));
    NTT(a,lim,1);NTT(b,lim,1);
    for (int i=0;i<lim;i++) a[i]=a[i]*b[i]%ljc;
    NTT(a,lim,-1);
    for (int i=0;i<n;i++) printf("%lld ",a[i]);
}