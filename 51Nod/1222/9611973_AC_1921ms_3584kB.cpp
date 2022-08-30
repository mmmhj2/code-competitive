#include<iostream>
#include<cmath>
using namespace std;

typedef unsigned long long int ui64;

const int MAXN = 320000;

int mu[MAXN+5], prime[MAXN+5];
bool vist[MAXN+5];
ui64 a, b;

int getMu(){
	mu[1] = 1;
	int cnt = 0;
	for(int i = 2; i <= MAXN; i++){
		if(!vist[i]){
			prime[++cnt] = i;
			mu[i] = -1;
		}
		for(int j = 1; j <= cnt; j++){
			int t = i * prime[j];
			if(t > MAXN)	break;
			vist[t] = true;
			if(i % prime[j] == 0){
				mu[t] = 0;
				break;
			}else{
				mu[t] = -mu[i];
			}
		}
	}
	return 0;
}

ui64 getAns(ui64 n){
	if(n == 0)	return n;
	ui64 sq = sqrt(n);
	ui64 res = 0, tmp = 0;
	for(ui64 k = 1; k <= sq; k++){
		if(mu[k]){
			tmp = 0;
			ui64 nk2 = n/(k*k);
			for(ui64 i = 1; i*i*i <= nk2; i++){
				for(ui64 j = i+1; j*j*i <= nk2; j++){
					tmp += (nk2/(i*j)-j) * 6 + 3;
				}
				tmp += (nk2/(i*i)-i) * 3;
				tmp++;
			}
			res += tmp * mu[k];
		}
	}
	return (res+n)/2;
}

int main(){
	getMu();
	cin >> a >> b;
	cout << getAns(b) - getAns(a-1) << endl;
	return 0;
}
