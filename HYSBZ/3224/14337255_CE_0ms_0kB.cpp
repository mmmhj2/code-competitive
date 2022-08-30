#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <iostream>
#include <utility>
#include <map>

using namespace std;
using namespace __gnu_pbds;

typedef pair<int, int> p2i;
typedef map<int, int> m2i;
typedef tree<p2i, null_type, less<p2i>, splay_tree_tag, tree_order_statistics_node_update> splayTree;

m2i rnks;

int main()
{
    splayTree spl;
    int n, opt, x;
    cin >> n;

    while(n--)
    {
        cin >> opt ;

        switch(opt)
        {
        case 1:
            cin >> x ;
            spl.insert(p2i(x, rnks[x]));
            rnks[x]++;
            break;
        case 2:
            cin >> x ;
            rnks[x]--;
            spl.erase(p2i(x, rnks[x]));
            break;
        case 3:
            cin >> x ;
            cout << ((int)spl.order_of_key(p2i(x, 0)) + 1) << endl ;
            break;
        case 4:
            cin >> x ;
            cout << (spl.find_by_order(x-1) -> first) << endl ;
            break;
        case 5:
            cin >> x ;
            cout << (spl.find_by_order(spl.order_of_key(p2i(x, 0))-1)->first) << endl ;
            break;
        case 6:
            cin >> x ;
            cout << (spl.upper_bound(p2i(x, 0))->first) << endl ;
            break;
        }
    }

}
