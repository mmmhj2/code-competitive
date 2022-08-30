#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <queue>
#include <ctime>
using namespace std;

namespace AhoCorasickAutomata
{
static const int CHARSET_SIZE = 70;
static const int PREALLOCATE_SIZE = 2500000 + 10;

int child[PREALLOCATE_SIZE][CHARSET_SIZE];
int fail[PREALLOCATE_SIZE];
int inCnt[PREALLOCATE_SIZE];
int allocCnt;

inline int getID(char c)
{
    if('a' <= c && c <= 'z')
        return c - 'a';
    if('A' <= c && c <= 'Z')
        return c - 'A' + 26;
    if('0' <= c && c <= '9')
        return c - '0' + 52;
    return 62;          // -
}

int insert(const char * s)
{
    int len = strlen(s);
    int cur = 0;
    for(int i = 0; i < len; i++)
    {
        int id = getID(s[i]);
        if(child[cur][id] == -1)
        {
            child[cur][id] = allocCnt++;
            memset(child[allocCnt], 0xFF, (sizeof (int)) * CHARSET_SIZE);
        }
        cur = child[cur][id];
    }
    return cur;
}

void constructAutomata()
{
    queue <int> Q;
    fail[0] = 0, inCnt[0] = 1;
    for(int i = 0; i < CHARSET_SIZE; i++)
    {
        if(child[0][i] != -1)
            fail[child[0][i]] = 0, inCnt[0]++;
        else
            child[0][i] = 0;
    }

    for(int i = 0; i < CHARSET_SIZE; i++)
        if(child[0][i] > 0)
            Q.push(child[0][i]);

    while(!Q.empty())
    {
        int cur = Q.front();
        Q.pop();
        for(int i = 0; i < CHARSET_SIZE; i++)
        {
            if(child[cur][i] > 0)
            {
                fail[child[cur][i]] = child[fail[cur]][i];
                inCnt[child[fail[cur]][i]] ++ ;
                Q.push(child[cur][i]);
            }
            else
                child[cur][i] = child[fail[cur]][i];
        }
    }
}
};
char txt[50005];
int ans[AhoCorasickAutomata::PREALLOCATE_SIZE];
int trace[505];

void getAns()
{
    using namespace AhoCorasickAutomata;
    queue <int> Q;
    for(int i = 0; i <= allocCnt; i++)
        if(inCnt[i] <= 0)
            Q.push(i);

    while(!Q.empty())
    {
        int cur = Q.front();
        Q.pop();

        if(cur <= 0)
            break;

        inCnt[fail[cur]] --;
        ans[fail[cur]] += ans[cur];
        if(inCnt[fail[cur]] == 0)
            Q.push(fail[cur]);

    }
}

int main()
{
    memset(AhoCorasickAutomata::child, 0xFF, sizeof AhoCorasickAutomata::child);
    AhoCorasickAutomata::allocCnt = 1;

    int M, N;
    cin >> N ;

    for(int i = 1; i <= N; i++)
    {
        cin >> txt;
        trace[i] = AhoCorasickAutomata::insert(txt);
    }
    AhoCorasickAutomata::constructAutomata();

    cin >> M ;

    for(int i = 1; i <= M; i++)
    {
        cin >> txt ;
        int len = strlen(txt);
        int pos = 0;
        for(int l = 0; l < len; l++)
            pos = AhoCorasickAutomata::child[pos][AhoCorasickAutomata::getID(txt[l])],
            ans[pos]++;
    }

    getAns();

    for(int i = 1; i <= N; i++)
        cout << ans[trace[i]] << endl ;

    return 0;
}

