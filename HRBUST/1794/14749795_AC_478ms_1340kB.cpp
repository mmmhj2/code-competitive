#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 50000 + 50;

int TREE[MAXN];
int N;

inline int LOBIT(int x)
{
    return x&(-x);
}

void Add(int x, int delta)
{
    while(x <= N)
    {
        TREE[x] += delta;
        x += LOBIT(x);
    }
}

int Query(int x)
{
    int ans = 0;
    while(x > 0)
    {
        ans += TREE[x];
        x -= LOBIT(x);
    }
    return ans ;
}

int main()
{
    int kase, k;
    scanf("%d", &kase);
    k = kase;
    while(k--)
    {
        memset(TREE, 0x00, sizeof TREE);
        char str[20];
        int x, y;
        //cin >> N ;
        scanf("%d", &N);
        for(int i = 1; i <= N; i++)
            //cin >> x ,Add(i, x);
            scanf("%d", &x),
            Add(i, x);

        //cout << "Case " << kase - k << ":" << endl ;
        printf("Case %d:\n", kase - k);

        bool quit = true;
        while(quit)
        {
            scanf("%s", str);
            switch(str[0])
            {
            case 'E':
                quit = false;
                break;
            case 'A':
                scanf("%d%d", &x, &y);
                Add(x, y);
                break;
            case 'S':
                scanf("%d%d", &x, &y);
                Add(x, -y);
                break;
            case 'Q':
                scanf("%d%d", &y, &x);
                printf("%d\n", Query(x) - Query(y-1));
            }
        }
    }
    return 0;
}
