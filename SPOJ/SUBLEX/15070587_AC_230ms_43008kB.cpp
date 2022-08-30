#include <algorithm>
#include <iostream>
#include <iterator>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

const int MAXN = 90000 + 10 ;

int N;
int ans[MAXN * 2];
struct SuffixAutomaton
{
    static const int MAXN = 90000 + 10;
    static const int MAX_APLHABET = 30;
    static const int ROOT = 1;
    string s;

    struct AutoNode
    {
        int son[MAX_APLHABET];
        int pre;
        // Maximum length of match
        int maxm;
    };
    AutoNode node[MAXN * 2];
    int last, total;

    void push_back(int val)
    {
        node[++total].maxm = val;
    }

    void append(char c)
    {
        int ch = c - 'a' ;
        this->push_back(node[last].maxm + 1);

        int p = last, np = total;

        while(p && !node[p].son[ch])
            node[p].son[ch] = np, p = node[p].pre;

        if(!p)
            node[np].pre = 1;
        else
        {
            int q = node[p].son[ch];
            if(node[q].maxm != node[p].maxm+1)
            {
                this->push_back(node[p].maxm + 1);
                int nq = total;
                memcpy(node[nq].son, node[q].son, sizeof node[q].son);

                node[nq].pre = node[q].pre;
                node[q].pre = node[np].pre = nq;

                while(node[p].son[ch] == q)
                    node[p].son[ch] = nq, p = node[p].pre;
            }
            else
                node[np].pre = q;
        }
        last = np;
    }

    int F[MAXN * 2];

    int getCnt(int x)
    {
        if(F[x] > 0)
            return F[x];
        F[x] = 1;
        for(int i = 0; i < MAX_APLHABET; i++)
            if(node[x].son[i])
                F[x] += getCnt(node[x].son[i]);
        return F[x];
    }

    string output;
    void phraseOutput(int pos, int len)
    {
        if(--len == 0)
        {
            cout << output << endl ;
            output.clear();
            return;
        }

        for(int i = 0; i < MAX_APLHABET; i++)
        {
            const int & to = node[pos].son[i];
            if(!to)
                continue;
            if(F[to] < len)
            {
                len -= F[to];
            }
            else
            {
                output.push_back('a' + i);
                phraseOutput(to, len);
                return;
            }
        }
    }

    SuffixAutomaton(const string & str)
    {
        s = str;
        total = last = 1;
        memset(node, 0, sizeof node);
        memset(F, 0, sizeof F);

        for(string::iterator itr = s.begin(); itr != s.end(); itr++)
            this->append(*itr);
    }
};

SuffixAutomaton * SAM;

int main()
{
    string str;
    cin >> str;

    SAM = new SuffixAutomaton(str);
    SAM->getCnt(SuffixAutomaton::ROOT);

    int Q;
    cin >> Q;
    while(Q--)
    {
        int k;
        cin >> k;
        SAM->phraseOutput(SuffixAutomaton::ROOT, k + 1);
    }

    return 0;
}
