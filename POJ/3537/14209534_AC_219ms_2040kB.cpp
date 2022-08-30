#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 2000 + 5 ;
int SG[MAXN];

int getSG(int cur)
{
    if(cur < 0)
        return 0;
    if(SG[cur] >= 0)
        return SG[cur];

    bool mex[MAXN] = {0};   int _mex = 0;
    for(int i = 1; i <= cur; i++)
        mex[getSG(i-3) ^ getSG(cur-i-2)] = true;

    while(mex[_mex])
        _mex++;
    return SG[cur] = _mex;
}

int main()
{
    memset(SG, 0xff, sizeof SG);
    int n;
    cin >> n ;
    cout << (getSG(n) ? 1 : 2) << endl ;
    return 0;
}
