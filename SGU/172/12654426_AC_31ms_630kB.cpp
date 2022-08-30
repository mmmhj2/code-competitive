#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
const int MAXN = 300;
const int MAXM = 30500;

int N, M;
int Adj[MAXN+5][MAXN+5];
int bicolor[MAXN+5];

queue <int> q;

int main()
{

    cin >> N >> M;
    for(int i = 1; i <= M; i++)
    {
        int u, v;
        cin >> u >> v ;
        Adj[u][v] = 1;
        Adj[v][u] = 1;
    }

    for(int i = 1; i <= N; i++)
        bicolor[i] = -1;
    for(int i = 1; i <= N; i++)
    {
        if(bicolor[i] != -1)
            continue;
        q.push(i);
        bicolor[i] = 1;

        while(!q.empty())
        {
            int cur = q.front();
            q.pop();

            for(int i = 1; i <= N; i++)
            {
                if(Adj[cur][i] && (i != cur))
                {
                    if(bicolor[i] == bicolor[cur])
                    {
                        cout << "no" << endl;
                        return 0;
                    }
                    if(bicolor[i] == -1)
                    {
                        bicolor[i] = (bicolor[cur] == 1 ? 0 : 1);
                        q.push(i);
                    }
                }
            }

        }
    }
    cout << "yes" << endl;

    vector <int> ans;
    for(int i = 1; i <= N; i++)
        if(bicolor[i] == 1)
            ans.push_back(i);
    cout << ans.size() << endl;

    for(int i = 0 ; i < ans.size(); i++)
    {
        if(i != 0)
            cout << " " ;
        cout << ans[i] ;
    }
    cout << endl ;
}
