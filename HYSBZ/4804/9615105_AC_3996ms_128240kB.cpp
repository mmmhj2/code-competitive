#include<iostream>
#include<cmath>
#include<cstdio>
#include<time.h>
#define SUCCEEDED 0
using namespace std;

typedef unsigned long long int ui64;
typedef long long int i64;

const int MAXN = 1e+7;
int prime[MAXN+5], n;
ui64 phi[MAXN+5];
bool vist[MAXN+5];

int getPhi(){
	phi[1] = 1;
	int cnt = 0;
	for(int i = 2; i <= MAXN; i++){
		if(!vist[i]){
			prime[++cnt] = i;
			phi[i] = i-1;
		}
		for(int j = 1; j <= cnt; j++){
			if(i*prime[j] > MAXN)	break;
			int t = i*prime[j] ;
			vist[t] = true;
			if(i % prime[j] == 0){
				phi[t] = phi[i] * prime[j];
				break;
			}else{
				phi[t] = phi[i] *(phi[prime[j]]);
			}
		}
	}
	for(int i = 2; i <= MAXN; i++)
		phi[i] += phi[i-1];
	return SUCCEEDED;
}


int main(int argc, char **argv){
	getPhi();
//	freopen("headcalc.in", "r", stdin);
//	freopen("headcalc.out","w", stdout);
	int t, n;
	cin >> t;
	while(t--){
		cin >> n;
		ui64 ans = 0;
		int last = 0;
		for(int i = 1; i <= n; i = last + 1){
			last = n/(n/i);
			ans += phi[n/i] * (phi[last] - phi[i-1]);
		}
		cout << ans*2 - phi[n] << endl;
	}
	//cout << clock()/ (double) CLOCKS_PER_SEC << endl;
}
