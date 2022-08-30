#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long i64;
const int MAXN = 1000000;
const int BUFFERSIZE = 1024;

#ifdef UNIX
#define TI64 "%lld %lld %lld"
#define I64 "%lld"
#else
#define TI64 "%I64d %I64d %I64d"
#define I64 "%I64d"
#endif // UNIX

i64 Z[MAXN], Y[MAXN], X[MAXN];  // 公差Z 末项Y 首项X
//i64 item[MAXN];                 // 项数
int n;

int getInput(void);
i64 BinarySearch();
i64 countItem(i64);


int main()
{
    //freopen("Test.txt", "r", stdin);
    while(getInput())
    {
        i64 lastbit = 0;
        for(int i = 0; i < n; i++)
            lastbit = lastbit ^ ((Y[i]-X[i]) / Z[i] + 1);

        if(!(lastbit & 1))
            printf("no corruption\n");
        else
            BinarySearch();
    }

    return 0;
}

int getInput(void)
{
    char buffer[BUFFERSIZE];
    n = 0; bool inflag = 0;

    while(inflag = (fgets(buffer, BUFFERSIZE, stdin) != NULL))
    {
        if(strlen(buffer) <= 2)
            break;
        sscanf(buffer, TI64, &X[n], &Y[n], &Z[n]);
        n++;
    }

    return n || inflag ;
}

i64 BinarySearch()
{
    i64 lb = 0, rb = 0xffffffffLL;

    while(lb+1 < rb)
    {
        int mid = (lb+rb) >> 1;

        if(countItem(mid) & 1)
            rb = mid;
        else
            lb = mid;
    }

    printf(I64, rb);
    printf(" ");
    printf(I64, countItem(rb)-countItem(rb-1));
    puts("");

    return lb;
}

i64 countItem(i64 limit)
{
    i64 sum = 0;
    for(int i = 0; i < n; i++)
    {
        if(X[i] > limit)
            continue;
        sum += ((min(limit, Y[i]) - X[i]) / Z[i]) + 1;
    }
    return sum;
}
