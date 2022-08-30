#include<cstdio>
#include<algorithm>

#define MAXN 10000000
#define MODNUM 20101009
#define Sum(x,y) (1ll*x*(x+1)/2%MODNUM*(1ll*y*(y+1)/2%MODNUM)%MODNUM)

using namespace std;

int mu[MAXN+10] = {0, 1}, prime[MAXN+10], sum[MAXN+10] = {0, 1};
bool vis[MAXN+10];
int N, M;

int calcSum(int x,int y){
	return (((1ll*x*(x+1)/2%MODNUM)*(1ll*y*(y+1)/2%MODNUM))%MODNUM);
}

int getMu(){
	int cnt=0;
	int nmin=min(N, M);
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
	int t = min(x,y);
	for(int i=1;i<=t;i=last+1){
		last = min(x/(x/i),y/(y/i));
		ret = (ret+(((sum[last]-sum[i-1])%MODNUM)*Sum(x/i,y/i))%MODNUM + MODNUM)%MODNUM;
	}
	return ret;
}


int calcAns(){
	int ans = 0, last = 0;
	int t = min(N, M);
	for(int i=1;i<=t;i=last+1){
		last = min(N/(N/i), M/(M/i));
		ans = (ans+((1ll*(i+last)*(last-i+1)/2)%MODNUM*(calcF(N/i,M/i))))%MODNUM;
	}
	return ans;
}


int main(){
	scanf("%d%d", &N, &M);
	getMu();
	int ans = 0;
	int last = 0;
	for(int i = 1; i <= min(N, M); i = last+1){
		last = min(N/(N/i), M/(M/i));
		ans = (ans+ (1ll*(i+last)*(last-i+1)/2)%MODNUM * calcF(N/i, M/i)) % MODNUM;
	}
	printf("%d", ans);
}