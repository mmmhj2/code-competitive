#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#define MAINLOOPBEGIN(x) while(x--){
#define MAINLOOPEND }
using namespace std;
const int MAXH = 40;
const int MAXW = 10;
const int MAXN = 400;
const int DIR[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int match[MAXN+10];
bool vist[MAXN+10];
vector <int> Adj[MAXN+10];
int H, W;

char MAP[MAXH+5][MAXW+5];
int PlaceNum[MAXH+5][MAXW+5];

int DFS(int cur)
{
    for(int i = 0;i < Adj[cur].size(); i++)
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

int LinkGraph(int x, int y)
{
    if(MAP[x][y] != '*')
        return -1;
    for(int i = 0; i < 4; i++)
    {
        int nx = x + DIR[i][0];
        int ny = y + DIR[i][1];

        if(nx < 0 || ny < 0)
            continue;
        if(nx >= H || ny >= W)
            continue;
        if(MAP[nx][ny] != '*')
            continue;
        Adj[PlaceNum[x][y]].push_back(PlaceNum[nx][ny]);
    }
    return 0;
}

int main()
{
    int kase;
    cin >> kase;
MAINLOOPBEGIN(kase)
    cin >> H >> W;
    int placecnt = 0;
    memset(MAP, 0x00, sizeof MAP);
    memset(PlaceNum, 0x00, sizeof PlaceNum);
    memset(match, 0xff, sizeof match);

    for(int i = 0; i < H; i++)
    {
        cin >> MAP[i];
        for(int j = 0; j < W; j++)
            if(MAP[i][j] == '*')
            {
                Adj[placecnt].clear();
                PlaceNum[i][j] = (placecnt++);
            }

    }

    for(int i = 0; i < H; i++)
        for(int j = 0; j < W; j++)
            LinkGraph(i, j);
/*
    for(int i = 0; i < placecnt; i++)
    {
        cerr << "Adjacent " << i << endl ;
        for(vector<int>::iterator itr = Adj[i].begin(); itr != Adj[i].end(); itr++)
            cerr << *itr << " ";
        cerr << endl;
    }
*/

    int ans = 0;
    for(int i = 0; i < placecnt; i++)
    {
        if(match[i] < 0)
        {
            memset(vist, 0x00, sizeof vist);
            if(DFS(i))
                ans++;
        }
    }
    cout << placecnt-ans << endl;

MAINLOOPEND
}

