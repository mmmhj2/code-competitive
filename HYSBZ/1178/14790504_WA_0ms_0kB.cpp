#include <algorithm>
#include <iostream>
#include <iterator>
#include <cstring>
#include <cstdio>
#include <vector>
#include <set>
using namespace std;

#ifdef LOCAL
#define DEBUGMSG()                                                              \
{                                                                               \
    cerr << "[调试 @" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "]" ;        \
}
#define DEBUGVAR(x)                                                             \
{                                                                               \
    cerr << "[调试 @" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "]:" ;       \
    cerr << "([" << typeid(x).name() << "]" << #x << ")" << x << endl ;         \
}
#define DEBUGARR(l, r)                                                          \
{                                                                               \
    cerr << "[调试 @" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "]:" ;       \
    copy(l, r, ostream_iterator<decltype(*l)>(cerr, " "));                      \
    cerr << endl ;                                                              \
}
#else
#define DEBUGMSG()
#define DEBUGVAR(x)
#define DEBUGARR(l, r)
#endif // LOCAL

const int INF = 0x7F7F7F7F;
const int MAXN = 200000 + 20;
const int MAXLOG = 20;

struct Company
{
    int l, r, id;

    static bool cmpLex(const Company & lhs, const Company & rhs)
    {
        return lhs.id < rhs.id;
    }

    static bool cmpSeg(const Company & lhs, const Company & rhs)
    {
        if(lhs.l == rhs.l)
            return lhs.r > rhs.r;
        return lhs.l < rhs.l;
    }
};

struct Element
{
    int x, flag;
    Element(){};
    Element(int _x, int _f) :
        x(_x), flag(_f){};

    bool operator < (const Element & rhs) const
    {
        return x < rhs.x;
    }
};

int N, F[MAXN * 2][MAXLOG + 1];
vector <Company> A, tmpSel;
set <Element> ans;
vector <int> lst;

void CalcF()
{
    for(int i = lst.size()-1, cur = tmpSel.size()-1; i >= 0; i--)
    {
        F[i][0] = F[i+1][0];
        if(tmpSel[cur].l == i)
            F[i][0] = min(F[i][0], tmpSel[cur].r);

        for(int k = 1; k <= 17; k++)
            if(F[i][k-1] != INF)
                F[i][k] = F[F[i][k-1]+1][k-1];

        while(cur >= 0 && tmpSel[cur].l == i )
            cur--;
    }
}

int getAns(int l, int r)
{
    if(l < 0 || r < 0)
        return 0;
    int ans = 0;
    for(int i = 17; i >= 0; i--)
        if(F[l][i] <= r)
            l = F[l][i] + 1, ans += (1 << i);
    return ans ;
}

int main()
{
    A.reserve(MAXN);
    tmpSel.reserve(MAXN);
    int L, R;
    //cin >> N ;
    scanf("%d", &N);
    for(int i = 1; i <= N; i++)
    {
        //cin >> L >> R ;
        scanf("%d%d", &L, &R);
        A.push_back(Company{L, R, i-1});
        lst.push_back(L),
        lst.push_back(R);
    }

    lst.erase(unique(lst.begin(), lst.end()), lst.end());
    sort(lst.begin(), lst.end());

    for(vector<Company>::iterator itr = A.begin(); itr < A.end(); itr++)
        itr->l = lower_bound(lst.begin(), lst.end(), itr->l) - lst.begin() ,
        itr->r = lower_bound(lst.begin(), lst.end(), itr->r) - lst.begin() ;

    sort(A.begin(), A.end(), Company::cmpSeg);

    // Delete overlapping intervals
    int last = INF;
    for(int i = N-1; i >= 0; i--)
        if(A[i].r < last)
            tmpSel.push_back(A[i]),
            last = A[i].r;
    reverse(tmpSel.begin(), tmpSel.end());

    memset(F, 0x7F, sizeof F);
    CalcF();

    printf("%d\n", getAns(0, lst.size()-1));
    sort(A.begin(), A.end(), Company::cmpLex);

    // Add sentinel node
    ans.insert(Element(-1, -1));
    ans.insert(Element(lst.size(), 1));

    for(vector<Company>::iterator itr = A.begin(); itr < A.end(); itr++)
    {
        //DEBUGVAR(ans.size());
        //pair<int, int> l = make_pair(itr->l, 1), r = make_pair(itr->r, -1);
        Element l(itr->l, 1), r(itr->r, -1);
        set<Element>::iterator itrL = ans.lower_bound(l);
        set<Element>::iterator itrR = ans.upper_bound(r);

        if(itrL != itrR || (*itrR).flag < 0)
            continue;
        itrL --;
        int L = (*itrL).x+1, R = (*itrR).x-1;

        if(getAns(L, itr->l-1) + getAns(itr->r+1, R) + 1 == getAns(L, R))
        {
            ans.insert(l), ans.insert(r);
            //cout << itr->id+1 << " " ;
            printf("%d ", itr->id+1);
        }
    }

    return 0;
}
