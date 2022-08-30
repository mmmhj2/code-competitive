#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
const int INF = 0x7f7f7f7f;
const int MAXN = 300 + 10;
int dist[MAXN][MAXN], N, M, T;

void Floyd_Alter()
{
    for(int k = 1; k <= N; k++)
        for(int i = 1; i <= N; i++)
            for(int j = 1; j <= N; j++)
                if(dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = min(dist[i][j], max(dist[i][k], dist[k][j]));
}

int main()
{

    int u, v, w;
    memset(dist, 0x7f, sizeof dist);
    
    scanf("%d%d%d", &N, &M, &T);

    for(int k = 0; k <= N; k++)
        dist[k][k] = 0;

    

    for(int i = 1; i <= M; i++)
    {
        scanf("%d%d%d", &u, &v, &w);
        dist[u][v] = w;
    }

    Floyd_Alter();

    for(int i = 1; i <= T; i++)
    {
        scanf("%d%d", &u, &v);
        if(dist[u][v] == INF)
            printf("%d\n", -1);
        else
            printf("%d\n", dist[u][v]);
    }

    return 0;
}
