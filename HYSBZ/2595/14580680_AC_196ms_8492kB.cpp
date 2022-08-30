#include <algorithm>
#include <iterator>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

#if __cplusplus >= 201103L
#define tuple _myTuple
#endif

struct tuple
{
    // X cord, Y cord and subset
    int first, second, third;
    tuple() {};
    tuple(int a, int b, int c)
    {
        first = a, second = b, third = c;
    }
};
tuple make_tuple(int x, int y, int z)
{
    return tuple(x, y, z);
}
const int INF = 0x7f7f7f7f;
const int MAXN = 10 + 5;
const int DIRX[4] = {0, 0, 1, -1};
const int DIRY[4] = {1, -1, 0, 0};
const int STATE_MAX = (1 << 11);
typedef pair<int, int> pii;

int N, M, K;
bool inQueue[MAXN][MAXN];
bool selected[MAXN][MAXN];
int val[MAXN][MAXN], dp[MAXN][MAXN][STATE_MAX];
tuple fa[MAXN][MAXN][STATE_MAX];
queue <pii> q;

void SPFA(int state)
{
    while (!q.empty())
    {
        pii cur = q.front();
        q.pop();
        inQueue[cur.first][cur.second] = false;

        for (int k = 0; k < 4; k++)
        {
            int nx = cur.first + DIRX[k],
                ny = cur.second + DIRY[k];

            if (nx < 0 || ny < 0 || nx >= N || ny >= M)
                continue;

            if (dp[nx][ny][state] > dp[cur.first][cur.second][state] + val[nx][ny])
            {
                dp[nx][ny][state] = dp[cur.first][cur.second][state] + val[nx][ny],
                fa[nx][ny][state] = make_tuple(cur.first, cur.second, state);

                if (!inQueue[nx][ny])
                    q.push(make_pair(nx, ny)),
                           inQueue[nx][ny] = true;
            }
        }
    }
}

void RunDP()
{
    for (int state = 1; state < (1 << K); state++)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                // shift to another state
                for(int sub = (state-1) & state; sub; sub = (sub-1) & state)
                {
                    // th cost is calculated repeatedly
                    if(dp[i][j][state] > dp[i][j][sub] + dp[i][j][state-sub] - val[i][j])
                    {
                        dp[i][j][state] = dp[i][j][sub] + dp[i][j][state-sub] - val[i][j];
                        fa[i][j][state] = tuple(i, j, sub);
                    }
                }

                if(dp[i][j][state] != INF)
                {
                    q.push(make_pair(i, j));
                    inQueue[i][j] = true;
                }
            }
        }
        // shift to the same state
        SPFA(state);
    }
}

void DFS(int x, int y, int state)
{
    if(fa[x][y][state].third == 0)
        return;
    if(x == INF)
        return;
    selected[x][y] = true;
    const tuple & tmp = fa[x][y][state];
    DFS(tmp.first, tmp.second, tmp.third);

    // shifted from previous state
    if(tmp.first == x && tmp.second == y)
        DFS(x, y, state - tmp.third);
}

int main()
{
    int stX, stY, stState;
    memset(dp, 0x7f, sizeof dp);
    cin >> N >> M ;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
        {
            cin >> val[i][j] ;
            if (!val[i][j])
            {
                dp[i][j][1 << (K++)] = 0;
                stX = i, stY = j;
            }
        }
    stState = (1 << K) - 1;

    RunDP();

    cout << dp[stX][stY][stState] << endl ;

    DFS(stX, stY, stState);

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            if(!val[i][j])
                cout << "x" ;
            else if(selected[i][j])
                cout << "o" ;
            else
                cout << "_" ;
        }
        cout << endl ;
    }
    return 0;
}