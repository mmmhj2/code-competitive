#include <algorithm>
#include <iostream>
#include <iterator>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

// Struct Version
struct SuffixAutomaton
{
    static const int MAXN = 500000 + 10;
    static const int MAX_APLHABET = 30;
    string s;

    //int son[MAXN][MAX_APLHABET];
    //int pre[MAXN], step[MAXN];

    struct AutoNode
    {
        int son[MAX_APLHABET];
        int pre, stp;
    };
    AutoNode node[MAXN * 2];
    int last, total;

    void push_back(int val)
    {
        node[++total].stp = val;
    }

    void append(char c)
    {
        int ch = c - 'a' ;
        this->push_back(node[last].stp + 1);

        int p = last, np = total;

        while(p && !node[p].son[ch])
            node[p].son[ch] = np, p = node[p].pre;

        if(!p)
            node[np].pre = 1;
        else
        {
            int q = node[p].son[ch];
            if(node[q].stp != node[p].stp+1)
            {
                this->push_back(node[p].stp + 1);
                int nq = total;
                memcpy(node[nq].son, node[q].son, sizeof node[q].son);

                //pre[nq] = pre[q];
                node[nq].pre = node[q].pre;
                //pre[q] = pre[np] = nq;
                node[q].pre = node[np].pre = nq;

                while(node[p].son[ch] == q)
                    //son[p][ch] = nq, p = pre[p];
                    node[p].son[ch] = nq, p = node[p].pre;
            }
            else
                //pre[np] = q;
                node[np].pre = q;
        }
        last = np;
    }



    SuffixAutomaton() = delete;
    SuffixAutomaton(const SuffixAutomaton &) = default;
    SuffixAutomaton(const string & str)
    {
        s = str;
        total = last = 1;
        memset(node, 0, sizeof node);

        for(string::iterator itr = s.begin(); itr != s.end(); itr++)
            this->append(*itr);

        //DEBUG(1, 0);
    }
};

SuffixAutomaton * SAM;
int ans;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    string a, b;
    cin >> a >> b ;
    SAM = new SuffixAutomaton(a);

    int ptr = 1, len = 0;

    for(string::iterator itr = b.begin(); itr != b.end(); itr++)
    {
        int cur = *itr - 'a';
        if(SAM->node[ptr].son[cur])
            len++, ptr = SAM->node[ptr].son[cur];
        else
        {
            while(ptr && !SAM->node[ptr].son[cur])
                ptr = SAM->node[ptr].pre;

            if(!ptr)
                len = 0, ptr = 1;
            else
                len = SAM->node[ptr].stp + 1, ptr = SAM->node[ptr].son[cur];
        }
        //cerr << *itr << " " << len << endl ;
        ans = max(ans, len);
    }

    cout << ans << endl ;

    return 0;
}
