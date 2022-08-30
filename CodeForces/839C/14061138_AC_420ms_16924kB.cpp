#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;
const int MAXN = 100000;

typedef vector<int>::iterator vitr;
vector <int> Adj[MAXN+5];
bool vist[MAXN+5];

double ans;

void DFS(int cur, int len, double prob)
{
    vector <int> & crv = Adj[cur];
    vector <int> tmp;
    vist[cur] = true;

    for(vitr itr = crv.begin(); itr != crv.end(); itr++)
        if(!vist[*itr])
            tmp.push_back(*itr);

    int totalCho = tmp.size();
    for(vitr itr = tmp.begin(); itr != tmp.end(); itr++)
        DFS(*itr, len+1, prob / totalCho);

    if(!totalCho)
        ans += prob * len ;
}

int main()
{
    int n;
    cin >> n ;
    for(int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v ;
        Adj[u].push_back(v);
        Adj[v].push_back(u);
    }
    DFS(1, 0, 1.0);
    cout << fixed << setprecision(15) << ans << endl ;
}
