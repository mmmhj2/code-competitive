#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;

int dp[15][15];
int number[15];
int A,B;

int divide(int i);
int countans(int);
int abs(int i);

int main(){
    for(int i = 0; i <= 10; i++)
        dp[1][i] = 1;
    for(int i = 2; i <= 10; i++){
        for(int j = 0; j <= 9; j++){
            for(int k = 0; k <= 9; k++){
                if(abs(k-j) >= 2){
                    dp[i][j] += dp[i-1][k];
                }
            }
        }
    }

    cin >> A >> B;

    int len = divide(A);
    int ans1 = countans(len);

    len = divide(B+1);
    int ans2 = countans(len);

    cout << ans2 - ans1 ;


    return 0;
}

int abs(int i){
    return abs(double(i));
}

int divide(int i){
    int cnt = 0;
    while(i){
        number[++cnt] = i % 10;
        //cout << number[cnt];
        i /= 10;
    }
//    cout << endl;
    return cnt;
}

int countans(int len){
    int ans = 0;
    for(int i = 1; i < len; i++)
        for(int j = 1; j <= 9; j++)
            ans += dp[i][j];
    for(int i = 1; i < number[len] ; i++)
        ans += dp[len][i];
    for(int i = len-1; i >= 1; i--){
        for(int j = 0; j < number[i]; j++){
            if(abs(number[i+1] - j) >= 2){
                ans += dp[i][j];
            }
        }
        if(abs(number[i+1] - number[i]) < 2)    break;
    }
    return ans;
}
