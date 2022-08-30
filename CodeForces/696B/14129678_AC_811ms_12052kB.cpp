#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

const int MAXN = 100000;
typedef vector<int>::iterator vitr;
vector <int> Adj[MAXN + 5];
int chCnt[MAXN + 5];
double ans[MAXN + 5];


void getCh(int cur)
{
    chCnt[cur] = Adj[cur].size();
    //for_each(Adj[cur].begin(), Adj[cur].end(), bind1st(getChProc(), cur));
    for(vitr itr = Adj[cur].begin(); itr != Adj[cur].end(); itr++)
    {
        getCh(*itr);
        chCnt[cur] += chCnt[*itr];
    }
}

void getAns(int cur)
{
    //for_each(Adj[cur].begin(), Adj[cur].end(), bind1st(getAnsProc(), cur));
    for(vitr itr = Adj[cur].begin(); itr != Adj[cur].end(); itr++)
    {
        ans[*itr] = ans[cur] + 1 + (chCnt[cur] - chCnt[*itr] - 1) / 2.0;
        getAns(*itr);
    }
}

int main()
{
    int n, u;
    cin >> n ;

    for(int i = 2; i <= n; i++)
        cin >> u , Adj[u].push_back(i);

    getCh(1);
    ans[1] = 1;
    getAns(1);
    for(int i = 1; i <= n; i++)
        cout << (i == 1 ? "" : " ") << fixed << setprecision(6) << ans[i] ;
    cout << endl ;
}
