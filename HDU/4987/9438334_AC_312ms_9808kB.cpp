#include <iostream>
#include <cmath>
#include <cstring>
#include <iomanip>

using namespace std;
const double pre = 1e-13;

double dp[1000005] = {1};
int m, n;
bool flag;

int main(){
	while(cin >> m >> n){
	    flag = false;
		memset(dp, 0x00, sizeof(dp));
		dp[0] = 1;dp[1] = 1.0/m;
		for(int i = 2; i <= n; i++){
			dp[i] = dp[i-1] + dp[i-1]* (1.0/m);
			if(i-1 >= m)
				dp[i] -= dp[i-m-1]/m;
			if(fabs(dp[i] - dp[i-1]) < pre){
				cout << fixed << setprecision(5) << dp[i] ;
				flag = true;
				break;
			}
		}
		if(!flag) cout << fixed << setprecision(5) << dp[n];
        cout << endl;
	}

	return 0;
}
