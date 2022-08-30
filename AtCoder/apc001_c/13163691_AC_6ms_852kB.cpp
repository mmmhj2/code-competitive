#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
using namespace std;
const int MAXN = 100000;
int SendQuery(int n);

struct _query
{
    int result;
    int query;
    _query(){};
    _query(int qu)
    {
        result = SendQuery(qu);
        query = qu;
    }
};

string str;

int N;

int SendQuery(int n)
{
    cout << n << endl << flush ;

    cin >> str ;
    if(str == "Vacant")
        exit(0);
    if(str == "Male")
        return 0;
    return 1;
}

int getExpAns(int curpos, _query prevQuery)
{
    if((curpos - prevQuery.query) & 1)
        return !(prevQuery.result);
    return prevQuery.result;
}

void binaryQuery()
{
    int l = 0, r = N;

    _query leftQuery, rightQuery;
    leftQuery.query = 0, leftQuery.result = SendQuery(0);
    rightQuery.query = N-1, rightQuery.result = SendQuery(N-1);

    while(r-l > 1)      // [l, r)
    {
        int mid = (l+r) >> 1;
        //cerr << "Expected Answer :" << getExpAns(mid, leftQuery) << endl ;
        _query MidQuery(mid);
        if(MidQuery.result == getExpAns(mid, leftQuery))
        {
            l = mid;
            leftQuery = MidQuery;
        }
        else
        {
            r = mid;
            rightQuery = MidQuery;
        }

    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> N;
    binaryQuery();
    return 0;
}
