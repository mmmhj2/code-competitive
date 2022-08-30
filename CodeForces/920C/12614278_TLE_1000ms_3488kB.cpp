#include <iostream>
#include <string>
using namespace std;

const int MAXN = 200000;

int num[MAXN+5], n;
bool swapable[MAXN+5];
int fastjudge = 1;
string str;

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> num[i];
    cin >> str;
    for(int i = 0; i < n; i++)
    {
        swapable[i+1] = str[i]-'0';
        if(swapable[i+1] == false)
            fastjudge = -1;
        if(!swapable[i+1])
            if(num[i+2] < num[i+1])
                fastjudge = 0;
    }
    if(fastjudge == 1)
    {
        cout << "YES" << endl;
        return 0;
    }
    if(fastjudge == 0)
    {
        cout << "NO" << endl;
        return 0;
    }

    for(int i = 1; i <= n; i++)
    {
        int curpos = i, tarpos = num[i];
        for(int i = curpos; i < tarpos; i++)
            if(!swapable[i])
            {
                cout << "NO" << endl;
                return 0;
            }
    }
    cout << "YES" << endl;
    return 0;
}
