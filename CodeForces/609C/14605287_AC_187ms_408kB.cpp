#include <algorithm>
#include <iostream>
//#include <cassert>
#include <cmath>
using namespace std;

const int MAXN = 100000 + 5;

int avg;
int N, sum, ans;
int M[MAXN];

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++)
        cin >> M[i], avg += M[i], sum += M[i];
    avg /= N;

    sort(&M[1], &M[N+1], greater<int>());
    //assert(M[1] >= M[2]);

    if(sum - avg * N == 0)
    {
        for(int i = 1; i <= N; i++)
            if(M[i] > avg)
                ans += M[i] - avg;
    }
    else
    {
        int deviate = sum - avg * N;
        //cerr << deviate << endl ;
        for(int i = 1; i <= N; i++)
        {
            if(deviate > 0 && M[i] > avg + 1)
            {
                deviate--;
                ans += M[i] - avg - 1;
            }
            else if(deviate == 0 && M[i] > avg)
                ans += M[i] - avg;
        }
    }
    cout << ans << endl ;
}
