#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
typedef long long i64;

int N, M;


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    while(cin >> N >> M)
    {
        int ans = 0x7F7F7F7F;
        for(int i = 1; i <= M; i++)
        {
            int u, d, x;
            cin >> u >> d ;
            x = (N * d + 1) / (u + d) + ((N * d + 1) % (u + d) != 0);
			ans = min(ans, u * x - (N - x) * d);
        }

        cout << ans << endl ;
    }
    return 0;
}
