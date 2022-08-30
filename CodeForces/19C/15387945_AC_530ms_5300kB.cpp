#include <functional>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <list>
#include <map>
using namespace std;
typedef list<int> lst;
constexpr int MAXN = 100000 + 10 ;

map <int, lst> mp;

int a[MAXN], ans;

int main()
{
    int N ;

    cin >> N ;
    for(int i = 0; i < N; i++)
        cin >> a[i] , mp[a[i]].push_back(i);

    a[N] = -1;

    for(int i = 0; i < N; i++)
    {
        lst & l = mp[a[i]] ;
        l.pop_front();

        for(auto itr = l.begin(); itr != l.end(); itr++)
        {
            int t1 = i + 1, t2 = *itr + 1;

            while(t1 < *itr && a[t1] == a[t2])
                t1++, t2++;
            if(t1 == *itr)
                i = *itr - 1, ans = i+1;
        }
    }

    cout << N - ans << endl ;
    for(int i = ans; i < N; i++)
        cout << a[i] << " \n"[i == N-1];
    return 0;
}
