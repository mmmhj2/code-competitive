
#include <algorithm>
#include <iostream>
#include <iterator>
#include <cstring>
#include <cstdio>
#include <vector>
#include <set>
using namespace std;

/*
[1, 4]	    0<N<=1000	    0<=S<=2^8	0<=Ti<=2^8	        0<=Fi<=2^8
[5, 12]	    0<N<=300000     0<=S<=2^8	0<=Ti<=2^8	        0<=Fi<=2^8
[13, 20]	0<N<=100000     0<=S<=2^8	-(2^8)<=Ti<=2^8     0<=Fi<=2^8
*/

typedef long long i64;
const int MAXN = 300000 + 50;

int N, S;
i64 F[MAXN], T[MAXN], dp[MAXN];
i64 MonoQueue[MAXN];

// Y(i)=dp[j]-F[n]*T[j]+F[j]*T[j]-s*F[j]
inline i64 getY(int id)
{
    return dp[id] - F[N] * T[id] + F[id] * T[id] - F[id] * S;
}
inline bool check(int i, int mid)
{
    return 1LL * (F[MonoQueue[mid+1]] - F[MonoQueue[mid]]) * T[i] \
           <= getY(MonoQueue[mid+1]) - getY(MonoQueue[mid]);
}

// O(N*logN)
void runDP()
{
    int head(0), tail(0);

    for(int i = 1; i <= N; i++)
    {
        int L = head, R = tail - 1, ans = tail;

        while(L <= R)
        {
            int mid = (L + R) >> 1 ;
            //cerr << "Middle : " << mid << endl ;
            if(check(i, mid))
                ans = mid,
                R = mid-1;
            else
                L = mid+1;
        }
        //cerr << L << " " << R << " " << ans << endl ;

        int t = MonoQueue[ans];
        dp[i] = dp[t] + (F[N] - F[t]) * (T[i] - T[t] + S);

        while(1LL * (getY(MonoQueue[tail]) - getY(MonoQueue[tail-1])) * \
                (F[i] - F[MonoQueue[tail]]) >= \
                1LL * (getY(i) - getY(MonoQueue[tail])) * \
                (F[MonoQueue[tail]] - F[MonoQueue[tail-1]]))
        {
            if(head >= tail)
                break;
            tail--;
        }
        MonoQueue[++tail] = i;

        //cerr << "Current MonoQueue : " << head << " " << tail << endl ;
        //copy(&MonoQueue[head], &MonoQueue[tail], ostream_iterator <int> (cerr, " "));
        //cerr << endl ;
    }
}

int main()
{
    cin >> N >> S ;

    for(int i = 1; i <= N; i++)
        cin >> T[i] >> F[i],
            T[i] += T[i-1], F[i] += F[i-1];

    runDP();

    cout << dp[N] << endl ;
    return 0;
}
