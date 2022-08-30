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
    static const int PREALLOCATE_SIZE = 500 + 10;
    static const int TRIE_ROOT = 1;
    typedef struct _node
    {
        int ch[CHARSET_SIZE];
        int fail;
        int cnt;
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
        preAlloc[AllocCnt].cnt = 0;
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
        preAlloc[p].cnt++;
    }

    void initFail()
    {
        queue <int> q;
        int p(TRIE_ROOT);
        preAlloc[p].fail = p;

        for(int i = 0; i < CHARSET_SIZE; i++)
            if(preAlloc[TRIE_ROOT].ch[i] < TRIE_ROOT)
                preAlloc[TRIE_ROOT].ch[i] = TRIE_ROOT;
            else
                preAlloc[preAlloc[TRIE_ROOT].ch[i]].fail = TRIE_ROOT,
                q.push(preAlloc[TRIE_ROOT].ch[i]);

        while(!q.empty())
        {
            p = q.front(); q.pop();
            preAlloc[p].cnt += preAlloc[preAlloc[p].fail].cnt;

            for(int i = 0; i < 4; i++)
                if(preAlloc[p].ch[i] < TRIE_ROOT)
                    preAlloc[p].ch[i] = preAlloc[preAlloc[p].fail].ch[i];
                else
                    preAlloc[preAlloc[p].ch[i]].fail = preAlloc[preAlloc[p].fail].ch[i],
                    q.push(preAlloc[p].ch[i]);
        }
    }

    int dp[PREALLOCATE_SIZE][11 * 11 * 11 * 11 + 5];
    int digit[4], cnt[4];
    int find(const char * s)
    {
        int ret = 0;
        int len = strlen(s);

        memset(dp, 0xFF, sizeof dp);
        for(int i = 0; i < 4; i++)
            cnt[i] = digit[i] = 0;
        for(int i = 0; i < len; i++)
            cnt[getID(s[i])]++;

        digit[0] = (cnt[3] + 1) * (cnt[2] + 1) * (cnt[1] + 1);
        digit[1] = (cnt[3] + 1) * (cnt[2] + 1) ;
        digit[2] = (cnt[3] + 1) ;
        digit[3] = 1;

        dp[TRIE_ROOT][0] = 0;

        for(int A = 0; A <= cnt[0]; A++)
            for(int B = 0; B <= cnt[1]; B++)
                for(int C = 0; C <= cnt[2]; C++)
                    for(int D = 0; D <= cnt[3]; D++)
                    {
                        int sum = A * digit[0] + B * digit[1] + C * digit[2] + D * digit[3] ;
                        //cerr << sum << endl ;
                        for(int i = 1; i <= AllocCnt; i++)
                            if(dp[i][sum] >= 0)
                                for(int k = 0; k < 4; k++)
                                {
                                    if(A == cnt[0] && k == 0)
                                        continue;
                                    if(B == cnt[1] && k == 1)
                                        continue;
                                    if(C == cnt[2] && k == 2)
                                        continue;
                                    if(D == cnt[3] && k == 3)
                                        continue;

                                    int t = (preAlloc[i].ch[k] ? preAlloc[i].ch[k] : TRIE_ROOT);
                                    //cerr << "Updating : " << t << " " << sum + digit[k] << endl ;
                                    dp[t][sum + digit[k]] = \
                                        max(dp[t][sum + digit[k]], \
                                            dp[i][sum] + preAlloc[t].cnt);
                                }
                    }
        int sum = 0;
        for(int i = 0; i < 4; i++)
            sum += cnt[i] * digit[i];
        //cerr << sum << endl ;
        for(int i = 1; i <= AllocCnt; i++)
        {
            //cerr << dp[i][sum] << " " ;
            ret = max(ret, dp[i][sum]);
        }

        return ret;
    }

    AhoCorasickAutomata()
    {
        this->clear();
    }
} Main;

char op[100];
int N ;
int main()
{
    int kase = 0;
    while(cin >> N && N)
    {
        Main.clear();

        for(int i = 1; i <= N; i++)
            cin >> op, Main.insert(op);
        Main.initFail();
        cin >> op ;
        printf("Case %d: %d\n", ++kase, Main.find(op));
    }

    return 0;
}

