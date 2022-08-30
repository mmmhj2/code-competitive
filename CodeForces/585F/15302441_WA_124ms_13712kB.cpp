#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <queue>
#include <ctime>
using namespace std;

typedef long long i64;
const int INF = 0x7FFFFFFF;
const int MOD = 1e9 + 7;
const int MAXN = 1000 + 10;

string str, A, B;
int N, D;

struct AhoCorasickAutomata
{
    static const int CHARSET_SIZE = 10;
    //static const int MAX_WORD_CNT = 1010 + 10;
    //static const int MAX_WORD_LEN = 1000 + 10;
    static const int PREALLOCATE_SIZE = 125000 + 10;
    static const int TRIE_ROOT = 1;
    typedef struct _node
    {
        int ch[CHARSET_SIZE];
        int fail;
        bool isTail;
    } node, *pnode;

    node preAlloc[PREALLOCATE_SIZE];
    int AllocCnt;

    inline int getID(char c)
    {
        return c - '0';
    }

    inline void AllocNew()
    {
        AllocCnt++;
        for(int i = 0; i < CHARSET_SIZE; i++)
            preAlloc[AllocCnt].ch[i] = 0;
        preAlloc[AllocCnt].fail = TRIE_ROOT;
        preAlloc[AllocCnt].isTail = 0;
    }
    void clear()
    {
        AllocCnt = 0;
        AllocNew();
    }

    void insert(const char * s)
    {
        //cerr << s << endl ;
        int len = strlen(s);
        int p = TRIE_ROOT;

        for(int i = 0; i < len; i++)
        {

            int t = getID(s[i]);
            if(preAlloc[p].ch[t] < TRIE_ROOT)
            {
                AllocNew();
                preAlloc[p].ch[t] = AllocCnt;
            }
            p = preAlloc[p].ch[t];

        }
        preAlloc[p].isTail = true;
    }

    void initFail()
    {
        queue <int> q;
        int p(TRIE_ROOT);
        preAlloc[p].fail = p;
        q.push(p);

        while(!q.empty())
        {
            p = q.front();
            q.pop();

            if(preAlloc[p].isTail)
            {
                for(int i = 0; i < CHARSET_SIZE; i++)
                    preAlloc[p].ch[i] = p;
                continue;
            }

            for(int i = 0; i < CHARSET_SIZE; i++)
                if(preAlloc[p].ch[i] > TRIE_ROOT)
                {
                    int ch = preAlloc[p].ch[i];
                    int fl = preAlloc[p].fail;

                    if(p != TRIE_ROOT)
                        preAlloc[ch].fail = preAlloc[fl].ch[i];

                    q.push(ch);
                }
                else
                    preAlloc[p].ch[i] = preAlloc[preAlloc[p].fail].ch[i];
        }
    }

    AhoCorasickAutomata()
    {
        this->clear();
        for(int i = 0; i < CHARSET_SIZE; i++)
            preAlloc[0].ch[i] = 1;
    }
} Main;

typedef struct _tagDPARRAY
{
    i64 dp[2][2][AhoCorasickAutomata::PREALLOCATE_SIZE];
} DPARRAY, *PDPARRAY;

DPARRAY dp1, dp2;
PDPARRAY dpNew, dpOld;

i64 Calc(const char * s, const AhoCorasickAutomata & ACA)
{
    dpNew = &dp1, dpOld = &dp2;
    memset(dpNew, 0x00, (sizeof (DPARRAY)));
    memset(dpOld, 0x00, (sizeof (DPARRAY)));
    dpNew->dp[1][1][1] = 1;

    for(int p = 0; p < D; p++)
    {
        swap(dpNew, dpOld);
        memset(dpNew, 0x00, (sizeof (DPARRAY)));
        for(int i = 0; i < 2; i++)
            for(int j = 0; j < 2; j++)
                for(int k = 1; k <= ACA.AllocCnt; k++)
                {
                    if(!dpOld->dp[i][j][k])
                        continue;
                    i64 tmp = dpOld->dp[i][j][k] % MOD;

                    int ed = (j == 1 ? s[p] - '0' : 9);
                    for(int x = 0; x <= ed; x++)
                    {
                        int newi = i & ((int)x == 0);
                        int newj = j & ((int)x == ed);
                        int newk ;
                        if(x == 0 && i != 0)
                            newk = AhoCorasickAutomata::TRIE_ROOT;
                        else
                            newk = ACA.preAlloc[k].ch[x];
                        if(newk == 0)
                            newk = AhoCorasickAutomata::TRIE_ROOT;
                        dpNew->dp[newi][newj][newk] += tmp;
                    }
                }
    }

    i64 ret = 0;

    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 2; j++)
            for(int k = 1; k <= ACA.AllocCnt; k++)
                if(ACA.preAlloc[k].isTail && dpNew->dp[i][j][k])
                    ret = (ret + (dpNew->dp[i][j][k]% MOD)) % MOD;

    //cerr << ret << endl ;
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> str >> A >> B ;
    D = A.length(), N = str.length();

    for(int i = 0; i + D / 2 - 1 < N; i++)
        Main.insert(str.substr(i, D / 2).c_str());
    Main.initFail();

    i64 ans = Calc(B.c_str(), Main) - Calc(A.c_str(), Main);

    int p = AhoCorasickAutomata::TRIE_ROOT;
    for(int i = 0; i < D; i++)
        if(Main.preAlloc[p].ch[Main.getID(A[i])])
            p = Main.preAlloc[p].ch[Main.getID(A[i])];
        else
            p = AhoCorasickAutomata::TRIE_ROOT;
    //cerr << p << endl ;
    if(Main.preAlloc[p].isTail)
        ans++;
    ans = (ans + MOD) % MOD;
    cout << ans << endl ;
    return 0;
}

