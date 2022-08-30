#include <algorithm>
#include <iostream>
#include <iomanip>
#include <complex>
#include <cfloat>
using namespace std;

#define cntLeadingZero(x) __builtin_clz(x)

typedef int64_t i64;
typedef uint64_t u64;
constexpr int MAXN = 100000 + 5;
constexpr int MAXLOG = 20;

int answer;
int ST[MAXN][MAXLOG];
int N, M, H[MAXN];
bool selected[MAXN];
int previous_Sel[MAXN];
int appCnt[MAXN];
int DP[MAXN];

void PrepareST()
{
    int L = 31 - cntLeadingZero(N);
    for(int i = 0; i < N; i++)
        ST[i][0] = H[i];
    for(int k = 1; k <= L; k++)
        for(int i = 0; i < 1 + N - (1 << (k - 1)); i++)
            ST[i][k] = max(ST[i][k-1], ST[i + (1 << (k - 1))][k-1]);
}

int Query(int L, int R)
{
    int k = 31 - cntLeadingZero(R - L + 1);
    return max(ST[L][k], ST[R - (1 << k) + 1][k]);
}

int lower_bound(int pos, int val)
{
    int L = pos + 1, R = N;
    while(L < R)
    {
        int mid = (L + R) >> 1;
        if(Query(pos + 1, mid) <= val)
            L = mid + 1;
        else
            R = mid;
    }
    return L;
}

void prepareAnswer()
{
    int cnt = 1;
    DP[N] = 0;
    for(int i = N - 1; i >= 0; i--)
    {
        int pos = lower_bound(i, H[i]);
        DP[i] = DP[pos] + 1;
    }

    selected[0] = true;
    previous_Sel[0] = -1;
    appCnt[0] = 1;

    int last = 0, lastH = H[0];
    for(int i = 1; i < N; i++)
    {
        selected[i] = false;
        previous_Sel[i] = last;
        if(H[i] > lastH)
        {
            selected[i] = true;
            last = i, lastH = H[i];
            cnt++;
        }
        appCnt[i] = cnt;
    }
    answer = cnt;
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int T;
    cin >> T ;
    while(T--)
    {
        cin >> N >> M ;
        for(int i = 0; i < N; i++)
            cin >> H[i];
        PrepareST(), prepareAnswer();

        while(M--)
        {
            int p, q;
            cin >> p >> q , p -= 1;
            if(selected[p])
            {
                if(p == 0)
                    cout << DP[lower_bound(p, q)] + 1 << endl ;
                else
                {
                    if (q <= H[previous_Sel[p]])
                        cout << appCnt[previous_Sel[p]] + DP[lower_bound(p, H[previous_Sel[p]])] << endl ;
                    else
                        cout << appCnt[p] + DP[lower_bound(p, q)] << endl ;
                }
            }
            else
            {
                if(q <= H[previous_Sel[p]])
                    cout << answer << endl ;
                else
                    cout << appCnt[previous_Sel[p]] + DP[lower_bound(p, q)] + 1 << endl ;
            }
        }
    }
    return 0;
}
