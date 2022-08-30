#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef map<int, int> mp2i;
typedef mp2i::iterator mpitr2i;
typedef vector<int> vint;
typedef vint::iterator vitrint;
typedef long long i64;
const int MAXN = 100000;

int allocated;
mp2i * mapAddr[MAXN+5];

int N;
int veccol[MAXN+5];
pair<int, i64> maxCol[MAXN+5];

mp2i colors[MAXN+5];
vint Adj[MAXN+5];

void joint(int x, int coltps, int num)
{
    int & tmp =  (*mapAddr[x])[coltps];
    tmp += num;

    if(tmp > maxCol[x].first)
    {
        maxCol[x].first = tmp;
        maxCol[x].second = coltps;
    }
    else if(tmp == maxCol[x].first)
    {
        maxCol[x].second += coltps;
    }
}

void DFS(int cur, int fa)
{
    pair<int, int> maxColour;

    for(vitrint itr = Adj[cur].begin(); itr != Adj[cur].end(); itr++)
    {
        if(*itr == fa)
            continue;
        DFS(*itr, cur);
        int siz = mapAddr[*itr]->size();
        if(siz > maxColour.first)
            maxColour.first = siz, maxColour.second = *itr;
    }

    if(maxColour.second == 0)
        mapAddr[cur] = &colors[allocated++];
    else
    {
        // Joint the two vertices
        maxCol[cur] = maxCol[maxColour.second];
        mapAddr[cur] = mapAddr[maxColour.second];

        for(vitrint itr = Adj[cur].begin(); itr != Adj[cur].end(); itr++)
        {
            if(*itr == fa || *itr == maxColour.second)
                continue;
            for(mpitr2i itr2 = mapAddr[*itr]->begin(); itr2 != mapAddr[*itr]->end(); itr2++)
                joint(cur, itr2->first, itr2->second);
        }
    }
    joint(cur, veccol[cur], 1);
}

int main()
{
    int u, v;

    cin >> N ;
    for(int i = 1; i <= N; i++)
        cin >> veccol[i];
    for(int i = 1; i < N; i++)
        cin >> u >> v ,
        Adj[u].push_back(v) ,
        Adj[v].push_back(u) ;

    DFS(1, 0);

    for(int i = 1; i <= N; i++)
        cout << maxCol[i].second << " " ;

    return 0;
}
