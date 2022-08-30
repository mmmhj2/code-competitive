#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
//#include <cstdlib>
using namespace std;

int m[11],n,ans = 0x7fffffff,a,b;

int sumArray(int ar[], int lb, int rb){
	int sum = 0;
	for(int i = rb-lb; i >= 0; i--){
		sum = sum + ar[rb-i]*pow(10.0,(double) i);
	}
	return sum;
}

int main(){
	/*int t[5] = {1,2,3,4,5};
	cout << sumArray(t,1,4);*/
	cin >> n;
	while(n--){
		ans = 0x7fffffff;
		int l = 0;
		char t[22];
		fflush(stdin);
		scanf("%[^\n]", t);
		//cout << t << endl;
		l = strlen(t);
		//cout << l << endl;
		
		int t1 = 0;
		for(int i = 0; i < l; i++){
			if('0' <= t[i] && t[i] <= '9'){
				m[t1++] = t[i] - '0';
				//cout << m[t1-1];
			}
		}
		l = (l+1)/2;
		//system("pause");
		do{
			if(((m[0] == 0) && ((0-l/2) != 1)) || ((m[l/2] == 0 && ((l-l/2) != 1))))
				continue;
			/*cout << endl;
			for(int i = 0; i < l; i++)
				cout << m[i];*/
			//cout << l/2;	
			a = sumArray(m, 0, l/2-1);
			//cout << "A: " <<a;
			b = sumArray(m, l/2, l-1);
			//cout << "B: " <<b;
			ans = min(ans,abs(a-b));
		}while(next_permutation(m,m+l));
		cout << ans << endl;
	}
}
