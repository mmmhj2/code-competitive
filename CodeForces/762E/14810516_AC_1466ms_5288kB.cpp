#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <set>
using namespace std;
using namespace __gnu_pbds;

typedef long long i64;
const int MAXN = 100000 + 10;
const int MAXF = 10000 + 5;
const int MAXF_STRICT = 1e4;
const int MAXN_STRICT = 1e5;

struct station
{
    int x, r, f;

    station() = default;
    station(int _x, int _r, int _f) :
        x(_x), r(_r), f(_f)
    {

    }

    static bool cmpR(const station & lhs, const station & rhs)
    {
        return lhs.r < rhs.r ;
    }
};
vector <station> data;
tree
    <int,
    null_type,
    less<int>,
    splay_tree_tag,
    tree_order_statistics_node_update>
    st[MAXF];
i64 ans;
int N, K;

int main()
{
    int x, r, f;
    cin >> N >> K ;

    for(int i = 1; i <= N; i++)
    {
        cin >> x >> r >> f ;
        data.push_back(station(x, r, f));
        st[f].insert(x);
    }

    sort(data.begin(), data.end(), station::cmpR);

    for(station & i : data)
    {
        int l(max(1, i.f - K)), r(min(MAXF_STRICT, i.f + K));
        for(int j = l; j <= r; j++)
              //ans += (st[j].lower_bound(i.x + i.r + 1) - st[j].begin()) + (st[j].lower_bound(i.x - i.r) - st[j].begin());
              ans += st[j].order_of_key(i.x + i.r + 1) - st[j].order_of_key(i.x - i.r) ;
        st[i.f].erase(i.x);
    }

    cout << ans-N << endl ;

    return 0;
}
