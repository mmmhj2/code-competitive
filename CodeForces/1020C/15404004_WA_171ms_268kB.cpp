#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int MAXN = 3000 + 5;
const int64_t INF = 0x7FFFFFFFFFFFFFFF;

int N, M;
vector <int> price[MAXN];
int64_t ans = INF ;

int main()
{
    cin >> N >> M ;
    for(int i = 1; i <= N; i++)
    {
        int p, c;
        cin >> p >> c ;
        price[p].push_back(c);
    }
    for(int i = 1; i <= N; i++)
        sort(price[i].begin(), price[i].end());

    for(int v = 1; v <= N; v++)
    {
        int64_t cst(0);
        int req(v - price[1].size());
        vector <int> left;

        for(int p = 2; p <= M; p++)
        {
            int delta = max(int (price[p].size() - v + 1), 0);
            vector<int>::iterator maxitr = price[p].begin() + delta;

            for(vector<int>::iterator itr = price[p].begin(); itr < maxitr; itr++)
                cst += *itr, req--;
            for(vector<int>::iterator itr = maxitr; itr < price[p].end(); itr++)
                left.push_back(*itr);
        }

        if(req > 0)
        {
            vector<int>::iterator ed = left.begin() + req;
            nth_element(left.begin(), ed, left.end());

            for(vector<int>::iterator itr = left.begin(); itr < ed; itr++)
                cst += *itr;
        }

        ans = min(cst, ans);
    }

    cout << ans << endl ;
    return 0;
}

