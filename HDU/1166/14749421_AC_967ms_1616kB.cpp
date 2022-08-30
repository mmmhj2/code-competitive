#include <iostream>
#include <cstring>
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
    cin >> kase ;
    k = kase;
    while(k--)
    {
        memset(TREE, 0x00, sizeof TREE);
        string str;
        int x, y;
        cin >> N ;
        for(int i = 1; i <= N; i++)
            cin >> x ,Add(i, x);

        cout << "Case " << kase - k << ":" << endl ;

        while(true)
        {
            cin >> str;
            if(str == "End")
                break;
            if(str == "Query")
                cin >> x >> y ,
                cout << Query(y) - Query(x-1) << endl ;
            if(str == "Add")
                cin >> x >> y ,
                Add(x, y);
            if(str == "Sub")
                cin >> x >> y ,
                Add(x, -y);
        }
    }
    return 0;
}
