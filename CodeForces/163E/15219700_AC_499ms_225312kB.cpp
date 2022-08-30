#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <queue>
#include <ctime>
using namespace std;

typedef long long i64;
const int MAXN = 100000 + 10;
const int MAXM = 1000000 + 10;

int pos[MAXN];
int in[MAXM], out[MAXM];

inline int LoBit(int x)
{
    return x & (-x);
}

struct AhoCorasickAutomata
{
    static const int CHARSET_SIZE = 30;
    static const int PREALLOCATE_SIZE = MAXM;
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
        return c - 'a';
    }

    inline void AllocNew()
    {
        AllocCnt++;
        memset(preAlloc[AllocCnt].ch, 0x00, sizeof preAlloc[AllocCnt].ch);
        preAlloc[AllocCnt].fail = 0;
        preAlloc[AllocCnt].cnt = 0;
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
        preAlloc[p].cnt++;
        pos[id] = p;
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
                }
        }
    }

    int find(const char * s)
    {
        return 0;
    }
} Main;

char op[MAXM];
bool expel[MAXM];
i64 BIT[MAXM * 2];
int N, K;

vector <int> Adj[MAXM];
void AddEdge(int u, int v)
{
    // u -> v
    Adj[u].push_back(v);
}

void Modify(int x, i64 delta)
{
    int k = x;

    while(k <= Main.AllocCnt * 2)
        BIT[k] += delta, k += LoBit(k);
}
i64 Query(int x)
{
    i64 ans = 0;
    int k = x;
    while(k > 0)
        ans += BIT[k], k -= LoBit(k);
    return ans ;
}

i64 Query(const char * c)
{
    i64 ans = 0;
    int len = strlen(c);
    int cur = AhoCorasickAutomata::TRIE_ROOT;
    for(int i = 0; i < len; i++)
    {
        int t = Main.getID(c[i]);

        while(!Main.preAlloc[cur].ch[t] && cur != AhoCorasickAutomata::TRIE_ROOT)
            cur = Main.preAlloc[cur].fail;
        cur = Main.preAlloc[cur].ch[t];

        if(!cur)
            cur = AhoCorasickAutomata::TRIE_ROOT;

        ans += Query(in[cur]);
    }
    return ans ;
}

int TmStp;
void DFS(int cur, int fa)
{
    in[cur] = ++TmStp;
    for(vector<int>::iterator itr = Adj[cur].begin(); itr != Adj[cur].end(); itr++)
        if(*itr != fa)
            DFS(*itr, cur);
    out[cur] = ++TmStp;
}

int main()
{
    Main.clear();

    scanf("%d%d", &N, &K);
    for(int i = 1; i <= K; i++)
        scanf("%s", op), Main.insert(op, i);
    Main.initFail();

    for(int i = 1; i <= Main.AllocCnt; i++)
        AddEdge(Main.preAlloc[i].fail, i);
    DFS(1, 0);

    for(int i = 1; i <= K; i++)
        expel[i] = false, Modify(in[pos[i]], 1), Modify(out[pos[i]] + 1, -1);

    while(N--)
    {
        //cin >> op ;
        scanf("%s", op);
        if(op[0] == '?')
            cout << Query(op + 1) << endl ;
        else
        {
            int number;
            sscanf(op+1, "%d", &number);

            bool update = (op[0] == '-');
            if(expel[number] == update)
                continue;
            expel[number] = update;

            Modify(in[pos[number]], (update ? -1 : 1));
            Modify(out[pos[number]] + 1, (update ? 1 : -1));
        }
    }

    return 0;
}

