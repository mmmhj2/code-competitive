#include<iostream>
#include<algorithm>
#define MAXN 50005
using namespace std;

int prime[MAXN+5];
int mu[MAXN+5] = {0 ,1};
bool vist[MAXN+5];
int n;

int euler();
int calc(int, int, int);

int main(int argc, char* argv[]){
	euler();
	cin >> n;
	int a, b, c, d, k;
	while(n--){
		cin >> a >> b >> c >> d >> k;
		cout << calc(b, d, k) - calc((a-1), d, k) - calc(b, (c-1), k) + calc((a-1), (c-1), k) << endl; 
	}
}


int euler(){
	int cnt = 0;
	for(int i = 2; i <= MAXN; i++){
		if(!vist[i]){
			vist[i] = true;
			prime[++cnt] = i;
			mu[i] = -1;
		}
		for(int j = 1; j <= cnt; j++){
			if(1LL * i * prime[j] > 1LL * MAXN)	break;
			vist[i*prime[j]] = true;
			if(i % prime[j] == 0){
				mu[i * prime[j]] = 0; 
				break;
			}else{
				mu[i * prime[j]] = mu[i] * mu[prime[j]];
			}
		}
	}
	for(int i = 1; i <= MAXN; i++)
		mu[i] += mu[i-1];
	return 0;
}

int calc(int x, int y, int k){
	x /= k; y /= k;
	if(x > y) swap(x, y);
	int last = 0; int res = 0;
	for(int i = 1; i <= x; i = last+1){
		last = min(x/(x/i), y/(y/i));
		res += (x/i)*(y/i)*(mu[last] - mu[i-1]); 
	}
	return res;
}
