#include <algorithm>
#include <iterator>
#include <iostream>
//#include <iomanip>
//#include <cstring>
//#include <cstdlib>
#include <string>
#include <vector>
//#include <queue>
//#include <cmath>
//#include <set>
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

typedef long long i64;

vector <i64> vec;
string str;
string t1, t2;
i64 ans;

void DFS(string s)
{
    if(s.size() <= 0)
    {
        for(i64 x : vec)
            ans += x;
        return ;
    }

    for(string::iterator itr = s.begin(); itr != s.end(); itr++)
    {
        t1 = string(s.begin(), itr+1);
        t2 = string(itr+1, s.end());
        //DEBUGVAR(t1);
        //DEBUGVAR(t2);
        //DEBUGVAR(stol(t1));
        vec.push_back(stoll(t1));
        DFS(t2);
        vec.pop_back();
    }
}

int main()
{
    cin >> str ;
    DFS(str);
    cout << ans << endl ;
}


