#include <algorithm>
#include <iterator>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <set>
using namespace std;

#ifdef LOCAL
#define DEBUGVAR(x)                                                             \
{                                                                               \
    cerr << "[调试 @" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "]:" ;      \
    cerr << x << endl ;                                                         \
}
#define DEBUGARR(l, r)                                                          \
{                                                                               \
    cerr << "[调试 @" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "]:" ;      \
    copy(l, r, ostream_iterator<decltype(*l)>(cerr, " "));                      \
    cerr << endl ;                                                              \
}
#else
#define DEBUGVAR(x)
#define DEBUGARR(l, r)
#endif // LOCAL

const int MAXN = 10000 + 5;
const int MAXM = 30000 + 5;

struct disjointSet{
    int fa[MAXN+20];

    void clear(int N)
    {
        for(int i = 0; i <= N; i++)
            fa[i] = i;
    }

    disjointSet()
    {
    }

    disjointSet(int N)
    {
        clear(N);
    }

    int find(int x)
    {
        if(fa[x] == x)
            return x;
        return fa[x] = find(fa[x]);
    }

    void unite(int x, int y)
    {
        fa[find(x)] = find(y);
    }
};

disjointSet dS(MAXN);
int N, M, K;
vector<int> Lang[MAXM];

int main()
{
    int t;
    cin >> N >> M ;
    for(int i = 1; i <= N; i++)
    {
        cin >> K ;
        for(int j = 1; j <= K; j++)
            cin >> t,
            Lang[t].push_back(i);
    }

    for(int i = 1; i <= M; i++)
    {
        int c1 = dS.find(*Lang[i].begin());
        if(Lang[i].size() <= 1)
            continue;
        for(vector<int>::iterator itr = Lang[i].begin()+1; itr != Lang[i].end(); itr++)
            if(dS.find(*itr) != dS.find(c1))
                dS.unite(*itr, c1);
    }

    DEBUGARR(&dS.fa[1], &dS.fa[N+1]);
    int cnt = -1;
    for(int i = 1; i <= N; i++)
        if(dS.fa[i] == i)
            cnt++;
    cout << cnt << endl ;
}
