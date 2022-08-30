#include<iostream>
#include<cstring>
using namespace std;

const int MAXN = 32;
int C[MAXN+2][MAXN+2];

class	_CCalc{
public:
	_CCalc(){
//		cout << "Calculating Combine" << endl;
		C[0][0] = 1;
		for(int i = 1; i <= MAXN; i++){
			C[i][0] = C[i-1][0];
			for(int j = 1; j <= i; j++){
				C[i][j] = C[i-1][j] + C[i-1][j-1];
			}
		}
	}
};

class	_NumCalc : public _CCalc{
public:
	_NumCalc() : _CCalc(){};
	int NumCalc(int x, int k);
};

class _find : public _NumCalc{
public:
	_find() : _NumCalc(){};
	int find(int, int, int);
};

int main(int argc, char ** argv){
	int t;
	int m, n, k;
	_find MainClass;
	cin >> t;
	while(t--){
		cin >> m >> n >> k;
		if(m < 0){
			m &= ~(1 << 31);
			if(n == 0)	n--, k--;
			n &= ~(1 << 31);
			cout << ((1<<31)|(MainClass.find(m, n, k))) << endl;
		}else{
			if(m == 0)	k--, m++;
			cout << MainClass.find(m, n ,k) << endl;
		}
	}
}

int _NumCalc :: NumCalc(int x, int k){
	int ans = 0, pos = 0, sum = 0;
	bool bit[33] ;
	memset(bit, 0x00, sizeof(bit));
	while(x){
		bit[++pos] = x % 2;
		x /= 2;
	}
	for(int i = pos; i >= 1; i--){
		if(!bit[i])	continue;
		sum += C[i-1][k-ans] ;
		ans++;
		if(ans >= k)	break;
	}
	if(ans == k)	sum ++;
	return sum;
}

int _find :: find(int l, int r, int k){
	int i = 0, num = 0;
	for(i = 1; i < 32; i++){
		num = NumCalc(r, i) - NumCalc(l-1, i);
		if(num >= k)	break;
		k -= num;
	}
	int tl = l;
	while(l <= r){
		int mid = l + (r-l)/2;
		num = NumCalc(mid, i) - NumCalc(tl-1, i);
		if(num >= k)	r = mid-1;
		else	l = mid+1;
	}
	return l;
}
