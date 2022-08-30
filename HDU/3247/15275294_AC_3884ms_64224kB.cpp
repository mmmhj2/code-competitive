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
    static const int CHARSET_SIZE = 2;
    static const int MAX_WORD_CNT = 1010 + 10;
    static const int MAX_WORD_LEN = 1000 + 10;
    static const int PREALLOCATE_SIZE = MAX_WORD_CNT * MAX_WORD_LEN + 10;
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
        return c - '0';
    }

    inline void AllocNew()
    {
        AllocCnt++;
        for(int i = 0; i < CHARSET_SIZE; i++)
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
        preAlloc[p].isTail = id;
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

            if(preAlloc[preAlloc[p].fail].isTail < 0)
                preAlloc[p].isTail = -1;
            if(preAlloc[preAlloc[p].fail].isTail > 0)
                preAlloc[p].isTail |= preAlloc[preAlloc[p].fail].isTail;

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

struct BFSNode
{
    int len, st;
    int cur;
};

bool vist[1030][50000 + 10 * 1000 + 10];
char op[50000 + 10];
int N, M;

int solve()
{
    BFSNode tmp, cur;
    queue <BFSNode> q;

    memset(vist, 0x00, sizeof vist);
    int target(0);
    for(int i = 0; i < N; i++)
        target |= (1 << i);

    tmp = (BFSNode){0, 0, AhoCorasickAutomata::TRIE_ROOT};
    q.push(tmp);

    while(!q.empty())
    {
        cur = q.front();
        q.pop();

        if(vist[cur.st][cur.cur])
            continue;
        vist[cur.st][cur.cur] = true;

        if(cur.st == target)
            return cur.len;

        const AhoCorasickAutomata::node & p = Main.preAlloc[cur.cur];

        for(int i = 0; i < 2; i++)
            if(Main.preAlloc[p.ch[i]].isTail < 0)
                continue;
            else
            {
                tmp.st = cur.st | Main.preAlloc[p.ch[i]].isTail;
                tmp.len = cur.len + 1;
                tmp.cur = p.ch[i];

                q.push(tmp);
            }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    while(cin >> N >> M && N && M)
    {
        Main.clear();
        for(int i = 1; i <= N; i++)
            cin >> op, Main.insert(op, (1 << (i - 1)));
        for(int i = 1; i <= M; i++)
            cin >> op, Main.insert(op, -1);
        Main.initFail();

        cout << solve() << endl ;
    }

    return 0;
}

