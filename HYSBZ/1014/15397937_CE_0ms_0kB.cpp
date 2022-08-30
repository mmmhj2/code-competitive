#include <functional>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdio>
#include <list>
#include <map>
using namespace std;
constexpr int MAXN = 150000 + 5 ;

typedef unsigned long long ui64;
ui64 Power[MAXN];
char str[MAXN];
int N, M;

namespace splayTree
{
    int rt, TreeSz, ch[MAXN][2], fa[MAXN], sz[MAXN], val[MAXN];
    ui64 Hash[MAXN];

    void Pushup(int x)
    {
        int l = ch[x][0], r = ch[x][1];
        sz[x] = sz[l] + sz[r] + 1;
        Hash[x] = Hash[l] + 1LL * val[x] * Power[sz[l]] + 1LL * Hash[r] * Power[sz[l]+1];
    }

    void Rotate(int x, int & k)
    {
        int y = fa[x], z = fa[fa[x]];
        int l, r;

        // Rotation indicator
        if(ch[y][0] == x)
            l = 0, r = 1;
        else
            r = 0, l = 1;

        if(y == k)      // x has reached the target
            k = x;
        else
        {
            if(ch[z][0] == y)
                ch[z][0] = x;
            else
                ch[z][1] = x;
        }
        fa[x] = z, fa[y] = x, fa[ch[x][r]] = y;
        ch[y][l] = ch[x][r], ch[x][r] = y;
        Pushup(y), Pushup(x);
    }

    void Splay(int x, int & k)
    {
        while(x != k)
        {
            int y = fa[x], z = fa[fa[x]];
            //cerr << "Splaying : " << x << " " << y << " " << z << endl ;
            if(y != k)  // rotate twice
            {
                if((ch[y][0] == x) ^ (ch[z][0] == y))
                    Rotate(x, k);
                else
                    Rotate(y, k);
            }
            Rotate(x, k);
        }
    }

    void build(int l, int r, int k)
    {
        if(l > r)
            return;
        if(l == r)
        {
            val[l] = Hash[l] = (str[l] - 'a' + 1);
            fa[l] = k, sz[l] = 1;
            if(l < k)
                ch[k][0] = l;
            else
                ch[k][1] = l;
            return;
        }

        int mid = (l + r) >> 1 ;
        build(l, mid-1, mid), build(mid+1, r, mid);
        val[mid] = str[mid] - 'a' + 1;
        fa[mid] = k;
        Pushup(mid);

        if(mid < k)
            ch[k][0] = mid ;
        else
            ch[k][1] = mid ;
    }

    int find(int k, int rnk)
    {
        int l = ch[k][0], r = ch[k][1];

        if(sz[l] + 1 == rnk)
            return k;
        else if(sz[l] >= rnk)
            return find(l, rnk);
        else
            return find(r, rnk - sz[l] - 1);
    }

    int getHash(int rnk, int val)
    {
        int x = find(rt, rnk), y = find(rt, rnk + val + 1);
        //cerr << "Trying to get Hash : " << x << " " << y << endl ;
        Splay(x, rt), Splay(y, ch[x][1]);
        //cerr << "Splaying Finished" << endl ;

        return Hash[ch[y][0]];
    }

    int query(int x, int y)
    {
        int L = 0, R = min(TreeSz-x, TreeSz-y);

        while(L + 1 < R)
        {
            int mid = (L + R) >> 1 ;
            //cerr << "Binary Searching : " << L << " " << R << " " << mid << endl ;
            if(getHash(x, mid) == getHash(y, mid))
                L = mid;
            else
                R = mid;
        }
        return L;
    }

    void insert(int k, int cval)
    {
        int x = find(rt, k+1), y = find(rt, k+2);
        Splay(x, rt), Splay(y, ch[x][1]);

        int newAlloc = TreeSz++;
        ch[y][0] = newAlloc;
        fa[newAlloc] = y;
        val[newAlloc] = cval;
        Pushup(newAlloc), Pushup(y), Pushup(x);
    }
};
using namespace splayTree;

int main()
{


    scanf("%s\n%d", str+2, &M);
    N = strlen(str+2);

    Power[0] = 1;
    for(int i = 1; i < MAXN; i++)
        Power[i] = Power[i-1] * 27;

    build(1, N + 2, 0);
    rt = (N + 3) >> 1;
    TreeSz = N + 2;

    int x, y;
    char op[5], op2[5];
    for(int i = 0; i < M; i++)
    {
        scanf("%s", op);

        switch(op[0])
        {
        case 'Q':
            scanf("%d%d", &x, &y);
            printf("%d\n", query(x, y));
            break;
        case 'R':
            scanf("%d%s", &x, op2);
            x = find(rt, x+1);
            Splay(x, rt);
            val[rt] = op2[0] - 'a' + 1;
            Pushup(rt);
            break;
        case 'I':
            scanf("%d%s", &x, op2);
            insert(x, op2[0] - 'a' + 1);
            break;
        }
    }

    return 0;
}
