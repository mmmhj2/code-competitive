#include<iostream>
#include<algorithm>
#define MAXN 500000
using namespace std;

int prime[500010];
int mu[500010] = {0 ,1};
bool vist[500010];
int n;

int euler();
int calc(int, int);

int main(int argc, char* argv[]){
	euler();
	cin >> n;
	int a, b, c, d, k;
	while(n--){
		cin >> a >> b >> c >> d >> k;
		a /= k; b /= k;
		c /= k; d /= k;
		cout << calc(b, d) - calc(a-1, d) - calc(b, c-1) + calc(a-1, c-1) << endl; 
	}
}


int euler(){
	int cnt = 0;
	for(int i = 2; i < 500005; i++){
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
	for(int i = 1; i < 500005; i++){
		mu[i] += mu[i-1];
	}
	return 0;
}

int calc(int x, int y){
	if(x > y) swap(x, y);
	int last = 0; int res = 0;
	for(int i = 1; i <= x; i = last+1){
		last = min(x/(x/i), y/(y/i));
		res += (x/i)*(y/i)*(mu[last] - mu[i-1]); 
	}
	return res;
}
