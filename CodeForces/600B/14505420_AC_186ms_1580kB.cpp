#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 200000 + 5;

int arrA[MAXN], arrB[MAXN];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m ;

    for(int i = 1; i <= n; i++)
        cin >> arrA[i];
    for(int i = 1; i <= m; i++)
        cin >> arrB[i];

    sort(&arrA[1], &arrA[n+1]);

    for(int i = 1; i <= m; i++)
    {
        cout << upper_bound(&arrA[1], &arrA[n+1], arrB[i]) - &arrA[1] << " " ;
    }
    return 0;
}
