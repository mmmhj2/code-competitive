#include <algorithm>
#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

namespace TemplateNamespace
{

class OptmizedReading
{
    static const int BUF_LEN = 100000000 + 10;
    int errflag;
    char pBuffer[BUF_LEN];
    char * pRead;

    void setEofRead()
    {
        errflag = EOF;
        if(pRead == pBuffer + BUF_LEN)
            resetFlow();
    }

    void resetFlow()
    {
        int len = fread(pBuffer, 1, BUF_LEN - 1, stdin);
        pBuffer[len] = '\0';        // Append null character
        if(len != BUF_LEN - 1)
            errflag = EOF;

        pRead = pBuffer;
    }

public:
    void flush()
    {
        errflag = 0;
    }

    int getError()
    {
        return errflag;
    }

    void ReadOptmized()
    {
        resetFlow();
    }

    int ReadUnInt()
    {
        int ret = 0;

        while(*pRead < '0' || *pRead > '9')
        {
            if(*pRead == '\0')
            {
                setEofRead();
                return 0;
            }

            *pRead = '\0';
            pRead++;
        }

        while(*pRead >= '0' && *pRead <= '9')
            ret = ret * 10 + (*pRead - '0'), *pRead = '\0',	pRead++;
        return ret;
    }

    int readChar()
    {
        char ch = *pRead;
        if(ch == '\0')
        {
            setEofRead();
            return EOF;
        }
        pRead++;
        return ch;
    }
} Opt;

}
using TemplateNamespace::Opt;
const int MAXK = 10, MAXN = 1e5 + 10;
pair <int, int> a[MAXK][MAXN];
int b[MAXK][MAXN];
int v[MAXK], cnt[MAXN];
int pointer[MAXK];
int T, N, K;

int main()
{
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    #endif // ONLINE_JUDGE

    Opt.ReadOptmized();
    T = Opt.ReadUnInt();

    while(T--)
    {
        N = Opt.ReadUnInt(), K = Opt.ReadUnInt();

        for(int i = 1; i <= K; i++)
            v[i] = Opt.ReadUnInt(), pointer[i] = 0;

        for(int i = 1; i <= N; i++)
        {
            for(int j = 1; j <= K; j++)
            {
                a[j][i].first = Opt.ReadUnInt();
                a[j][i].second = i;
            }
            for(int j = 1; j <= K; j++)
                b[j][i] = Opt.ReadUnInt();
            cnt[i] = 0;
        }

        int ans = 0;
        for(int i = 1; i <= K; i++)
            sort(a[i] + 1, a[i] + N + 1);

        while(true)
        {
            int orgAns = ans ;
            for(int i = 1; i <= K; i++)
                while(a[i][pointer[i] + 1].first <= v[i] && pointer[i] < N)
                {
                    //cerr << "Hit" << endl ;
                    int x = a[i][++pointer[i]].second;
                    cnt[x] ++ ;
                    if(cnt[x] >= K)
                    {
                        //cerr << "Killed" << endl ;
                        ans++;
                        for(int j = 1; j <= K; j++)
                            v[j] += b[j][x];
                    }
                }
            //cerr << ans << " " << orgAns << endl ;
            if(ans == orgAns)
                break;
        }
        printf("%d\n", ans);
        for(int i = 1; i <= K; i++)
            printf("%d%c", v[i], " \n"[i == K]);

    }

    return 0;
}
