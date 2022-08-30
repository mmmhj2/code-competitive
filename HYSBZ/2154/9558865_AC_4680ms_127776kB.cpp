#include<cstdio>
#include<algorithm>
#define Sum(x,y) (1ll*x*(x+1)/2%MODNUM*(1ll*y*(y+1)/2%MODNUM)%MODNUM)

//using namespace std;
const int MAXN = 10000000, MODNUM = 20101009;
int mu[MAXN+10], prime[MAXN+10], sum[MAXN+10];
bool vis[MAXN+10];
int N, M;

int getMu(){
	int cnt=0;
	mu[1] = sum[1] = 1;
	int nmin=std::min(N, M);
	for(int i=2;i<=nmin;i++){
		if(!vis[i]){
			vis[i] = true;
			prime[++cnt] = i;
			mu[i] = -1;
		}
		for(int j=1;j<=cnt;j++){
			int t=i*prime[j];
			if(t>nmin)	break;
			vis[t]=true;
			if(i%prime[j]==0){
				mu[t]=0;
				break;
			}else{
				mu[t]=mu[i]*mu[prime[j]];
			}
		}
		sum[i] = (sum[i-1] + 1ll*i*i*mu[i]) % MODNUM;
	}
	return 0;
}
int calcF(int x,int y){
	int ret = 0, last = 0;
	int t = std::min(x,y);
	for(int i=1;i<=t;i=last+1){
		last = std::min(x/(x/i),y/(y/i));
		ret = (ret+(((sum[last]-sum[i-1])%MODNUM)*Sum(x/i,y/i))%MODNUM + MODNUM)%MODNUM;
	}
	return ret;
}
int main(){
	scanf("%d%d", &N, &M);
	getMu();
	int ans = 0;
	int last = 0;
	int t = std::min(N, M);
	for(int i = 1; i <= t; i = last+1){
		last = std::min(N/(N/i), M/(M/i));
		ans = (ans+ (1ll*(i+last)*(last-i+1)/2)%MODNUM * calcF(N/i, M/i)) % MODNUM;
	}
	printf("%d", ans);
}
