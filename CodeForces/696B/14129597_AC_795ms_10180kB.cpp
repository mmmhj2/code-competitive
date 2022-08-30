#include <functional>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <vector>
using namespace std;

const int MAXN = 100000;

vector <int> Adj[MAXN + 5];
int chCnt[MAXN + 5];
double ans[MAXN + 5];

struct getChProc : public binary_function<int, int, void>
{
    void operator () (const int & fa, const int & cur) const;
};
struct getAnsProc : public binary_function<int, int, void>
{
    void operator () (const int & fa, const int & cur) const;
};

void getCh(int cur)
{
    chCnt[cur] = Adj[cur].size();
    for_each(Adj[cur].begin(), Adj[cur].end(), bind1st(getChProc(), cur));
}

void getAns(int cur)
{
    for_each(Adj[cur].begin(), Adj[cur].end(), bind1st(getAnsProc(), cur));
}

void getChProc::operator() (const int & fa,const int & cur) const
{
    getCh(cur);
    chCnt[fa] += chCnt[cur];
}

void getAnsProc::operator()(const int& fa, const int& cur) const
{
    ans[cur] = ans[fa] + 1 + (chCnt[fa] - chCnt[cur] - 1) / 2.0;
    getAns(cur);
}


int main()
{
    int n, u;
    cin >> n ;

    for(int i = 2; i <= n; i++)
        cin >> u , Adj[u].push_back(i);

    getCh(1);
    ans[1] = 1;
    getAns(1);
    for(int i = 1; i <= n; i++)
        cout << (i == 1 ? "" : " ") << fixed << setprecision(6) << ans[i] ;
    cout << endl ;
}
