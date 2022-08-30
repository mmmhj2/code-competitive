#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <queue>
#include <ctime>
using namespace std;

typedef long long i64;

struct AhoCorasickAutomata
{
    static const int CHARSET_SIZE = 4;
    static const int PREALLOCATE_SIZE = 1000 + 10;
    static const int TRIE_ROOT = 1;
    typedef struct _node
    {
        int ch[CHARSET_SIZE];
        int fail;
        int isTail;
    } node, *pnode;

    node preAlloc[PREALLOCATE_SIZE];
    int AllocCnt;

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
        default:
            return 3;
        }
    }

    inline void AllocNew()
    {
        AllocCnt++;
        for(int i = 0; i < 4; i++)
            preAlloc[AllocCnt].ch[i] = 0;
        preAlloc[AllocCnt].fail = 0;
        preAlloc[AllocCnt].isTail = 0;
    }
    void clear()
    {
        AllocCnt = 0;
        AllocNew();
    }

    void insert(const char * s, int id)
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
        preAlloc[p].isTail |= (1 << id);
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
            p = q.front(); q.pop();
            preAlloc[p].isTail |= preAlloc[preAlloc[p].fail].isTail;

            for(int i = 0; i < 4; i++)
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

char op[105];
int w[20], W[1050];
int N, L;

typedef struct _DPARRAY
{
    int dp[1050][1050];
}DPARRAY, *PDPARRAY;

DPARRAY dp1, dp2;
PDPARRAY dpNew, dpOld;

int solve()
{
    dpNew = &dp1, dpOld = &dp2;
    memset(dpOld, 0x00, (sizeof (DPARRAY)));
    const int MAXMOV = (1 << N) ;
    const AhoCorasickAutomata::node * nodes = Main.preAlloc;

    // Pre-calculate weight for every possible status
    for(int i = 0; i < MAXMOV; i++)
    {
        W[i] = 0;
        for(int j = 0; (1 << j) <= i; j++)
            if(i & (1 << j))
                W[i] += w[j];
    }
    // Dynamic Programming
    dpOld->dp[1][0] = true;
    for(int i = 1; i <= L; i++)
    {
        memset(dpNew, 0x00, (sizeof (DPARRAY)));
        for(int j = 1; j <= Main.AllocCnt; j++)
            for(int k = 0; k < MAXMOV; k++)
                if(dpOld->dp[j][k])
                    for(int c = 0; c < 4; c++)
                    {
                        int x = nodes[j].ch[c];
                        int y = nodes[x].isTail;
                        dpNew->dp[x][(k | y)] = 1;
                    }
        swap(dpNew, dpOld);
    }
    // Calculate Answer
    int ret = 0x80000000 ;
    for(int i = 1; i <= Main.AllocCnt; i++)
        for(int j = 0; j < MAXMOV; j++)
            if(dpOld->dp[i][j])
                ret = max(ret, W[j]);
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    while(cin >> N >> L)
    {
        Main.clear();

        for(int i = 0; i < N; i++)
            cin >> op >> w[i], Main.insert(op, i);
        Main.initFail();

        int ans = solve();
        if(ans < 0)
            cout << "No Rabbit after 2012!" << endl ;
        else
            cout << ans << endl ;
    }

    return 0;
}

