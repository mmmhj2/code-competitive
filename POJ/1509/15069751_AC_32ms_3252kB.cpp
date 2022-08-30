#include <algorithm>
#include <iostream>
#include <iterator>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

const int MAXN = 10000 + 10 ;

int N;
int ans[MAXN * 2];
struct SuffixAutomaton
{
    static const int MAXN = 10000 + 10;
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

int main()
{

    int kase;
    cin >> kase;

    while(kase--)
    {
        int orgLen;
        string str;
        cin >> str;
        orgLen = N = str.length();

        for(int i = 0; i < N; i++)
            str.push_back(str[i]);

        N = str.length();
        SAM = new SuffixAutomaton(str);

        int p = SuffixAutomaton::ROOT;
        for(int i = 0; i < orgLen; i++)
        {
            bool flag = false;
            for(int j = 0; j < SuffixAutomaton::MAX_APLHABET; j++)
                if(SAM->node[p].son[j])
                {
                    flag = true;
                    p = SAM->node[p].son[j];
                    break;
                }
            if(!flag)
                break;
        }

        cout << SAM->node[p].maxm - orgLen + 1 << endl ;
        delete SAM;
    }

    return 0;
}
