#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

typedef long long int _i64;

struct _ans{
	_i64 ans, l, r;
	_ans(){
		ans = l = r = 0;
	}
}ans[1500];

void solve(_i64);
void printans(int);

int main(){
	_i64 n;
	cin >> n;
	solve(n);
}

void solve(_i64 n){
	_i64 r = 0, l = 1;
	_i64 sum = 0;
	_i64 sq = (_i64)sqrt(n*1.0);
	int cnt = 0;
	while(true){
		while(sum < n){
			r++;
			sum += r*r;
		}
		if(l > sq)	break;
		if(sum == n){
			ans[cnt].ans = r - l + 1;
			ans[cnt].l = l;
			ans[cnt].r = r;
			cnt++;
		}
		sum -= (l*l);
		l++;
	}
	printans(cnt);
}

void printans(int cnt){
	cout << cnt << endl;
	for(int i = 0; i < cnt; i++){
		cout << ans[i].ans;
		for(int j = ans[i].l; j <= ans[i].r; j++)
			cout << " " << j;
		cout << endl;
	}
}
