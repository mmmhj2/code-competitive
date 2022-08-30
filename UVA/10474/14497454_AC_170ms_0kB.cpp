#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>

#define BEGIN "CASE# %d:\n"
#define NOT_FOUND "%d not found\n"
#define FOUND "%d found at %d\n"

using namespace std;


int main()
{
    int N, Q, kase = 1;

    while(cin >> N >> Q)
    {
        if((!N) && (!Q))
            break;
        int t;
        vector <int> vec;

        for(int i = 1; i <= N; i++)
            cin >> t, vec.push_back(t);

        sort(vec.begin(), vec.end());
        printf(BEGIN, kase++);

        for(int i = 1; i <= Q; i++)
        {
            int q;
            cin >> q ;
            if(!binary_search(vec.begin(), vec.end(), q))
                printf(NOT_FOUND, q);
            else
            {
                int pos = lower_bound(vec.begin(), vec.end(), q) - vec.begin();
                printf(FOUND, q, pos+1);
            }

        }
    }

    return 0;
}
