#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 100000;

int n, m, useless;
int pos[MAXN+50];
int sum[MAXN+50];
int val[MAXN+50];

int main()
{
    while(scanf("%d%d", &m, &n) != EOF)
    {
        memset(pos, 0xFF, sizeof pos);
        memset(sum, 0x00, sizeof sum);
        memset(val, 0x00, sizeof val);
        if((!n) && (!m))
            break;
        pos[0] = 0;
        for(int i = 1; i <= n; i++)
        {
            scanf("%d", &val[i]);
            sum[i] = sum[i-1] + val[i];
            sum[i] %= m ;
            if(pos[sum[i]] >= 0)
            {
                for(int k = pos[sum[i]] + 1; k <= i; k++)
                    if(k == pos[sum[i]] + 1)
                        printf("%d", k);
                    else
                        printf(" %d", k);
                printf("\n");
                for(int k = i + 1; k <= n; k++)
                    scanf("%d", &useless);
                break;
            }
            pos[sum[i]] = i;
        }

    }
    return 0;
}