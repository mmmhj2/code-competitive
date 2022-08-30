#include <algorithm>
#include <iostream>
//#include <cassert>
#include <cstring>
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
i64 A[MAXN], B[MAXN];
i64 min1[MAXN], min2[MAXN];
int mindate1[MAXN], mindate2[MAXN];

bool check(int dayid)
{
    if(dayid > N)
        return true;

    i64 sum = 0;

    //cerr << "checking date : " << dayid << " " << min1[dayid] << " " << min2[dayid] << endl ;

    tmpcst.clear();
    for(vector<GADGET>::iterator itr = gad.begin(); itr != gad.end(); itr++)
    {
        if(itr->typ == 1)
        {
            //cerr << min1[dayid] * itr->cst << endl;
            tmpcst.push_back(make_pair(min1[dayid] * itr->cst, itr - gad.begin()));
        }

        if(itr->typ == 2)
        {
            //cerr << min2[dayid] * itr->cst << endl;
            tmpcst.push_back(make_pair(min2[dayid] * itr->cst, itr - gad.begin()));
        }

    }
    sort(tmpcst.begin(), tmpcst.end());
    //cerr << "Price : " << tmpcst[0].first << " " << tmpcst[1].first << " " << tmpcst[2].first << endl ;

    for(int i = 0; i < K; i++)
        sum += tmpcst[i].first;
    //cerr << sum << endl ;

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

        //cerr << L << " " << R << " " << mid << endl ;

        if(check(mid))
        {
            //cerr << "Moving R" << endl ;
            R = mid;
        }
        else
        {
            //cerr << "Moving L" << endl ;
            L = mid;
        }

    }
    return R;
}

int main()
{
    int typ, cst;
    memset(min1, 0x7f, sizeof min1);
    memset(min2, 0x7f, sizeof min2);
    cin >> N >> M >> K >> S ;
    for(int i = 1; i <= N; i++)
    {
        cin >> A[i] ;
        //min1[i] = min(A[i], min1[i-1]);
        if(A[i] < min1[i-1])
        {
            min1[i] = A[i] ;
            mindate1[i] = i;
        }
        else
        {
            min1[i] = min1[i-1];
            mindate1[i] = mindate1[i-1];
        }
    }

    for(int i = 1; i <= N; i++)
    {
        cin >> B[i] ;
        //min2[i] = min(B[i], min2[i-1]);
        if(B[i] < min2[i-1])
        {
            min2[i] = B[i] ;
            mindate2[i] = i;
        }
        else
        {
            min2[i] = min2[i-1];
            mindate2[i] = mindate2[i-1];
        }
    }

    for(int i = 1; i <= M; i++)
    {
        cin >> typ >> cst;
        gad.push_back(GADGET{typ, cst});
    }
    int ans = BinarySearch();
    if(ans > M)
    {
        cout << -1 << endl ;
        return 0;
    }
    cout << ans << endl ;
    check(ans);
    for(int i = 0; i < K; i++)
    {
        cout << tmpcst[i].second+1 << " " ;
        if(gad[tmpcst[i].second].typ == 1)
            cout << mindate1[ans] << endl ;
        else
            cout << mindate2[ans] << endl ;
    }

}
