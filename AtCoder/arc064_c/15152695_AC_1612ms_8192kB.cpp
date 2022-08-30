#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

const int MAXN = 1000 + 10;

#define y1 MyY1
#define y2 MyY2
struct barrier
{
    int x, y, r;
};

int N;
int x1, x2, y1, y2;
vector <barrier> vbar;
double dist[MAXN];
bool inQueue[MAXN];

double precalcDist[MAXN][MAXN];
double getDist(int from, int to)
{
    double deltaX = vbar[from].x - vbar[to].x;
    double deltaY = vbar[from].y - vbar[to].y;
    return max(sqrt(deltaX * deltaX + deltaY * deltaY) - vbar[from].r - vbar[to].r, 0.0);
}

void SPFA()
{
    fill(dist, dist + N + 2, 1e100);
    memset(inQueue, 0x00, sizeof inQueue);

    queue <int> q;
    q.push(0);
    dist[0] = 0, inQueue[0] = true;

    while(!q.empty())
    {
        int to = q.front();
        inQueue[to] = false;
        q.pop();

        for(int i = 0; i <= N + 1; i++)
        {
            if(i == to)
                continue;

            if(dist[i] > dist[to] + precalcDist[i][to])
            {
                dist[i] = dist[to] + precalcDist[i][to];
                if(!inQueue[i])
                {
                    inQueue[i] = true;
                    q.push(i);
                }
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int u, v, w;

    cin >> x1 >> y1 >> x2 >> y2 ;
    vbar.push_back(barrier{x1, y1, 0});
    vbar.push_back(barrier{x2, y2, 0});

    cin >> N ;
    for(int i = 1; i <= N; i++)
        cin >> u >> v >> w, vbar.push_back(barrier{u, v, w});

    for(int i = 0; i <= N + 1; i++)
        for(int j = 0; j < i; j++)
            precalcDist[i][j] = precalcDist[j][i] = getDist(i, j);

    SPFA();

    cout << fixed << setprecision(10) << dist[1] << endl ;

    return 0;
}
