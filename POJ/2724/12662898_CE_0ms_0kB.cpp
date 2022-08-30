#include <algorithm>
#include <iostream>
#include <utility>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
const int MAXN = 10;
const int MAXM = 2000;

vector <int> Adj[MAXM*2+10];
vector <int> opt;

bool vist[MAXM*2+10];
int  match[MAXM*2+10];
int len;

void init()
{
    for(int i = 0; i < len; i++)
        Adj[i].clear();
}

void addEdge(int u, int v)
{
    Adj[u].push_back(v);
    Adj[v].push_back(u);
}

int DFS(int cur)
{
    for(int i = 0; i < Adj[cur].size(); i++)
    {
        int & to = Adj[cur][i];
        if(vist[to])
            continue;
        vist[to] = true;
        if(match[to] < 0 || DFS(match[to]))
        {
            match[to] = cur;
            match[cur] = to;
            return true;
        }
    }
    return false;
}

int main()
{
    int N, M;
    string str;
    while(cin >> N >> M)
    {
        if(N == 0 && M == 0)
            break;
        opt.clear();
        for(int i = 0; i < M; i++)
        {
            cin >> str;
            int optres = 0;
            bool asterisk = false
            for(int i = 0; i < N; i++)
                if(str[i] == '1')
                    optres += 1 << (N-i-1) ;
                else if(str[i] == '*')
                    asterisk = true;

            opt.push_back(optres);
            if(asterisk)
            {
                for(int i = 0; i < N; i++)
                    if(str[i] == '*')
                    {
                        optres += 1 << (N-i-1);
                        break;
                    }
                        
                opt.push_back(optres);
            }
        }


        sort(opt.begin(), opt.end());
        opt.erase(unique(opt.begin(), opt.end()), opt.end());
//        opt.resize(len);
//        int sz = opt.size();
//        assert(sz == len);
        len = opt.size();
        init();
        for(int i = 0; i < len; i++)
        {
            int pi = opt[i], pj;
            for(int j = i+1; j < len; j++)
            {
                int cnt = 0;
                pj = opt[j];
                for(int k = 0; k < N; k++)
                {
                    int lobitpi = ((pi >> k) & 1);
                    int lobitpj = ((pj >> k) & 1);
                    if((lobitpi ^ lobitpj) == 1)
                        cnt++;
                }
                if(cnt == 1)
                    addEdge(i, j);
            }
        }

        int ans = 0;
        memset(match, -1, sizeof match);
        for(int i = 0; i < len; i++)
        {
            if(match[i] < 0)
            {
                memset(vist, 0x00, sizeof vist);
                if(DFS(i))
                    ans++;
            }
        }

        cout << len - ans << endl;
    }
}

