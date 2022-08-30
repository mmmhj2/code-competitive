#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 20;
const int K = 3;

int flip[MAXN+5], dir[MAXN+5];

int solve(int firstdir);

int main()
{
    for(int i = 1; i <= MAXN; i++)
        cin >> dir[i];
    cout << min(solve(1), solve(0)) << endl;
}

int solve(int firstdir)
{
    memset(flip, 0x00, sizeof flip);
    dir[0] = firstdir;
    int sum = 0, res = 0;
    for(int i = 0; i < MAXN; i++)
    {
        if((sum + dir[i]) & 1)
            flip[i] = 1, res++;
        sum += flip[i];
        if(i-2 >= 0)
            sum -= flip[i-2];
    }

    if((dir[MAXN]+flip[MAXN-1]+flip[MAXN-2]) & 1)
        return 0x7fffffff;
    return res;
}
