#include <algorithm>
#include <iostream>
#include <iterator>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

const int MAXN = 250000 + 10 ;

int N;
int ans[MAXN * 2];
struct SuffixAutomaton
{
    static const int MAXN = 250000 + 10;
    static const int MAX_APLHABET = 30;
    static const int ROOT = 1;
    string s;

    struct AutoNode
    {
        int son[MAX_APLHABET];
        int pre;
        // Maximum length of match
        int maxm;

        int contrib;
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

    int Bin[MAXN], id[MAXN * 2];
    void radix_sort()
    {
        for(int i = 1; i <= total; i++)
            Bin[node[i].maxm]++;
        for(int i = 1; i <= N; i++)
            Bin[i] += Bin[i-1];
        for(int i = 1; i <= total; i++)
            id[Bin[node[i].maxm]--] = i;
    }

    void getAns()
    {
        int p = ROOT;

        for(string::const_iterator itr = s.begin(); itr != s.end(); itr++)
            p = node[p].son[*itr-'a'],
            node[p].contrib++;

        for(int i = total; i > 1; i--)
        {
            int t = node[id[i]].maxm;
            ans[t] = max(ans[t], node[id[i]].contrib);
            node[node[id[i]].pre].contrib += node[id[i]].contrib;
        }
    }


    SuffixAutomaton(const string & str)
    {
        s = str;
        total = last = 1;
        memset(node, 0, sizeof node);

        for(string::iterator itr = s.begin(); itr != s.end(); itr++)
            this->append(*itr);

        this->radix_sort();
    }
};

SuffixAutomaton * SAM;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    string str;
    cin >> str;
    N = str.length();

    SAM = new SuffixAutomaton(str);

    SAM->getAns();

    for(int i = N - 1; i > 0; i--)
        ans[i] = max(ans[i], ans[i+1]);
    for(int i = 1; i <= N; i++)
        cout << ans[i] << endl ;

    return 0;
}
