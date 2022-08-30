#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 120 + 10;

//coefficients
int co1[MAXN], co2[MAXN];

int main()
{
    int n;
    while(cin >> n)
    {
        // initiating coefficients
        // 1 + x + x^2 + x^3 + ...
        for(int i = 0; i <= n; i++)
            co1[i] = 1, co2[i] = 0;

        // Calculating multiplications
        for(int i = 2; i <= n; i++)
        {
            for(int j = 0; j <= n; j++)
                for(int k = 0; k+j <= n; k += i)
                    co2[j+k] += co1[j];

            for(int j = 0; j <= n; j++)
                co1[j] = co2[j], co2[j] = 0;
        }

        cout << co1[n] << endl ;
    }
    return 0;
}
