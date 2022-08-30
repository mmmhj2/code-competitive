#include <algorithm>
#include <iostream>
//#include <cassert>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

const int MAXN = 200000 + 5;
typedef long long i64;
struct GADGET
{
    int typ, cst;
};
vector <GADGET> gad;
vector <pair<i64,int> > tmpcst;
int N, M, K, S;
int A[MAXN], B[MAXN];
int min1[MAXN], min2[MAXN];
int mindate1[MAXN], mindate2[MAXN];

bool check(int dayid)
{
    if(dayid > N)
        return true;
    i64 sum = 0;

    tmpcst.clear();
    for(vector<GADGET>::iterator itr = gad.begin(); itr != gad.end(); itr++)
        if(itr->typ == 1)
            tmpcst.push_back(make_pair(1LL * min1[dayid] * itr->cst, itr - gad.begin()));
        else if(itr->typ == 2)
            tmpcst.push_back(make_pair(1LL * min2[dayid] * itr->cst, itr - gad.begin()));
    sort(tmpcst.begin(), tmpcst.end());

    for(int i = 0; i < K; i++)
        sum += tmpcst[i].first;

    if(sum <= S)
        return true;
    return false;
}

int BinarySearch()
{
    int L = 0, R = MAXN;
    while(L + 1 < R)
    {
        int mid = (L+R) >> 1 ;
        if(check(mid))
            R = mid;
        else
            L = mid;
    }
    return R;
}

int main()
{
    int typ, cst;
    memset(min1, 0x7f, sizeof min1);
    memset(min2, 0x7f, sizeof min2);
    scanf("%d%d%d%d", &N, &M, &K, &S);
    for(int i = 1; i <= N; i++)
    {
        scanf("%d", &A[i]);
        if(A[i] < min1[i-1])
            min1[i] = A[i],
            mindate1[i] = i;
        else
            min1[i] = min1[i-1],
            mindate1[i] = mindate1[i-1];
    }

    for(int i = 1; i <= N; i++)
    {
        scanf("%d", &B[i]);
        if(B[i] < min2[i-1])
            min2[i] = B[i],
            mindate2[i] = i;
        else
            min2[i] = min2[i-1],
            mindate2[i] = mindate2[i-1];
    }

    for(int i = 1; i <= M; i++)
    {
        scanf("%d%d", &typ, &cst);
        gad.push_back(GADGET{typ, cst});
    }
    int ans = BinarySearch();
    if(ans > N)
    {
        puts("-1");
        return 0;
    }
    printf("%d\n", ans);
    check(ans);
    for(int i = 0; i < K; i++)
    {
        printf("%d ", tmpcst[i].second+1);
        if(gad[tmpcst[i].second].typ == 1)
            printf("%d", mindate1[ans]);
        else
            printf("%d", mindate2[ans]);
        puts("");
    }
}
