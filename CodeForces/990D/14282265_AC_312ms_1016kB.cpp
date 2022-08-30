#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1000 + 5 ;
bool MAT[MAXN][MAXN];

int main()
{
    int n, a, b;
    cin >> n >> a >> b ;

    if(min(a, b) > 1 || ((a == 1 && b == 1) && (n == 2 || n == 3)))
    {
        cout << "NO" << endl ;
        return 0;
    }

    cout << "YES" << endl ;

    int complement = 0;




    if(a == 1 && b == 1)
    {
        for(int i = 1; i <= n - a; i++)
            MAT[i][i-1] = MAT[i-1][i] = true;

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
                cout << MAT[i][j] ;
            cout << endl ;
        }
        return 0;
    }

    if(a == 1)
        swap(a, b), complement = true;

    for(int i = 1; i <= n - a; i++)
        MAT[i][i-1] = MAT[i-1][i] = true;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            cout << (int)(complement ^ MAT[i][j] && i != j) ;
        cout << endl ;
    }

    return 0;
}
