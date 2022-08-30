#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

struct node
{
    int v[3], dist;
    bool operator < (const node & rhs) const
    {
        return dist > rhs.dist;
    }
};

const int MAXN = 200 + 5;
int vis[MAXN][MAXN], cap[3], ans[MAXN];

void updateAns(const node & u)
{
    for(int i = 0; i < 3; i++)
    {
        int d = u.v[i];
        if(ans[d] < 0 || ans[d] > u.dist) ans[d] = u.dist;
    }
    return;
}

int BFS(int a, int b, int c, int d);

int main()
{
    int T, a, b, c, d;

    cin >> T;

    while(T--)
    {
        cin >> a >> b >> c >> d;
        BFS(a, b, c, d);
    }
    return 0;
}

int BFS(int a, int b, int c, int d)
{
    cap[0] = a, cap[1] = b, cap[2] = c;
    memset(vis, 0x00, sizeof vis);
    memset(ans, 0xff, sizeof ans);
    priority_queue <node> q;

    node start;
    start.dist = 0;
    start.v[0] = 0;
    start.v[1] = 0;
    start.v[2] = c;

    q.push(start);

    vis[0][0] = 1;

    while(!q.empty())
    {
        node u = q.top(); q.pop();
        updateAns(u);

        if(ans[d] >= 0)  break;

        for(int i = 0; i < 3; i ++){
            for(int j = 0; j < 3; j ++)
            {
                if(u.v[i] == 0 || u.v[j] == cap[j]) continue;
                int amount = min(cap[j], u.v[i]+u.v[j]) - u.v[j];
                node u2 = u;

                u2.dist = u.dist + amount;
                u2.v[i] -= amount, u2.v[j] += amount;

                if(!vis[u2.v[0]][u2.v[1]])
                {
                    vis[u2.v[0]][u2.v[1]] = 1;
                    q.push(u2);
                }
            }
        }
    }

    while(d >= 0)
    {
        if(ans[d] >= 0){
            cout << ans[d] << " " << d << endl;
            return ans[d];
        }
        d--;
    }

    return -1;
}

