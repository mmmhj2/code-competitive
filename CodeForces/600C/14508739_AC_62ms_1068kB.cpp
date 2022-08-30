#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef string::iterator stritr;
string str;

int charCnt[30];
int changeCnt;
int changeLst[30];

int main()
{
    cin >> str;

    for(stritr i = str.begin(); i != str.end(); i++)
        charCnt[*i - 'a']++;
    for(int i = 0; i < 30; i++)
        if(charCnt[i] & 1)
            changeCnt++,
            changeLst[changeCnt] = i;

    for(int i = 1; i <= changeCnt/2; i++)
    {
        charCnt[changeLst[i]]++;
        charCnt[changeLst[changeCnt-i+1]]--;
    }

    string tmpStr, ansStr;
    int centre = -1;

    for(int i = 0; i < 26; i++)
        if(charCnt[i] & 1)
        {
            centre = i;
            for(int j = 0; j < (charCnt[i]-1)/2; j++)
                tmpStr.push_back('a' + i);
        }

        else
            for(int j = 0; j < charCnt[i] / 2; j++)
                tmpStr.push_back('a' + i);
    ansStr.append(tmpStr);

    if(centre >= 0)
        ansStr.push_back('a' + centre);

    reverse(tmpStr.begin(), tmpStr.end());
    ansStr.append(tmpStr);

    cout << ansStr << endl;
    return 0;
}


/*
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <stack>
#include <map>
#include <vector>
#define INF 0x3f3f3f
#define eps 1e-8
#define MAXN (200000+10)
#define MAXM (100000)
#define Ri(a) scanf("%d", &a)
#define Rl(a) scanf("%lld", &a)
#define Rf(a) scanf("%lf", &a)
#define Rs(a) scanf("%s", a)
#define Pi(a) printf("%d\n", (a))
#define Pf(a) printf("%.2lf\n", (a))
#define Pl(a) printf("%lld\n", (a))
#define Ps(a) printf("%s\n", (a))
#define W(a) while(a--)
#define CLR(a, b) memset(a, (b), sizeof(a))
#define MOD 1000000007
#define LL long long
#define lson o<<1, l, mid
#define rson o<<1|1, mid+1, r
#define ll o<<1
#define rr o<<1|1
using namespace std;
char str[MAXN]; int num[30];
bool mark[30];
int main()
{
    Rs(str); CLR(num, 0);
    int len = strlen(str);
    for(int i = 0; i < len; i++)
        num[str[i]-'a']++;
    CLR(mark, false); int cnt = 0;
    for(int i = 0; i < 26; i++)
        if(num[i] & 1)
            mark[i] = true, cnt++;
    char mid; int use = 0;
    if(len & 1)
    {
        cnt--;
        for(int i = 0; i <= 25; i++)
        {
            if(mark[i])
                use++;
            if(use > cnt / 2)
            {
                mid = 'a' + i;
                mark[i] = false;
                break;
            }
        }
    }
    bool flag = false; use = 0;
    for(int i = 0; i <= 25; i++)
    {
        if(mark[i])
        {
            if(flag)
                num[i]--;
            else
                num[i]++;
            use++;
        }
        if(use == cnt / 2)
            flag = true;
    }
    int F = 0, B = len-1;
    for(int i = 0; i < 26; i++)
    {
        for(int j = F; j < F + num[i] / 2; j++)
            str[j] = 'a' + i;
        F += num[i] / 2;
        for(int j = B; j > B - num[i] / 2; j--)
            str[j] = 'a' + i;
        B -= num[i] / 2;
    }
    if(len & 1)
        str[len / 2] = mid;
    Ps(str);
    return 0;
}
*/
