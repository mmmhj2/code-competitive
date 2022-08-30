#include <cstdio>
#include <cmath>
#include <cstring>

const double EulerMascheroni = 0.57721566490153286060651209;
int n;double ans[1000005];

int main(){
	for(int i = 1; i <= 1000000; i++)
		ans[i] = ans[i-1] + 1.0/i;
	while(scanf("%d" ,&n) == 1){
		if(n > 1000000)
			printf("%.4lf\n", EulerMascheroni + log(n * 1.0) + 1.0 / (2 * n));
		else
			printf("%.4lf\n", ans[n]);
	}
	return 0;
}
