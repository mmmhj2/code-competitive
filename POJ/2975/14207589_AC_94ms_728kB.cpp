#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

const int MAXN = 1000 + 5 ;
int n, cnt, ans;
vector <int> pile ;

void solveProc(const int & val)
{
    if((ans ^ val) < val)
        cnt++;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    while(cin >> n && n)
    {
        pile.clear();
        cnt = 0, ans = 0;
        int t;
        for(int i = 1; i <= n; i++)
            cin >> t , pile.push_back(t) , ans ^= t;

        for_each(pile.begin(), pile.end(), solveProc);
        cout << cnt << endl ;
    }
    return 0;
}
