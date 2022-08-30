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
vector <int> A, T;

int main()
{

    cin >> N ;

    i64 a, t;
    i64 ansA, ansT;

    cin >> ansA >> ansT;
    for(int i = 1; i < N; i++)
    {
        cin >> a >> t;
        if(ansA % a)
            ansA = (ansA/a + 1) * a;

        if(ansT <= ansA / a * t)
            ansT = ansA / a * t;
        else
        {
            if(ansT % t)
                ansT = (ansT/t + 1) * t;
            ansA = ansT / t * a;
        }


    }
    cout << ansA + ansT << endl ;
    return 0;
}
