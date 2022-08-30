#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 100000;

int n, m;
int budget[MAXN+5];

int BinarySearch();
bool check(int expense);

int main()
{
    ios::sync_with_stdio(0);

    cin >> n >> m;

    for(int i = 1; i <= n; i++)
        cin >> budget[i];

    cout << BinarySearch() << endl ;
}

int BinarySearch()
{
    int lb = 0, rb = 0x7fffffff;

    while(lb+1 < rb)
    {
        int mid = (lb+rb) >> 1;

        if(check(mid))
            rb = mid;
        else
            lb = mid;
    }
    return  rb;

}

bool check(int exp)
{
    int monthsum = 1;
    int tmpsum = 0;

    for(int i = 1; i <= n; i++)
    {
        if(budget[i] > exp)
            return false;
        if(tmpsum + budget[i] > exp)
            monthsum++, tmpsum = budget[i];
        else
            tmpsum += budget[i];
    }

    return monthsum <= m ;
}
