#include <algorithm>
#include <iostream>
#include <iterator>
#include <cstring>
#include <string>
#include <vector>
using namespace std;


struct SuffixAutomaton
{
    static const int MAXN = 500000 + 10;
    static const int MAX_APLHABET = 30;
    string s;

    int son[MAXN][MAX_APLHABET];
    int pre[MAXN], step[MAXN];
    int last, total;

    void push_back(int val)
    {
        step[++total] = val;
    }

    void append(char c)
    {
        int ch = c - 'a' ;
        this->push_back(step[last] + 1);

        int p = last, np = total;

        while(p && !son[p][ch])
            son[p][ch] = np, p = pre[p];

        if(!p)
            pre[np] = 1;
        else
        {
            int q = son[p][ch];
            if(step[q] != step[p]+1)
            {
                this->push_back(step[p] + 1);
                int nq = total;
                memcpy(son[nq], son[q], sizeof son[q]);

                pre[nq] = pre[q];
                pre[q] = pre[np] = nq;

                while(son[p][ch] == q)
                    son[p][ch] = nq, p = pre[p];
            }
            else
                pre[np] = q;
        }
        last = np;
    }
/*
    vector <int> stk;
    void DEBUG(int cur, int fa)
    {

        for(int x : stk)
            cerr << (char)(x + 'a') ;
        cerr << endl ;

        for(int i = 0; i < 26; i++)
        {
            if(son[cur][i] == fa || (!son[cur][i]))
                continue;

            stk.push_back(i);
            DEBUG(son[cur][i], cur);
            stk.pop_back();
        }
    }
*/
    SuffixAutomaton() = delete;
    SuffixAutomaton(const SuffixAutomaton &) = default;
    SuffixAutomaton(const string & str)
    {
        s = str;
        total = last = 1;
        memset(son, 0, sizeof son);
        memset(pre, 0, sizeof pre);
        memset(step, 0, sizeof step);

        for(string::iterator itr = s.begin(); itr != s.end(); itr++)
            this->append(*itr);

        //DEBUG(1, 0);
    }
};

SuffixAutomaton * SAM;
int ans;

int main()
{
    string a, b;
    cin >> a >> b ;
    SAM = new SuffixAutomaton(a);

    int ptr = 1, len = 0;

    for(string::iterator itr = b.begin(); itr != b.end(); itr++)
    {
        int cur = *itr - 'a';
        if(SAM->son[ptr][cur])
            len++, ptr = SAM->son[ptr][cur];
        else
        {
            while(ptr && !SAM->son[ptr][cur])
                ptr = SAM->pre[ptr];

            if(!ptr)
                len = 0, ptr = 1;
            else
                len = SAM->step[ptr] + 1, ptr = SAM->son[ptr][cur];
        }
        //cerr << *itr << " " << len << endl ;
        ans = max(ans, len);
    }

    cout << ans << endl ;

    return 0;
}
