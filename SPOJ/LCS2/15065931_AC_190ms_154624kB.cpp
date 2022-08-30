#include <algorithm>
#include <iostream>
#include <iterator>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

int N;
struct SuffixAutomaton
{
    static const int MAXN = 500000 + 10;
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

    ////////////////////////////////////////////////////////////////////////

    int Bin[MAXN], mapping[MAXN * 2];
    int MaxMatch[MAXN * 2], MinMatch[MAXN * 2];

    void radix_sort()
    {
        for(int i = 1; i <= total; i++)
            MinMatch[i] = node[i].maxm;
        for(int i = 1; i <= total; i++)
            Bin[MinMatch[i]]++;
        for(int i = 1; i <= N; i++)
            Bin[i] += Bin[i-1];
        for(int i = 1; i <= total; i++)
            mapping[Bin[MinMatch[i]]--] = i;
    }

    ////////////////////////////////////////////////////////////////////////

    void match(const string & m)
    {
        int p = ROOT, len = 0;
        for(int i = 1; i <= total; i++)
            MaxMatch[i] = 0;

        for(string::const_iterator itr = m.begin(); itr != m.end(); itr++)
        {
            int x = *itr - 'a';
            if(node[p].son[x])
                p = node[p].son[x], len++;
            else
            {
                while(p && !node[p].son[x])
                    p = node[p].pre;
                if(p)
                    len = node[p].maxm + 1, p = node[p].son[x];
                else
                    p = ROOT, len = 0;
            }

            MaxMatch[p] = max(MaxMatch[p], len);
        }

        for(int i = total; i >= 1; i--)
        {
            int cur = mapping[i];
            MinMatch[cur] = min(MinMatch[cur], MaxMatch[cur]);

            const int & fa = node[cur].pre;
            if(fa)
                MaxMatch[fa] = min(node[fa].maxm, max(MaxMatch[fa], MaxMatch[cur]));
        }
    }

    int LCSLen()
    {
        int ans = 0;
        for(int i = 1; i <= total; i++)
            ans = max(ans, MinMatch[i]);
        return ans;
    }

    SuffixAutomaton(const string & str)
    {
        s = str;
        total = last = 1;
        memset(node, 0, sizeof node);

        for(string::iterator itr = s.begin(); itr != s.end(); itr++)
            this->append(*itr);
    }
};

SuffixAutomaton * SAM;
int ans;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    string str;
    cin >> str;
    N = str.length();

    SAM = new SuffixAutomaton(str);
    SAM->radix_sort();

    while(cin >> str)
        SAM->match(str);

    cout << SAM->LCSLen() << endl ;

    return 0;
}
