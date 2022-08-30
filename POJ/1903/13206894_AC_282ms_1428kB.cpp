#include <iostream>
#include <string>
#include <map>
using namespace std;

const int MAXN = 100;

struct _state
{
    const static int MAXLEN = 30;
    int chosen[MAXLEN];
    int chosencnt;
    void push_back(int _tp)
    {
        chosen[++chosencnt] = _tp;
    }

};

_state ans; int n;
string joints[MAXN+5];

map <int, _state> ansmap;

int dfs   (int cur, int chosenstr, _state curstate);
int revdfs(int cur, int chosenstr, _state curstate);

inline int setChosen(const string & joint, int prevVal)
{
    int len = joint.length();
    for(int i = 0; i < len; i++)
        prevVal ^= 1 << (int)(joint[i]-'A');
    return prevVal;
}

int main()
{
    _state st ;
    cin >> n ;
    for(int i = 1; i <= n; i++)
        cin >> joints[i] ;

    st.chosencnt = 0;
    dfs(1, 0, st);
    revdfs(n/2+1, 0, st);

    cout << ans.chosencnt << endl ;

    for(int i = 1; i <= ans.chosencnt; i++)
        if(i != 1)
            cout << " " << ans.chosen[i] ;
        else
            cout << ans.chosen[i] ;
    cout << endl ;

    return 0;
}

int dfs(int cur, int chosenstr, _state curstate)
{
    if(ansmap.find(chosenstr) == ansmap.end())
        ansmap[chosenstr] = curstate;
    if(ansmap[chosenstr].chosencnt < curstate.chosencnt)
        ansmap[chosenstr] = curstate;
    if(cur > n/2)
        return 0;

    dfs(cur+1, chosenstr, curstate);

    //curstate.chosencnt++;
    chosenstr = setChosen(joints[cur], chosenstr);
    //curstate.chosen[curstate.chosencnt] = cur;
    curstate.push_back(cur);

    dfs(cur+1, chosenstr, curstate);

    return 0;
}

int revdfs(int cur, int chosenstr, _state curstate)
{
    if(ansmap.find(chosenstr) != ansmap.end())
        if(ansmap[chosenstr].chosencnt + curstate.chosencnt > ans.chosencnt)
        {
            ans = ansmap[chosenstr];
            for(int i = 1; i <= curstate.chosencnt; i++)
                ans.push_back(curstate.chosen[i]);
        }
    if(cur > n)
        return 0;

    revdfs(cur+1, chosenstr, curstate);

    chosenstr = setChosen(joints[cur], chosenstr);
    curstate.push_back(cur);

    revdfs(cur+1, chosenstr, curstate);
    return 0;
}
