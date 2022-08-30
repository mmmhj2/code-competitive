#include <iostream>
using namespace std;

int mobius(int);

int main()
{
    int e;
    cin >> e;
    cout << mobius(e) << endl;
}

int mobius(int n)
{
    int cnt = 0, k = 0;

    for(int i = 2; i*i <= n; i++)
    {
        if(n % i)
            continue;

        cnt = 0, k++;

        while(n % i == 0)
        {
            n /= i;
            cnt++;
        }
        if(cnt >= 2)
            return 0;

        }
    if(n != 1)
        k++;
    return (k%2) ? -1 : 1;
}
