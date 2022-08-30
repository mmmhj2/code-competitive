#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 100000;

int n, mcnt;
int a[MAXN+5];

int BinarySearch();
int check(int median);

int main()
{
    //ios::sync_with_stdio(0);    cin.tie(0);
    while(scanf("%d", &n) != EOF)
    {
        int cn2 = (n-1)*n / 2;
        mcnt = cn2 / 2;
        //cin >> n ;
        memset(a, 0x00, sizeof a);

        for(int i = 1; i <= n; i++)
            scanf("%d", &a[i]);

        sort(a+1, a+n+1);

        //cout << BinarySearch() << endl ;
        printf("%d\n", BinarySearch());
    }
}

int BinarySearch()
{
    int lb = 0, rb = a[n] - a[1] + 10;
    while(lb+1 < rb)
    {
        int mid = (lb+rb) >> 1;

        if(check(mid))
            lb = mid;
        else
            rb = mid;
    }

    return lb;
}

int check(int median)
{
    int sum = 0;
    for(int i = 1; i <= n; i++)
    {
        sum += n - (lower_bound(&a[1], &a[n+1], a[i]+median)-&a[1]);
    }
    return sum > (mcnt);
}


