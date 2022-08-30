#include<iostream>
#include<algorithm>
#include<cstdio>

const int MAXN = 10000;
const int PRICNT = 1230;

int prime[PRICNT+5];
bool vist[MAXN+5];
int cnt = 0;

using namespace std;

int sieve(void);
int solve(int);

int main(){
/*	freopen("primelist.text", "w", stdout);
	int cnt = sieve();
	cout << cnt << endl;
	for(int i = 1; i <= cnt; i++)
		cout << prime[i] << endl;
*/
	sieve();
	int in = 0;
	while(1){
		cin >> in;
		if(in == 0)
			break;
		solve(in);
	}

}

int sieve(void){
	cnt = 0;
	for(int i = 2; i <= MAXN; i++){
		if(!vist[i]){
			prime[++cnt] = i;
			vist[i] = true;
		}
		for(int j = 1; j <= cnt; j++){
			int tmp = i * prime[j];
			if(tmp > MAXN) break;
			vist[tmp] = true;
			if(i % prime[j] == 0)
				break;
		}
	}
	return cnt;
}

int solve(int tar){
	int ans = 0;
	int l = 1, r = 1;
	int tmp = 0;
	while(true){
		while(tmp < tar && r <= cnt){
			tmp += prime[r++];
		}
		if(tmp < tar)	
			break;
		if(tmp == tar)
			ans++;
		tmp -= prime[l++];
	}
	cout << ans << endl;
	return ans;
}
