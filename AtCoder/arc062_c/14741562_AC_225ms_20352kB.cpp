#include <algorithm>
#include <iostream>
#include <iterator>
#include <cstdio>
#include <vector>
#include <cmath>
#include <map>
using namespace std;


#ifdef LOCAL
#define DEBUGMSG()                                                              \
{                                                                               \
    cerr << "[调试 @" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "]" ;        \
}
#define DEBUGVAR(x)                                                             \
{                                                                               \
    cerr << "[调试 @" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "]:" ;       \
    cerr << "([" << typeid(x).name() << "]" << #x << ")" << x << endl ;         \
}
#define DEBUGARR(l, r)                                                          \
{                                                                               \
    cerr << "[调试 @" << __PRETTY_FUNCTION__ << ":" << __LINE__ << "]:" ;       \
    copy(l, r, ostream_iterator<decltype(*l)>(cerr, " "));                      \
    cerr << endl ;                                                              \
}
#else
#define DEBUGMSG()
#define DEBUGVAR(x)
#define DEBUGARR(l, r)
#endif // LOCAL

#define getBit(x) (col##x << (10 * (4-x)))

using i64 = long long;

const int MAXN = 500 ;

int N;
i64 COL[MAXN][8], tmp[4], ans;
map <i64, i64> mp;

i64 getHash(i64 col1, i64 col2, i64 col3, i64 col4)
{
    return getBit(1) | getBit(2) | getBit(3) | getBit(4);
}

void ModifyMap(i64 h, i64 delta)
{
    // Rotation
    for(int i = 0; i < 4; i++)
    {
        mp[h] += delta;
        //DEBUGVAR(h);
        h = (h >> 10) | ((h & 0x3FF) << 30);
    }

}



int main()
{
    cin >> N ;

    for(int i = 0; i < N; i++)
    {
        for(int c = 0; c < 4; c++)
            cin >> COL[i][c],
            COL[i][c+4] = COL[i][c];
        ModifyMap(getHash(COL[i][0], COL[i][1], COL[i][2], COL[i][3]), 1);
    }

    for(int i = 0; i < N; i++)
    {
        ModifyMap(getHash(COL[i][0], COL[i][1], COL[i][2], COL[i][3]), -1);
        for(int j = i+1; j < N; j++)
        {
            ModifyMap(getHash(COL[j][0], COL[j][1], COL[j][2], COL[j][3]), -1);
            for(int k = 0; k < 4; k++)
            {
                i64 tmpans = 1;
                tmp[0] = getHash(COL[j][k+1], COL[j][k+0], COL[i][1], COL[i][0]);
                tmp[1] = getHash(COL[j][k+0], COL[j][k+3], COL[i][2], COL[i][1]);
                tmp[2] = getHash(COL[j][k+3], COL[j][k+2], COL[i][3], COL[i][2]);
                tmp[3] = getHash(COL[j][k+2], COL[j][k+1], COL[i][4], COL[i][3]);

                for(int c = 0; c < 4; c++)
                    if(!mp[tmp[c]])
                        goto JMP;

                for(int c = 0; c < 4; c++)
                    tmpans *= mp[tmp[c]],
                    ModifyMap(tmp[c], -1);

                for(int c = 0; c < 4; c++)
                    ModifyMap(tmp[c], 1);
                ans += tmpans;

                JMP:
                    ;
            }
            ModifyMap(getHash(COL[j][0], COL[j][1], COL[j][2], COL[j][3]), 1);
        }
    }

    cout << ans << endl ;
    return 0;
}
