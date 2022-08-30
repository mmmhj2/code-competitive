#include <algorithm>
#include <iterator>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <set>
using namespace std;

#ifdef LOCAL
#define DEBUG(l, r) \
{   \
    cerr << "[调试 @ " << __LINE__ << " : " << __FUNCTION__ << "]" ;    \
    copy(l, r, ostream_iterator<decltype(*l)>(cerr, " "));          \
    cerr << endl ;                                                  \
}
#else
#define DEBUG(l, r)
#endif // LOCAL

const int MAXN = 10000 + 15;
const int MAXM = 10000 + 5;

struct disjointSet{
    int fa[MAXN*MAXN+20];

    void clear(int N)
    {
        for(int i = 0; i <= N; i++)
            fa[i] = i;
    }

    disjointSet(int N)
    {
        clear(N);
    }

    int find(int x)
    {
        if(fa[x] == x)
            return x;
        return fa[x] = find(fa[x]);
    }

    void unite(int x, int y)
    {
        if(x < 2)
            swap(x, y);
        fa[find(x)] = find(y);
    }
};

string lft, rgt;
int K, l, r;
int repeat[30];
int alphaBegin[30];
int HP[MAXN*MAXN];
disjointSet dS(MAXN);
vector <int> lf, rt;

// 高精输出
void ProcessOutput(int x)
{
    if(x == -1)
    {
        cout << 0 << endl;
        return ;
    }
    if(x == 0)
    {
        cout << 1 << endl ;
        return ;
    }
    memset(HP, 0x00, sizeof HP);
    HP[0] = 2;
    int len = 0;

    for(int i = 1; i < x; i++)
    {
        int carry = 0;
        for(int k = 0; k <= len; k++)
        {
            HP[k] = HP[k] * 2 + carry;
            carry = HP[k] / 10;
            HP[k] = HP[k] % 10;
        }
        if(carry)
            HP[++len] = carry;
    }

    for(int i = len; i >= 0; i--)
        cout << HP[i] ;
    cout << endl ;
}

int getAns(int cur)
{
    for(int i = 0; i < lf.size(); i++)
    {
        int u = dS.find(lf[i]),
            v = dS.find(rt[i]);
        if(u == v)
            continue;
        if(u == 0 && v == 1)
            return -1;
        if(v == 0 && u == 1)
            return -1;
        dS.unite(u, v);
        cur--;
    }
    return cur;
}

int main()
{
    int T;
    cin >> T ;

    while(T--)
    {
        memset(alphaBegin, 0x00, sizeof alphaBegin);
        lf.clear(), rt.clear();
        alphaBegin[0] = 2;
        int cnt = 0, alpSum = 0;

        cin >> K ;
        for(int i = 1; i <= K; i++)
            cin >> repeat[i],
            alphaBegin[i] += alphaBegin[i-1],
            alphaBegin[i+1] += repeat[i],
            alpSum += repeat[i];

        dS.clear(alpSum + 5);
        cnt = alpSum;

        cin >> l >> lft >> r >> rgt;

        for(string::iterator itr = lft.begin(); itr != lft.end(); itr++)
        {
            switch(*itr)
            {
            case '1':
                lf.push_back(1);
                break;
            case '0':
                lf.push_back(0);
                break;
            default:
                for(int i = 0; i < repeat[*itr-'a'+1]; i++)
                    lf.push_back(alphaBegin[*itr-'a'+1]+i);
            }
        }
        DEBUG(lf.begin(), lf.end());

        for(string::iterator itr = rgt.begin(); itr != rgt.end(); itr++)
        {
            switch(*itr)
            {
            case '1':
                rt.push_back(1);
                break;
            case '0':
                rt.push_back(0);
                break;
            default:
                for(int i = 0; i < repeat[*itr-'a'+1]; i++)
                    rt.push_back(alphaBegin[*itr-'a'+1]+i);
            }
        }

        DEBUG(rt.begin(), rt.end());

        cnt = getAns(cnt);
        cerr << cnt << endl ;

        DEBUG(dS.fa, &dS.fa[alpSum+2]);

        if(lf.size() != rt.size())
        {
            cout << 0 << endl;
            continue;
        }

        if(K == 0)
        {
            if(lft == rgt)
                cout << 1 << endl ;
            else
                cout << 0 << endl ;
            continue;
        }

        ProcessOutput(cnt);
    }
}
