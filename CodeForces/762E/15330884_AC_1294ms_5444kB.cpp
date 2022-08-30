#include <iostream>
#include <vector>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef tree <int, null_type, less<int>, splay_tree_tag, tree_order_statistics_node_update> splayTree;
const int MAXF = 1e4;
const int MAXN = 1e5;
const int MAXX = 1e9;

splayTree feq[MAXF + 5];

struct station
{
    int x, r, f;

    station(){};
    station(int _x, int _r, int _f)
    {
        x = _x, r = _r, f = _f;
    }

    bool operator < (const station & rhs) const
    {
        return r < rhs.r;
    }
};
vector <station> stavec;
int64_t ans;

int N, K;
int main()
{
    cin >> N >> K ;

    for(int i = 1; i <= N; i++)
    {
        int x, r, f;
        cin >> x >> r >> f;
        stavec.push_back(station(x, r, f));
        feq[f].insert(x);
    }
    sort(stavec.begin(), stavec.end());

    for(auto & x : stavec)
    {
        int l = max(1, x.f - K), r = min(MAXF, x.f + K);

        for(int i = l; i <= r; i++)
            ans += feq[i].order_of_key(x.x + x.r + 1) - feq[i].order_of_key(x.x - x.r);
        feq[x.f].erase(x.x);
    }

    cout << ans - N << endl ;
    return 0;
}
