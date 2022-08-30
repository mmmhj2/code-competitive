#include <iostream>
#include <ext/pb_ds/tree_policy.hpp>
#include <cmath>
using namespace std;
typedef unsigned long long int ui_64;

ui_64 phi(ui_64 x){
    ui_64 ans = x, sq = sqrt(x);
    for(ui_64 i = 2ll; i <= sq; i++){
        if(x % i == 0)
            ans = ans / i * (i-1);
        while(x % i == 0)
            x /= i;
    }
    if(x > 1)   ans = ans / x * (x-1);
    return ans;
}

int main(int argc, char* argv[]){
    ui_64 n, ans = 0;
    cin >> n;
    for(ui_64 i = sqrt(n); i > 0 ; i --){
        if(n % i == 0){
            ans += i * phi(n/i);
            if(i * i < n)   ans += (n/i)* phi(i);
        }
    }
    cout << ans;
}
