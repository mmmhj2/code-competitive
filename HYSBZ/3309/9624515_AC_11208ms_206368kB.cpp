#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstdio>
using namespace std;

const int MAXN = 10000000;

typedef unsigned long long int ui64;
typedef long long int i64;

int powdiv[MAXN+5], divmulti[MAXN+5], sum[MAXN+5];
int prime[MAXN+5], g[MAXN+5];
bool vis[MAXN+5];

class _sieveFunc{
public:
	virtual int sieve() = 0;
};

class _mainClass : public _sieveFunc{
public:
	int sieve();
	_mainClass(){sieve();};
	~_mainClass(){};
	ui64 process(int, int);
};


int main(){
	_mainClass MainClass;
	int a, b, t;
	scanf("%d", &t);
	while(t--){
		scanf("%d%d", &a, &b);
		printf("%lld\n", MainClass.process(a, b));
	}
}

int _mainClass :: sieve(){
	int cnt = 0;
	for(int i = 2; i <= MAXN; i++){
		if(!vis[i]){
			prime[++cnt] = i;
			g[i] = powdiv[i] = 1;
			divmulti[i] = i;
		}
		for(int j = 1; j <= cnt; j++){
			if(1ll * prime[j] * i > MAXN)	break;
			
			int t = i * prime[j];
			vis[t] = true;
			
			if(i % prime[j] == 0){
				powdiv[t] = powdiv[i] + 1;
				divmulti[t]= divmulti[i] * prime[j];
				if(i == divmulti[i])
					g[t] = 1;
				else
					g[t] = (powdiv[i/divmulti[i]] == powdiv[t] ? -g[i / divmulti[i]]: 0);
				break;
			}else{
				powdiv[t] = 1;
				divmulti[t] = prime[j];
				g[t] = (powdiv[i] == 1? -g[i]: 0);
			}
		}
		sum[i] = sum[i-1] + g[i];
	}
	return 0;
}

ui64 _mainClass :: process(int x, int y){
	ui64 res = 0;
	int last = 0;
	int t = min(x, y);
	for(int i = 1;  i <= t; i = last + 1){
		last = min(x/(x/i), y/(y/i));
		res +=1ll * (x/i) * (y/i) * (sum[last] - sum[i-1]);
	}
	return res;
}
