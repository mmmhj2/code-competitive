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
const int MOD = 10007;

struct AhoCorasickAutomata
{
    static const int CHARSET_SIZE = 4;
    static const int MAX_WORD_CNT = 6;
    static const int MAX_WORD_LEN = 5;
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

struct Matrix
{
    static const int MAX_LENGTH = 210;
    i64 mat[MAX_LENGTH][MAX_LENGTH];
    int Len;

    Matrix() {}
    Matrix(int n, i64 init)
    {
        Len = n;
        for(int i = 1; i <= Len; i++)
            for(int j = 1; j <= Len; j++)
                mat[i][j] = init;
    }

    void print()
    {
        for(int i = 1; i <= Len; i++)
        {
            if(i == 1)
                cout << "/" ;
            else if (i == Len)
                cout << "\\" ;
            else
                cout << "|" ;
            for(int j = 1; j <= Len; j++)
                cout << setw(4) << mat[i][j] ;

            cout << "   " ;
            if(i == 1)
                cout << "\\" ;
            else if (i == Len)
                cout << "/" ;
            else
                cout << "|" ;
            cout << endl;
        }
        cout << endl ;

    }

    Matrix operator * (const Matrix & rhs)  const
    {
        Matrix ret(Len, 0);

        for(int i = 1; i <= Len; i++)
            for(int j = 1; j <= Len; j++)
                for(int k = 1; k <= Len; k++)
                    if(mat[i][k] && rhs.mat[k][j])
                    {
                        ret.mat[i][j] += mat[i][k] * rhs.mat[k][j];
                        ret.mat[i][j] %= MOD ;
                    }

        return ret;
    }

    Matrix operator ^ (i64 exp)
    {
        Matrix ret(Len, 0);

        for(int i = 1; i <= Len; i++)
            ret.mat[i][i] = 1;

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
    Matrix ret (ACA.AllocCnt * 2, 0);

    for(int i = 1; i <= ACA.AllocCnt; i++)
        for(int j = 0; j < AhoCorasickAutomata::CHARSET_SIZE; j++)
        {
            int t = ACA.preAlloc[i].ch[j] ;
            if(ACA.preAlloc[t].isTail)
                ret.mat[i][t + ACA.AllocCnt] ++;
            else
                ret.mat[i][t]++, ret.mat[i + ACA.AllocCnt][t + ACA.AllocCnt]++;
        }
    return ret;
}

char op[10];
int N, L;
int main()
{
    while(cin >> N >> L)
    {
        int ans(1), base(4), exp(L);
        Main.clear();

        for(int i = 1; i <= N; i++)
            cin >> op, Main.insert(op);
        Main.initFail();
        
        Matrix m = constructMat(Main);
        m = m ^ L ;
        
        while(exp)
        {
            if(exp & 1)
                ans = ans * base % MOD;
            base = base * base % MOD;
            exp >>= 1;
        }

        for(int i = 1; i <= m.Len; i++)
            ans -= m.mat[1][i], ans = (ans + MOD) % MOD ;
        cout << ans << endl ;
    }
    return 0;
}

