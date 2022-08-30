#include<iostream>
#include<cmath>
#include<fstream>
#include<bits/stdc++.h>
using namespace std;

#define MAXN 500000

typedef long long int ll;

int euler(void);
int primecheck(int);
ll calc(ll);
int mu[500000] = {0, 1};
int prime[500000];
bool vist[500000];
int t;

int main(){
	euler();
	cin >> t;
	while(t--){
		int k;
		cin >> k;
		if(k == 1){
			cout << k << endl;
			continue;
		}
		ll lb = 1,rb = 2000000005;
		ll ans = 0;
		while(lb <= rb){
			ll middle = (lb+rb)>>1;
			//cout << lb << " " << rb << " " << middle << endl;
			int t = calc(middle);
			if(t < k){
				lb = middle+1;
			}if(t > k){
				rb = middle-1;
			}if(t == k){
				ans = middle;
				break;
			}
		}
		cout << ans << endl;
	}
}
	
/*
int primecheck(int x){
	for(int i = 2; i < sqrt(i); i++)
		if(x % i == 0)
			return false;
	return true;
}*/

int euler(){
	int cnt = 0;
	for(int i = 2; i < 400000; i++){
		if(/*primecheck(i) && */!vist[i]){
			prime[++cnt] = i;
			mu[i] = -1;
			vist[i] = true;
		}
		for(int j = 1; j <= cnt; j++){
			if(i * prime[j] > MAXN)	break;
			vist[i * prime[j] ] = true;
			if(i % prime[j] == 0)	{
				mu[i * prime[j]] = 0;
				break;
			}else{
				mu[i * prime[j]] = mu[i] * mu[prime[j]];
			}
		}
	}
	return 0;
}

ll calc(ll x){
	ll res = 0;
	int sq = sqrt(x);
	for(int i = 1; i <= sq; i++)
		res += mu[i]*(x/(i*i));
	return res;
}
