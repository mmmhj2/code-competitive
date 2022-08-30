#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;

const int MAXN = 1000000 + 5;

int N, M;
int inBlk[MAXN];
bool vist[MAXN];

vector <int> Adj[MAXN];
set <int> ans;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int u, v;
    cin >> N >> M ;

    for(int i = 1; i <= M; i++)
        cin >> u >> v , Adj[u].push_back(v);

    for(int i = 1; i <= N; i++)
        if(!inBlk[i])
        {
            inBlk[i] = i;
            for(int x : Adj[i])
                if(inBlk[x] == 0)
                    inBlk[x] = i;
            //vist[i] = true;
        }

    for(int i = N; i >= 1; i--)
        if(inBlk[i] == i)
            for(int x : Adj[i])
                inBlk[x] = i;

    for(int i = 1; i <= N; i++)
        if(inBlk[i] == i)
            ans.insert(i);

    cout << ans.size() << endl ;

    for(auto itr = ans.begin(); itr != ans.end(); itr++)
        cout << *itr << " ";
    cout << endl ;

    return 0;

    return 0;
}

