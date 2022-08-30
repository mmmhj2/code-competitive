#include <algorithm>
#include <iostream>
#include <iterator>
#include <cstring>
#include <utility>
#include <vector>
using namespace std;
const int MAXN = 10000 + 5;
typedef pair<int, int> Product;

int N;
int DSU[MAXN];
vector <Product> vP;

int Find(int x)
{
    if(DSU[x] < 0)
        return x;
    DSU[x] = Find(DSU[x]);
    return DSU[x];
}

int main()
{
    while(cin >> N)
    {
        memset(DSU, 0xFF, sizeof DSU);
        int u, v, ans = 0;
        if(!N)
            break;
        vP.clear();

        for(int i = 1; i <= N; i++)
        {
            cin >> u >> v ;
            vP.push_back(make_pair(u, v));
        }

        sort(vP.begin(), vP.end(), greater<Product>());

        for(vector<Product>::iterator itr = vP.begin(); itr != vP.end(); itr++)
        {
            int date = Find(itr->second);
            if(date > 0)
            {
                ans += itr->first;
                DSU[date] = date-1;
            }
        }

        cout << ans << endl ;

    }
    return 0;
}
