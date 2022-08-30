#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <queue>
using namespace std;

namespace AhoCorasickAutomata
{
    static const int CHARSET_SIZE = 30;
    static const int PREALLOCATE_SIZE = 500000 + 10;
    static const int TRIE_ROOT = 1;
    typedef struct _node
    {
        int ch[CHARSET_SIZE];
        int fail;
        int cnt;
    }node, *pnode;

    node preAlloc[PREALLOCATE_SIZE];
    int AllocCnt;

    pnode AllocNew()
    {
        AllocCnt++;
        memset(preAlloc[AllocCnt].ch, 0x00, sizeof node::ch);
        preAlloc[AllocCnt].fail = 0;
        preAlloc[AllocCnt].cnt  = 0;
        return &preAlloc[AllocCnt];
    }
    void clear()
    {
        AllocCnt = 0;
        AllocNew();
        //memset(preAlloc, 0x00, sizeof preAlloc);
    }

    void insert(const char * s)
    {
        int len = strlen(s);
        int p = TRIE_ROOT, q = 0;

        for(int i = 0; i < len; i++)
        {
            int t = s[i] - 'a';
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
        int p(TRIE_ROOT), b;
        for(int i = 0; i < CHARSET_SIZE; i++)
            if(preAlloc[p].ch[i])
                preAlloc[preAlloc[p].ch[i]].fail  = TRIE_ROOT,
                q.push(preAlloc[p].ch[i]);

        while(!q.empty())
        {
            p = q.front();
            q.pop();

            for(int i = 0; i < CHARSET_SIZE; i++)
            {
                if(!preAlloc[p].ch[i])
                    continue;

                for(b = preAlloc[p].fail; b > 0; b = preAlloc[b].fail)
                    if(preAlloc[b].ch[i])
                    {
                        preAlloc[preAlloc[p].ch[i]].fail = preAlloc[b].ch[i];
                        break;
                    }

                if(b < TRIE_ROOT)
                    preAlloc[preAlloc[p].ch[i]].fail = TRIE_ROOT;

                q.push(preAlloc[p].ch[i]);
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
            int t = s[i] - 'a';

            while(!preAlloc[p].ch[t] && p != TRIE_ROOT)
                p = preAlloc[p].fail;
            p = preAlloc[p].ch[t];

            if(!p)
                p = TRIE_ROOT;

            for(int q = p; q != TRIE_ROOT; q = preAlloc[q].fail)
            {
                ret += preAlloc[q].cnt;
                preAlloc[q].cnt = 0;
            }
        }
        return ret ;
    }
};


int main()
{
    int kase ;
    char str[1000000];
    scanf("%d", &kase);

    while(kase--)
    {
        AhoCorasickAutomata::clear();
        int N;
        scanf("%d", &N);

        for(int i = 1; i <= N; i++)
            scanf("%s", str), AhoCorasickAutomata::insert(str);

        AhoCorasickAutomata::initFail();

        scanf("%s", str);
        printf("%d\n", AhoCorasickAutomata::find(str));
    }

    return 0;
}

/*
1
5
she
he
say
shr
her
yasherhs
*/

