#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <queue>
#include <ctime>
using namespace std;

int dp[1000 + 10][2000 + 10];
namespace AhoCorasickAutomata
{
static const int CHARSET_SIZE = 4;
static const int PREALLOCATE_SIZE = 2000 + 10;
static const int TRIE_ROOT = 1;
typedef struct _node
{
    int ch[CHARSET_SIZE];
    int fail;
    bool isTail;
} node, *pnode;

node preAlloc[PREALLOCATE_SIZE];
int AllocCnt;

char strmap[10] = "ACGT";
inline int getID(char c)
{
    switch(c)
    {
    case 'A':
        return 0;
    case 'C':
        return 1;
    case 'G':
        return 2;
    case 'T':
        return 3;
    }
}

inline void AllocNew()
{
    AllocCnt++;
    memset(preAlloc[AllocCnt].ch, 0x00, sizeof preAlloc[AllocCnt].ch);
    preAlloc[AllocCnt].fail = 0;
    preAlloc[AllocCnt].isTail = 0;
}
void clear()
{
    AllocCnt = 0;
    AllocNew();
}

void insert(const char * s)
{
    int len = strlen(s);
    int p = TRIE_ROOT, q = 0;

    for(int i = 0; i < len; i++)
    {
        int t = getID(s[i]);
        q = preAlloc[p].ch[t];
        if(q < TRIE_ROOT)
        {
            AllocNew();
            q = AllocCnt;
            preAlloc[p].ch[t] = q;
        }
        p = q;
    }
    preAlloc[p].isTail = true;
}

void initFail()
{
    queue <int> q;
    int p(TRIE_ROOT);
    preAlloc[p].fail = 0;
    q.push(p);

    while(!q.empty())
    {
        p = q.front();
        q.pop();

        for(int i = 0; i < CHARSET_SIZE; i++)
            if(preAlloc[p].ch[i])
            {
                int tmp = preAlloc[p].fail;
                while(tmp && !preAlloc[tmp].ch[i])
                    tmp = preAlloc[tmp].fail;
                if(tmp < TRIE_ROOT)
                    preAlloc[preAlloc[p].ch[i]].fail = TRIE_ROOT;
                else
                    preAlloc[preAlloc[p].ch[i]].fail = preAlloc[tmp].ch[i];

                q.push(preAlloc[p].ch[i]);

                if(tmp && preAlloc[tmp].isTail)
                    preAlloc[p].isTail = true;
            }
            else
            {
                if(p == TRIE_ROOT)
                    preAlloc[p].ch[i] = TRIE_ROOT;
                else
                    preAlloc[p].ch[i] = preAlloc[preAlloc[p].fail].ch[i];
            }
    }
}

int find(const char * s)
{
    memset(dp, 0x3F, sizeof dp);

    dp[0][1] = 0;
    int len = strlen(s);

    for(int i = 0; i < len; i++)
        for(int j = 1; j <= AllocCnt; j++)
            for(int k = 0; k < 4; k++)
            {
                if(preAlloc[preAlloc[j].ch[k]].isTail)
                    continue;
                if(s[i] == strmap[k])
                    dp[i+1][preAlloc[j].ch[k]] = min(dp[i][j], dp[i+1][preAlloc[j].ch[k]]);
                else
                    dp[i+1][preAlloc[j].ch[k]] = min(dp[i][j] + 1, dp[i+1][preAlloc[j].ch[k]]);
            }


    int ret = 0x3F3F3F3F;
    for(int i = 1; i <= AllocCnt; i++)
        ret = min(ret, dp[len][i]);

    return ((ret == 0x3F3F3F3F) ? -1 : ret);
}
};

using namespace AhoCorasickAutomata;
int N;
string str;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int kase = 0;
    while(cin >> N && N)
    {
        clear();
        for(int i = 1; i <= N; i++)
            cin >> str, insert(str.c_str());
        initFail();

        cin >> str ;
        cout << "Case " << ++kase << ": " << find(str.c_str()) << endl ;
    }
    return 0;
}

