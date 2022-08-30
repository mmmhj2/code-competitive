#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
const int INF = 0x7f7f7f7f;
const int MAXN = 10000 + 10;
const int MAXW = 10000000;
const int EPS = 0.000000001;

struct Edge
{
    int to;
    double w;
};
typedef vector<Edge> vEdge;

int N, M;
vEdge Adj[MAXN];
bool vist[MAXN];
int u[MAXN];
int v[MAXN];
double w[MAXN];
double dist[MAXN];

bool negativeCircle;

void AddEdge(int u, int v, double w)
{
    Adj[u].push_back(Edge{v, w});
}

void CheckNegativeCircleRecursive(int cur,const double & delta)
{
    vist[cur] = true;

    for(vEdge::iterator itr = Adj[cur].begin(); itr != Adj[cur].end(); itr++)
    {
        int & to = itr->to;

        // Only enter when the weight is negative
        if(dist[to] > dist[cur] + (itr->w - delta))
        {
            if(vist[to])
            {
                //cerr << "Spotted negative circle" << endl ;
                negativeCircle = true;
                return ;
            }
            dist[to] = dist[cur] + (itr->w - delta);
            CheckNegativeCircleRecursive(to, delta);
        }
        if(negativeCircle)
            return;
    }
    vist[cur] = 0;
}

bool CheckBinary(double delta)
{
    memset(vist, 0x00, sizeof vist);
    // Set default distance to zero
    memset(dist, 0x00, sizeof dist);

    negativeCircle = false;

    //for(int i = 1; i <= N; i++)
    //    Adj[i].clear();
    //for(int i = 1; i <= M; i++)
    //    AddEdge(u[i], v[i], w[i]-delta);

    for(int i = 1; i <= N; i++)
    {
        //if(!vist[i])
        CheckNegativeCircleRecursive(i, delta);
        if(negativeCircle)
            break;
    }
    return negativeCircle;
}

double BinarySearch()
{
    double l = -MAXW, r = MAXW;
    int cnt = 0;
    while(cnt <= 100)
    {
        cnt++;
        double mid = (l+r)/2.0;
        //cerr << fixed << setprecision(8) << mid << endl ;
        if(CheckBinary(mid))
            r = mid;
        else
            l = mid;
    }
    return r;
}

int main()
{
    int u, v;
    double w;
    cin >> N >> M ;

    for(int i = 1; i <= M; i++)
    {
        cin >> u >> v >> w;
        AddEdge(u, v, w);
    }

    cout << fixed << setprecision(8) << BinarySearch() << endl ;
}
