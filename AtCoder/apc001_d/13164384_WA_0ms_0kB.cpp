#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
using namespace std;
const int MAXN = 100000;

int n, m;
int fa[MAXN+5];
int val[MAXN+5];
vector <int> blk[MAXN+5];
vector <int> ansEdge;
int ans;

int SetFind(int x)
{
    if(fa[x] != x)
        return fa[x] = SetFind(fa[x]);
    return fa[x];
}

void SetInit(int n)
{
    for(int i = 1; i <= n; i++)
        fa[i] = i;
}

int main()
{
    int blkcnt;

    cin >> n >> m ;
    SetInit(n);
    blkcnt = n;

    for(int i = 1; i <= n; i++)
    {
        cin >> val[i] ;
        //blk[i].push_back(val[i]);
    }


    for(int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        u++, v++;
        if(SetFind(u) != SetFind(v))
            fa[SetFind(u)] = SetFind(v), blkcnt--;
    }

    for(int i = 1; i <= n; i++)
        blk[SetFind(i)].push_back(val[i]);
/*
    for(int i = 1; i <= n; i++)
    {
        if(!blk[i].empty())
            cout << blk[i].size() << endl ;
    }
*/
    if(blkcnt <= 1)
    {
        cout << 0 << endl ;
        return 0;
    }

    blkcnt -= 2;

    for(int i = 1; i <= n; i++)
    {
        if(!blk[i].empty())
        {
            sort(blk[i].begin(), blk[i].end());
            ans += blk[i][0];
            for(int k = 1; k < blk[i].size(); k++)
                ansEdge.push_back(blk[i][k]);
        }
    }

    sort(ansEdge.begin(), ansEdge.end());

    if(ansEdge.size() < blkcnt)
    {
        cout << "Impossible" << endl;
        return 0;
    }


    for(int i = 0; i < blkcnt; i++)
        ans += ansEdge[i] ;

    cout << ans << endl ;
    return 0;


}
