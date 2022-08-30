#include<iostream>
#include<algorithm>
#include<cstring>
#include<fstream>

#define MAXN 100000
#define MAXT 20000
#define INT_MAX		2147483647

using namespace std;

struct _functionF{					//F(i) = i的约数和
	int i;
	int val;
}F[MAXN+5];

struct _query{
	int id;
	int m, n, a;
	int ans;
}query[MAXT+5];

template <typename T>
class FenwickTree{
public:
	T val[MAXN+10];
public:
	int clear(){
		memset(val, 0x00, sizeof(val));
		return 0;
	}
	FenwickTree(){
		memset(val, 0x00, sizeof(val));
	}
	inline int lowbit(int A){
		return (A&(-A));
	}

	T  add(int index, T val1){
		while(index <= MAXN){
			val[index] += val1;
			index += lowbit(index);
		}
		return val1;
	}

	T sum(int index){
		T val1 = 0;
		while(index > 0){
			val1 += val[index];
			index -= lowbit(index);
		}
		return val1;
	}

	int TestOutput(int end){
		ofstream fout("out.out", ios::trunc);
		for(int i = 1; i <= end; i++){
			fout << val[i] << endl;
		}
		fout.close();
		return 0;
	}
};
FenwickTree<int> sum;
////////////////////////////////////////////////////////////////////////////////////////////////////////////
int mu[MAXN+10], prime[MAXN+10];
bool vis[MAXN+10];
////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool compF(_functionF A, _functionF B){
	return A.val < B.val;
}
bool compQval(_query A, _query B){
	return A.a < B.a;
}
bool compQid(_query A, _query B){
	return A.id < B.id;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
int getMu();
int getAns(int, int);
////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]){
	getMu();
	int t, Max(0);
	cin >> t;
	for(int i = 1; i <= t; i++){
		cin >> query[i].n >> query[i].m >> query[i].a;
		query[i].id = i;
		if(query[i].n > query[i].m)	swap(query[i].n , query[i].m);
		Max = max(Max, query[i].n);
	}
	//cout << Max << endl;
	sort(query+1, query+t+1, compQval);
	sort(F+1, F+1+Max, compF);

	/*for(int i = 1; i <= 100; i++)
		cout << F[i].i << " " << F[i].val << endl;*/

	int pos = 0;
	for(int i = 1; i <= t; i++){
//		sum.clear();
		while(F[pos+1].val <= query[i].a && pos+1 <= Max){
			pos++;
//			cout << "Entered" << endl;
			for(int j = F[pos].i; j <= Max; j+= F[pos].i){
				//cout << F[pos].val << mu[j/F[pos].i] << F[pos].i << endl;
				sum.add(j, F[pos].val * mu[j/F[pos].i]);
			}
		}

		//sum.TestOutput(10);
		query[i].ans = getAns(query[i].n, query[i].m);
	}

	sort(query+1, query+t+1, compQid);
	for(int i = 1; i <= t; i++)
		cout << query[i].ans << endl;
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
int getMu(){
	int cnt = 0;
	mu[1] = 1;
	for(int i = 2; i <= MAXN; i++){
		if(!vis[i]){
			prime[++cnt] = i;
			mu[i] = -1;
		}
		for(int j = 1; j <= cnt; j++){
			if(i * prime[j] > MAXN)	break;
			vis[i*prime[j]] = true;
			if(i % prime[j] == 0){
				mu[i*prime[j]] = 0;
				break;
			}else{
				mu[i*prime[j]] = mu[i] * mu[prime[j]];
			}
		}
	}
	for(int i = 1; i <= MAXN; i++){
		F[i].i = i;
		for(int j = i; j <= MAXN; j+=i){
			F[j].val += i;
		}
	}
	//for(int i = 1; i <= 100; i++)
	//	cout << F[i].i << " " << F[i].val << endl;
	return 0;
}

int getAns(int n, int m){
	int ans = 0;
	int last  = 0, t = min(n, m);;
	for(int i = 1; i <= t; i = last+1){
		last = min(n/(n/i), m/(m/i));
		ans += (n/i) * (m/i) * (sum.sum(last) - sum.sum(i-1));
	}
	return ans & INT_MAX;
}
