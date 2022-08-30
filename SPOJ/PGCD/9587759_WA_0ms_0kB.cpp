#include<iostream>
#include<algorithm>
using namespace std;

typedef unsigned long long int u_i64;

const int MAXN = 10000000;
int mu[MAXN+5], prime[MAXN+5], g[MAXN+5];
int sum[MAXN+5];
bool vist[MAXN+5];
int n;

int sieve(void){
	int cnt = 0;
	mu[1] = 1;
	for(int i = 2; i <= MAXN; i++){
		if(!vist[i]){
			mu[i] = -1;
			vist[i] = true;
			prime[++cnt] = i;
			g[i] = 1;
		}
		for(int j = 1; j <= cnt; j++){
			int t = prime[j] * i;
			if(t > MAXN)	break;
			vist[t] = true;
			if(i % prime[j] == 0){
				mu[t] = 0;
				g[t] = mu[i];
				break;
			}else{
				mu[t] = mu[i] * mu[prime[j]];
				g[t] = mu[i] - g[i];
			}
		}
		sum[i] = sum[i-1] + g[i];
	}
	return 0;
}

u_i64 solve(int n, int m){
	u_i64 ans = 0;
	int t = min(n, m);
	int last  = 0;
	for(int i = 1; i <= t; i = last+1){
		last = min(n/(n/i), m/(m/i));
		ans += (n/i) * (m/i) * (sum[last] - sum[i-1]);
	}
	return ans;
}

int main(int argc ,char ** argv){
	cin >> n;
	sieve();
	int a, b;
	while(n--){
		cin >> a >> b;
		cout << solve(a, b) << endl;
	}
	return 0;
}
