#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <cstdio>
#include <queue>
#include <ctime>
using namespace std;

typedef long long i64;
const int INF = 0x7FFFFFFF;
const i64 MOD = 1e9 + 9;

struct AhoCorasickAutomata
{
    static const int CHARSET_SIZE = 4;
    static const int MAX_WORD_CNT = 15;
    static const int MAX_WORD_LEN = 15;
    static const int PREALLOCATE_SIZE = MAX_WORD_CNT * MAX_WORD_LEN + 10;
    static const int TRIE_ROOT = 1;
    typedef struct _node
    {
        int ch[CHARSET_SIZE];
        int fail;
        int mxMth;
    } node, *pnode;

    node preAlloc[PREALLOCATE_SIZE];
    int AllocCnt;

    inline int getID(char c)
    {
        switch(c)
        {
        case 'A':
            return 0;
        case 'T':
            return 1;
        case 'C':
            return 2;
        default:
            return 3;
        }
    }

    inline void AllocNew()
    {
        AllocCnt++;
        for(int i = 0; i < CHARSET_SIZE; i++)
            preAlloc[AllocCnt].ch[i] = 0;
        preAlloc[AllocCnt].fail = 0;
        preAlloc[AllocCnt].mxMth = 0;
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
        preAlloc[p].mxMth = len;
    }

    void initFail()
    {
        queue <int> q;
        int p(TRIE_ROOT);
        preAlloc[p].fail = p;

        for(int i = 0; i < CHARSET_SIZE; i++)
            if(preAlloc[TRIE_ROOT].ch[i] > TRIE_ROOT)
                preAlloc[preAlloc[TRIE_ROOT].ch[i]].fail = TRIE_ROOT,
                                                    q.push(preAlloc[TRIE_ROOT].ch[i]);
            else
                preAlloc[TRIE_ROOT].ch[i] = TRIE_ROOT ;

        while(!q.empty())
        {
            p = q.front();
            q.pop();
            preAlloc[p].mxMth = max(preAlloc[p].mxMth, preAlloc[preAlloc[p].fail].mxMth);

            for(int i = 0; i < CHARSET_SIZE; i++)
                if(preAlloc[p].ch[i] < TRIE_ROOT)
                    preAlloc[p].ch[i] = preAlloc[preAlloc[p].fail].ch[i];
                else
                    preAlloc[preAlloc[p].ch[i]].fail = preAlloc[preAlloc[p].fail].ch[i],
                                                q.push(preAlloc[p].ch[i]);
        }
    }

    AhoCorasickAutomata()
    {
        this->clear();
    }
} Main;

char op[15];
int N, M;
i64 dp[1010][110][15];
int solve(const AhoCorasickAutomata & ACA)
{
    memset(dp, 0x00, sizeof dp);
    dp[0][1][0] = 1;

    for(int i = 0; i < N; i++)
        for(int j = 1; j <= ACA.AllocCnt; j++)
            for(int k = 0; k <= 10; k++)
                for(int c = 0; c < AhoCorasickAutomata::CHARSET_SIZE; c++)
                {
                    int t = ACA.preAlloc[j].ch[c];
                    if(ACA.preAlloc[t].mxMth >= k + 1)
                        dp[i+1][t][0] = (dp[i+1][t][0] + dp[i][j][k]) % MOD;
                    else
                        dp[i+1][t][k+1] = (dp[i+1][t][k+1] + dp[i][j][k]) % MOD;
                }

    i64 ans = 0;
    for(int i = 1; i <= ACA.AllocCnt; i++)
        ans = (ans + dp[N][i][0]) % MOD;

    return ans;
}


int main()
{
    cin >> N >> M ;

    for(int i = 1; i <= M; i++)
        cin >> op, Main.insert(op);
    Main.initFail();

    cout << solve(Main) << endl ;

    return 0;
}

