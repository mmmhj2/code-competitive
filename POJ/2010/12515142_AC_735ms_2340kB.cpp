#include <algorithm>
#include <iostream>
#include <utility>
#include <queue>
using namespace std;

typedef pair<int, int> p2i;
const int MAXC = 100000;
const int INF  = 0x3fffffff;

p2i cow[MAXC+10];
int n, c, f;
int sumlo[MAXC+10], sumhi[MAXC+10];

int main()
{
    ios::sync_with_stdio(0);

    cin >> n >> c >> f;
    unsigned int median = n/2;
    for(int i = 1; i <= c; i++)
        cin >> cow[i].first >> cow[i].second;

    sort(cow+1, cow+c+1);

    priority_queue <int> q;

    int total = 0;
    for(int i = 1; i <= c; i++)
    {
        if(q.size() == median)
            sumlo[i] = total;
        else
            sumlo[i] = INF;

        q.push(cow[i].second);
        total += cow[i].second;

        while(q.size() > median)
            total -= q.top(), q.pop();
    }

    while(!q.empty())
        q.pop();
    total = 0;

    for(int i = c; i >= 1; i--)
    {
        if(q.size() == median)
            sumhi[i] = total;
        else
            sumhi[i] = INF;

        q.push(cow[i].second);
        total += cow[i].second;

        while(q.size() > median)
            total -= q.top(), q.pop();
    }

    int ans = -1;
    for(int i = 1; i <= c; i++)
        if(sumlo[i] + sumhi[i] + cow[i].second <= f)
            ans = max(ans, cow[i].first);
    cout << ans << endl ;
}
