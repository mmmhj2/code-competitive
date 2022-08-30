#include <algorithm>
#include <iterator>
#include <iostream>
//#include <iomanip>
//#include <cstring>
//#include <cstdlib>
#include <string>
#include <vector>
//#include <queue>
//#include <cmath>
//#include <set>
#include <map>
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

typedef long long i64;
int H, W, N;
i64 empt, ans[11];
map <pair<int, int>, int> mp;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int u, v;
    cin >> H >> W >> N ;
    empt = 1LL * (H - 2) * (W - 2);
    while(N--)
    {
        cin >> u >> v ;
        for(int i = -1; i <= 1; i++)
        {
            for(int j = -1; j <= 1; j++)
            {
                if(u + i < 1 || u + i > H)
                    continue;
                if(v + j < 1 || v + j > W)
                    continue;
                mp[make_pair(u+i, v+j)]++;
            }
        }
    }

    for(auto itr = mp.begin(); itr != mp.end(); itr++)
    {
        if(itr->first.first <= 1 || itr->first.first >= H)
            continue;
        if(itr->first.second <= 1 || itr->first.second >= W)
            continue;
        //cerr << itr->first.first << " " << itr->first.second << " " << itr->second << endl ;
        ans[itr->second]++;
        empt--;
    }

    cout << empt << endl ;
    for(int i = 1; i <= 9; i++)
        cout << ans[i] << endl ;

}

