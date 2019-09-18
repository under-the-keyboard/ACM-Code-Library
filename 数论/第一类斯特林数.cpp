#include<bits/stdc++.h>
#define ri register int
using namespace std;
const int rlen=1<<18|1;
const int mod=998244353;
inline int add(const int&a,const int&b){return a+b>=mod?a+b-mod:a+b;}
inline int dec(const int&a,const int&b){return a>=b?a-b:a-b+mod;}
inline int mul(const int&a,const int&b){return (long long)a*b%mod;}
inline int ksm(int a,int p){int ret=1;for(;p;p>>=1,a=mul(a,a))if(p&1)ret=mul(ret,a);return ret;}
const int N=4e5+5;
int n,A,B,a[N],b[N],pos[N],pw[N],tmp[N],fac[N],ifac[N],lim,tim;
inline void init(const int&up){
	lim=1,tim=pos[0]=0;
	while(lim<=up)lim<<=1,++tim;
	for(ri i=0;i<lim;++i)pos[i]=(pos[i>>1]>>1)|((i&1)<<(tim-1));
}
inline void ntt(int *a,const int&type){
	for(ri i=0;i<lim;++i)if(i<pos[i])swap(a[i],a[pos[i]]);
	int wn,w,a0,a1,typ=type==1?3:(mod+1)/3,mult=(mod-1)>>1;
	for(ri mid=1;mid<lim;mid<<=1,mult>>=1){
		wn=ksm(typ,mult);
		for(ri j=0,len=mid<<1;j<lim;j+=len){
			w=1;
			for(ri k=0;k<mid;++k,w=mul(w,wn)){
				a0=a[j+k],a1=mul(a[j+k+mid],w);
				a[j+k]=add(a0,a1),a[j+k+mid]=dec(a0,a1);
			}
		}
	}
	if(type==-1)for(ri i=0,inv=ksm(lim,mod-2);i<lim;++i)a[i]=mul(a[i],inv);
}
inline void mul(int *a,int *b){
	ntt(a,1),ntt(b,1);
	for(ri i=0;i<lim;++i)b[i]=mul(a[i],b[i]);
	ntt(b,-1);
}

inline void solve(int len){
	if(len==1){a[1]=1;return;}
	if(len&1){
		solve(len-1);
		for(ri i=len;i;--i)a[i]=add(a[i-1],mul(a[i],len-1));
		return;
	}
	solve(len>>1);
	init(len);
	int mid=len>>1;
	pw[0]=1;
	for(ri i=1;i<=mid;++i)pw[i]=mul(pw[i-1],mid);
	for(ri i=0;i<=mid;++i)tmp[i]=mul(a[i],fac[i]),b[i]=mul(pw[i],ifac[i]);
	for(ri i=mid+1;i<lim;++i)tmp[i]=b[i]=0;
	reverse(b,b+mid+1);
	mul(tmp,b);
	for(ri i=0;i<=mid;++i)b[i]=mul(b[i+mid],ifac[i]);
	for(ri i=mid+1;i<lim;++i)b[i]=0;
	mul(b,a);
}
inline int C(int n,int m){return n<m?0:mul(mul(fac[n],ifac[m]),ifac[n-m]);}
int main(){
    scanf("%d %d", &n, &A);
	if(n==1)return cout<<(A==1&&B==1),0;
	(fac[0]=fac[1]=ifac[0]=ifac[1]=1);
	for(ri i=2;i<=n;++i)fac[i]=mul(fac[i-1],i),ifac[i]=mul(ifac[mod-mod/i*i],mod-mod/i);
	for(ri i=2;i<=n;++i)ifac[i]=mul(ifac[i-1],ifac[i]);
	solve(n);
    for (int i = 1; i <= n; i ++)
        cout << a[i] << endl;
	return 0;
}
