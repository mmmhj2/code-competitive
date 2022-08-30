// Least/Lowest Common Ancestor Problem
// RMQ-SparseTable
// On-line Algorithm
#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <cmath>
#include <map>
using namespace std;
const int MAXN = 100000*2;
const int MAXBIT = 32+1;

typedef map<string, int> msi;
typedef msi::iterator msii;

int n, cnt;
msi mp;

int depth[MAXN+5], firstApp[MAXN+5], dfsSeq[MAXN+5];
int rmq[MAXBIT][MAXN+5];

vector <int> Adj[MAXN/2 + 5];
string reversemap[MAXN/2 + 5];
bool root[MAXN/2 + 5];

void DFS(int cur, int fa, int dep)
{
    dfsSeq[++cnt] = cur;
    firstApp[cur] = cnt;
    depth[cnt] = dep;

    for(int i = 0; i < Adj[cur].size(); i++)
    {
        int & to = Adj[cur][i];
        if(to == fa)    continue;

        DFS(to, cur, dep+1);

        dfsSeq[++cnt] = cur;
        depth[cnt] = dep;
    }
}

void initiate(int n)
{

    for(int i = 1; i <= n; i++)
        rmq[0][i] = i;

    for(int k = 1; k <= 32; k++)
    {
        int _base = 1 << k;
        if(_base > n)
            break;
        for(int i = 1; i+_base-1 <= n; i++)
        {
            int mid = i + (1 << (k-1));
            int & lf = rmq[k-1][i];
            int & rt = rmq[k-1][mid];
            if(depth[lf] < depth[rt])
                rmq[k][i] = lf;
            else
                rmq[k][i] = rt;
        }
    }
}
int Query(int l, int r)
{
    l = firstApp[l], r = firstApp[r];
    if(l > r)
        swap(l, r);
    int len = r - l + 1;
    int _2log = (int)(log(len) / log(2.0));
    int & lf = rmq[_2log][l];
    int & rt = rmq[_2log][r-(1<<_2log)+1];
    if(depth[lf] < depth[rt])
        return lf;
    return rt;
}

int main()
{
    int N, M;
    string fa, ch;
    cin >> N;
    n = N;
    for(int i = 1; i <= N; i++)
    {
        cin >> fa >> ch;

        int & mfa = mp[fa];
        int & mch = mp[ch];
        if(mfa == 0)
        {
            mfa = ++cnt;
            reversemap[cnt] = fa;
        }

        if(mch == 0)
        {
            mch = ++cnt;
            reversemap[cnt] = ch;
        }

        Adj[mfa].push_back(mch);
        //Adj[mch].push_back(mfa);
        root[mch] = true;
    }
/*
    msii itr = mp.begin();
    while(itr != mp.end())
    {
        cout << itr->first << " "<< itr->second << endl ;
        itr++;
    }
    for(int i = 1; i <= cnt; i++)
        cout << reversemap[i] << endl ;
*/
    cnt = 0;
    for(int i = 1; i <= n; i++)
    {
        if(!root[i])
            DFS(i, 0, 0);
    }
    initiate(cnt);
/*
    for(int i = 1; i <= cnt; i++)
        cout << dfsSeq[i] << " " << depth[i] << endl ;
    for(int i = 1; i <= mp.size()+1; i++)
        cout << firstApp[i] << " " ;
*/

    cin >> M;
    int ans = 0;
    for(int i = 1; i <= M; i++)
    {
        cin >> fa >> ch;
        int ma = mp[fa];
        int mb = mp[ch];
        ans = Query(ma, mb);
        cout << reversemap[dfsSeq[ans]] << endl;
    }
    return 0;
}
