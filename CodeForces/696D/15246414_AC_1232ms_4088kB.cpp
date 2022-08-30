#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <queue>
#include <ctime>
using namespace std;

typedef long long i64;
const i64 INF = 0x7FFFFFFFFFFFFFFF;

struct AhoCorasickAutomata
{
    static const int CHARSET_SIZE = 26;
    static const int MAX_WORD_CNT = 200;
    static const int MAX_WORD_LEN = 100;
    static const int PREALLOCATE_SIZE = MAX_WORD_CNT * MAX_WORD_LEN + 10;
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
        for(int i = 0; i < CHARSET_SIZE; i++)
            preAlloc[AllocCnt].ch[i] = 0;
        preAlloc[AllocCnt].fail = 0;
        preAlloc[AllocCnt].cnt = 0;
    }
    void clear()
    {
        AllocCnt = 0;
        AllocNew();
    }

    void insert(const char * s, int val)
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
        preAlloc[p].cnt += val;
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
            preAlloc[p].cnt += preAlloc[preAlloc[p].fail].cnt;

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

struct Matrix
{
    static const int MAX_LENGTH = 220;
    i64 mat[MAX_LENGTH][MAX_LENGTH];
    int Len;

    Matrix(){}
    Matrix(int n, i64 init)
    {
        Len = n;
        for(int i = 1; i <= Len; i++)
            for(int j = 1; j <= Len; j++)
                mat[i][j] = init;
    }

    Matrix operator * (const Matrix & rhs)  const
    {
        Matrix ret(Len, -1);

        for(int i = 1; i <= Len; i++)
            for(int k = 1; k <= Len; k++)
                for(int j = 1; j <= Len; j++)
                    ret.mat[i][j] = max(ret.mat[i][j],(rhs.mat[i][k] == -1 || mat[k][j] == -1) ? -INF : rhs.mat[i][k] + mat[k][j] );

        return ret;
    }

    Matrix operator ^ (i64 exp)
    {
        Matrix ret(Len, 0);
        Matrix aux = *this;

        while(exp)
        {
            if(exp & 1)
                ret = ret * aux;
            aux = aux * aux;
            exp >>= 1;
        }

        return ret;
    }
};

Matrix constructMat(const AhoCorasickAutomata & ACA)
{
    Matrix ret (ACA.AllocCnt, -1);
    for(int i = 1; i <= ACA.AllocCnt; i++)
        for(int j = 0; j < AhoCorasickAutomata::CHARSET_SIZE; j++)
            ret.mat[i][ACA.preAlloc[i].ch[j]] = ACA.preAlloc[ACA.preAlloc[i].ch[j]].cnt ;
    return ret;
}

int N;
i64 L;
i64 ans;
int w[250];
char op[250];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> L ;
    for(int i = 1; i <= N; i++)
        cin >> w[i];
    for(int i = 1; i <= N; i++)
        cin >> op, Main.insert(op, w[i]);
    Main.initFail();

    Matrix m = constructMat(Main);

    m = m ^ L ;

    for(int i = 1; i <= Main.AllocCnt; i++)
        ans = max(ans, m.mat[1][i]);

    cout << ans << endl ;

    return 0;
}

