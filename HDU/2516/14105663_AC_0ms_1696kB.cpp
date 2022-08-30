#include <algorithm>
#include <iostream>
using namespace std;
const int MAXF = 90;
long long fib[MAXF + 5];

void initFib()
{
    fib[1] = 1;
    for(int i = 2; i <= MAXF; i++)
        fib[i] = fib[i-1] + fib[i-2];
}

int main()
{
    initFib();
    int n;
    while(cin >> n)
    {
        if(!n)
            break;
        if(binary_search(&fib[1], &fib[MAXF], n))
            cout << "Second win" << endl ;
        else
            cout << "First win" << endl ;
    }
    return 0;
}
