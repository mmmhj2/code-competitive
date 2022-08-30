#include<cstdio>
#include<cmath>
using namespace std;
const int maxn = 200000 + 5;
long double logF[maxn*2+1];
 long double logC(int m,int n){
    return logF[m]-logF[n]-logF[m-n];
}
int main()
{
    for(int i=1;i<=maxn*2;i++)
        logF[i]=logF[i-1]+log(i);
    int n,kase=0;
    double p;
    while(scanf("%d%lf",&n,&p)==2){
         double ans=0.0;
        for(int i=1;i<=n;i++){
            long double c = logC(2*n-i,n);
            long double v1=c+(n+1)*log(p)+(n-i)*log(1-p);
            long double v2=c+(n+1)*log(1-p)+(n-i)*log(p);
            ans +=(double) i*(exp(v1)+exp(v2));
        }
        printf("Case %d: %.6lf\n",++kase,ans);
    }
}