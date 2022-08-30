#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <map>
using namespace std;

typedef long long i64;
const int MAXN = 100000 + 10;
const int MAXT = 1000000000 + 10;

struct BinaryIndexedTree
{
    map <int, int> data;
    int N;
    //#define LoBit(x) (x & (-x));

    BinaryIndexedTree()
    {
        N = MAXT;
    }

    inline static int LoBit(int x)
    {

        return (x & -x);
    }

    void add(int id, int delta)
    {
        while(id <= this->N)
            data[id] += delta,
            id += LoBit(id);
    }

    int query(int id)
    {
        int ans = 0;
        while(id)
            ans += data[id],
            id -= LoBit(id);
        return ans ;
    }
};

BinaryIndexedTree BIT[MAXN];
map <int, int> timestamp;

// Binary Indexed Tree - violent cards
int main()
{
    int N;
    cin >> N ;

    while(N--)
    {
        int op, x, t;
        cin >> op >> x >> t ;
        switch(op)
        {
        case 1:
            if(timestamp[t] == 0)
                timestamp[t] = timestamp.size();
            BIT[timestamp[t]].add(x, 1);
            break;
        case 2:
            BIT[timestamp[t]].add(x, -1);
            break;
        case 3:
            cout << BIT[timestamp[t]].query(x) << endl ;
        }
    }
    return 0;
}
