#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <queue>
#include <ctime>
using namespace std;

struct AhoCorasickAutomata
{
    static const int CHARSET_SIZE = 2;
    static const int PREALLOCATE_SIZE = 100000 + 10;
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
        }
    }

    int find(const char * s)
    {
        int len = strlen(s);
        int p = TRIE_ROOT;
        int ret = 0;

        for(int i = 0; i < len; i++)
        {
            int t = s[i] - '0';

            while(!preAlloc[p].ch[t] && p != TRIE_ROOT)
                p = preAlloc[p].fail;
            p = preAlloc[p].ch[t];

            if(!p)
                p = TRIE_ROOT;

            for(int q = p; q != TRIE_ROOT; q = preAlloc[q].fail)
            {
                ret += preAlloc[q].isTail;
            }
        }
        return ret ;
    }
}Main, Buffer;

char op[5 * 1000000 + 10];
void moveString(int is, int ie, int js, int je)
{
    int leni = ie - is + 1;
    int lenj = je - js + 1;

    if(leni > 0 && lenj > 0)
    {
        for(int i = 0; i < min(leni, lenj); i++)
            swap(op[is+i], op[js+i]);
        if(leni > lenj)
            moveString(is + lenj, ie, js, je);
        else
            moveString(js, js + leni - 1, js + leni, je);
    }
}

const int THRESHOLD = 2000;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T ;
    for(int k = 1; k <= T; k++)
    {
        cout << "Case #" << k << ":" << endl ;
        Buffer.clear();
        Main.clear();
        int N , ans = 0, len;
        cin >> N ;

        for(int i = 1; i <= N; i++)
        {
            cin >> op ;
            len = strlen(op+1);
            ans = ans % len;
            moveString(1, ans, ans+1, len);
            if(op[0] == '+')
            {
                Buffer.insert(&op[1]);
                Buffer.initFail();

                if(Buffer.AllocCnt >= THRESHOLD)
                    ;
            }
            else
            {
                ans = Buffer.find(&op[1]);
                cout << ans << endl ;
            }
        }
    }

    return 0;
}

