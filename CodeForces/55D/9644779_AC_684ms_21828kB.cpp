#include<iostream>
#include<cstring>
using namespace std;

int const MOD = 2520;
typedef long long int i64;

int hashTable[2525];
i64 dp[20][50][2525];
int ndiv[20];

i64 gcd(i64 a, i64 b){
	return (b ? gcd(b, a%b) : a);
}

int Hash(){
	int num = 0;
	for(int i = 1; i <= MOD; i++){
		if(MOD % i == 0)
			hashTable[i] = num++;
	}
	return num;
}

int divide(i64 x){
	//cout << endl;
	memset(ndiv, 0x00, sizeof(ndiv));
	int pos = 0;
	while(x){
		ndiv[pos++] = x % 10;
//		cout << ndiv[pos-1];
		x /= 10;
	}
	//cout << endl;
	return pos;
}

i64 memorizedsearching(int len, int num, int lcm, bool end){
	if(len == -1)	return num % lcm == 0;
	if(!end && dp[len][hashTable[lcm]][num] != -1)
		return dp[len][hashTable[lcm]][num];
	i64 ans = 0;	int max = end ? ndiv[len] : 9;
	for(int i = 0; i <= max; i++){
		ans += memorizedsearching(len-1, (num*10 + i) % MOD, (i ? i*lcm / gcd(lcm, i):lcm), end && i == max);
	}
	if(!end)	dp[len][hashTable[lcm]][num] = ans;
	return ans;
}

i64 solve(i64 x){
	int len = divide(x);
	return memorizedsearching(len-1, 0, 1, 1);
}

int main(){
	Hash();
	memset(dp, 0xff, sizeof(dp));
	int t;
	cin >> t;
	while(t--){
		i64 l, r;
		cin >> l >> r;
//		cout << l << r << endl;
		cout << solve(r) - solve(l-1) << endl;
	}
}
