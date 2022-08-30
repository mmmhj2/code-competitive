#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

int n, maxDepth;
vector <int> backtrace;

int IteratingSearch(int depth)
{
    if(depth >= maxDepth)
    {
        if(backtrace[depth] == n)
            return true;
        return false;
    }

    for(int i = 0; i <= depth; i++)
    {
        for(int j = i; j <= depth; j++)
        {
            int res = backtrace[i] + backtrace[j];
            if(res <= backtrace[depth])
                continue;
            if(res > n)
                continue;

            int tmp = res;
            for(int cur = depth+2; cur <= maxDepth; cur++)
                tmp *= 2;

            if(tmp < n)
                continue;

            backtrace.push_back(res);
            if(IteratingSearch(depth+1))
                return true;
            backtrace.pop_back();
        }
    }
    return false;
}

int main()
{
    while(true)
    {
        cin >> n ;
        if(n == 0)
            break;
        backtrace.clear();
        backtrace.push_back(1);

        int curMaxDepth = 0, m = 1;

        while(m < n)
        {
            m *= 2;
            curMaxDepth++;
        }


        for(maxDepth = curMaxDepth; ; maxDepth++)
            if(IteratingSearch(0))
                break;

        cout << *backtrace.begin() ;
        for(vector<int>::iterator itr = backtrace.begin()+1; itr != backtrace.end(); itr++)
            cout << " " << *itr ;
        cout << endl ;
    }
    return 0;
}
