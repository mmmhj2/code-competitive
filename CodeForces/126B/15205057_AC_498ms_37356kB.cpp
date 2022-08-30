#include <unordered_set>
#include <iostream>
#include <string>
#include <set>
using namespace std;

const int MAXN = 1000000 + 5;

int fail[MAXN];
void getFail(const string & pattern)
{
    int len = pattern.length();
    int i = 1, j = 0;
    fail[0] = -1, fail[1] = 0;

    while(i < len)
    {
        if(j == -1 || pattern[i] == pattern[j])
            fail[++i] = ++j;
        else
            j = fail[j];
    }
}
bool hasSolution;
set <int> appeared;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    string str;
    int len;

    cin >> str ;
    len = str.length();
    getFail(str);

    for(int i = 0; i < len; i++)
        appeared.insert(fail[i]);

    while(fail[len] > 0)
    {
        if(appeared.find(fail[len]) != appeared.end())
        {
            hasSolution = true;
            cout << str.substr(0, fail[len]) << endl ;
            break;
        }
        len = fail[len];
    }
    if(!hasSolution)
        cout << "Just a legend" << endl ;
    return 0;
}
