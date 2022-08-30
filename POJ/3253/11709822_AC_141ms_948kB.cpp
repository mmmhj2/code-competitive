#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

typedef long long i64;
i64 ans = 0;

int main()
{
    priority_queue <int, vector<int>, greater<int> > pq;
    int n;
    cin >> n;

    for(int i = 0; i < n ; i++)
    {
        int t;
        cin >> t;
        pq.push(t);
    }

    while(pq.size() >= 2)
    {
        int t1(pq.top());pq.pop();
        int t2(pq.top());pq.pop();

        //cout << "Merging :" << t1 << " " << t2 <<endl;
        ans += t1+t2;
        //cout << "Answer :" << ans << endl;

        pq.push(t1+t2);
    }

    cout << ans << endl;
}
