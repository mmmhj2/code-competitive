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
const int MAXN = 100000 + 10;

int pos[MAXN], posid;
vector <int> Adj[MAXN];
char op[MAXN + 10];
int N, M;
int TmStp;
int in[MAXN], out[MAXN];
int ans[MAXN];
int LastQuery[MAXN];
int BIT[MAXN * 2];
///////////////////////////////////////////////////////////////////
inline int LoBit(int x)
{
    return x & (-x);
}

struct Query
{
    int x, nxtQ;
}querys[MAXN];

void add(int x, int val)
{
    while(x <= TmStp)
    {
        BIT[x] += val;
        x += LoBit(x);
    }
}

int query(int x)
{
    int ans = 0;
    while(x)
    {
        ans += BIT[x];
        x -= LoBit(x);
    }
    return ans;
}

///////////////////////////////////////////////////////////////////
struct AhoCorasickAutomata
{
    static const int CHARSET_SIZE = 26;
    //static const int MAX_WORD_CNT = 1010 + 10;
    //static const int MAX_WORD_LEN = 1000 + 10;
    static const int PREALLOCATE_SIZE = 100000 + 10;
    static const int TRIE_ROOT = 1;
    typedef struct _node
    {
        int ch[CHARSET_SIZE];
        int fail;
        int fa;
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
        for(int i = 0; i < CHARSET_SIZE; i++)
            preAlloc[AllocCnt].ch[i] = 0;
        preAlloc[AllocCnt].fail = 0;
        preAlloc[AllocCnt].fa = 0;
    }
    void clear()
    {
        AllocCnt = 0;
        AllocNew();
    }

    void insert(const char * s)
    {
        int len = strlen(s);
        int p = TRIE_ROOT;

        for(int i = 0; i < len; i++)
        {
            if(s[i] == 'P')
                pos[++posid] = p;
            else if(s[i] == 'B')
                p = preAlloc[p].fa;
            else
            {
                int t = getID(s[i]);
                if(preAlloc[p].ch[t] < TRIE_ROOT)
                {
                    AllocNew();
                    preAlloc[p].ch[t] = AllocCnt;
                    preAlloc[AllocCnt].fa = p;
                }
                p = preAlloc[p].ch[t];
            }
        }
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
                    int ch = preAlloc[p].ch[i];
                    int fl = preAlloc[p].fail;

                    while(!preAlloc[fl].ch[i])
                        fl = preAlloc[fl].fail;
                    preAlloc[ch].fail = preAlloc[fl].ch[i];

                    q.push(ch);
                }
        }
    }

    AhoCorasickAutomata()
    {
        this->clear();
        for(int i = 0; i < CHARSET_SIZE; i++)
            preAlloc[0].ch[i] = 1;
    }
} Main;
///////////////////////////////////////////////////////////////////
void solve(AhoCorasickAutomata & ACA)
{
    int p = 1 ,id = 0, len = strlen(op);
    add(in[1], 1);

    for(int i = 0; i < len; i++)
    {
        switch(op[i])
        {
        case 'P':
            id++;
            for(int x = LastQuery[id]; x > 0; x = querys[x].nxtQ)
            {
                int to = pos[querys[x].x];
                ans[x] = query(out[to]) - query(in[to]-1);
            }
            break;
        case 'B':
            add(in[p], -1);
            p = ACA.preAlloc[p].fa;
            break;
        default:
            p = ACA.preAlloc[p].ch[ACA.getID(op[i])];
            add(in[p], 1);
        }
    }
}

void buildFailGraph(AhoCorasickAutomata & ACA)
{
    for(int i = 1; i <= ACA.AllocCnt; i++)
        Adj[ACA.preAlloc[i].fail].push_back(i);
}

void DFS(int cur)
{
    in[cur] = ++TmStp;

    for(vector<int>::iterator itr = Adj[cur].begin(); itr != Adj[cur].end(); itr++)
        DFS(*itr);

    out[cur] = ++TmStp;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> op ;
    Main.insert(op);
    Main.initFail();
    buildFailGraph(Main);
    DFS(0);

    cin >> M ;
    for(int i = 1; i <= M; i++)
    {
        int x, y;
        cin >> x >> y ;
        querys[i].nxtQ = LastQuery[y];
        querys[i].x = x;
        LastQuery[y] = i;
    }

    solve(Main);

    for(int i = 1; i <= M; i++)
        cout << ans[i] << endl ;

    return 0;
}

