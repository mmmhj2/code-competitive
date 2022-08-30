#include<iostream>
using namespace std;

typedef unsigned long long int u_64i;

const int MAXN = 1000000;

int mu[MAXN+5], prime[MAXN];
bool vis[MAXN+5];

int CalcMu(){
    int cnt = 0;
    mu[1] = 1;
    for(int i = 2; i <= MAXN; i++){
        if(!vis[i]){
            prime[++cnt] = i;
            mu[i] = -1;
        }
        for(int j = 1; j <= cnt; j++){
            int t = i * prime[j];
            if(t > MAXN)    break;
            vis[t] = true;
            if(i % prime[j] == 0){
                mu[t] = 0;
                break;
            }else{
                mu[t] = -mu[i];
            }
        }
    }
}

int main(int argc, char** argv){
    int t;
    cin >> t;
    CalcMu();
    while(t--){
        u_64i q, sum = 3;
        cin >> q;
        for(u_64i i = 1; i <= q; i++){
            sum += mu[i] * (q/i) * (q/i) * (q/i+3);
        }
        cout << sum << endl;
    }
}
