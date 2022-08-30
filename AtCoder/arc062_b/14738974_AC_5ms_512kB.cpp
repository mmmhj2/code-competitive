#include <algorithm>
#include <iostream>
#include <iterator>
#include <cstdio>
#include <vector>
#include <cmath>
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

using i64 = long long;

int N;
string str;


int main()
{
    int g = 0, p = 0;
    cin >> str ;

    for(string::iterator itr = str.begin(); itr != str.end(); itr++)
        if(*itr == 'p')
            p++;
        else
            g++;

    DEBUGVAR(p);
    DEBUGVAR(g);

    if(p >= g)
        cout << 0 << endl ;
    else
        cout << (g-p)/2 << endl ;

    return 0;
}
