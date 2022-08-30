#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

/*
Collection #1:
Can't be divided.
*/

const int MAXN = 20000;

int a[MAXN+5];
bool f[MAXN*6+5];

int main(int argc, char ** argv)
{
    int cas = 0;
    while(1)
    {
        cas ++;
        memset(f, 0x00, sizeof f);
        memset(a, 0x00, sizeof a);
        int sum = 0, len = 0;
        for(int i = 1; i <= 6; i++)
        {
            int x, t = 1;
            cin >> x;
            while(2*t-1 < x)
            {
                a[++len] = t * i;
                t *= 2;
            }
            a[++len] = (x - t + 1) * i;
            sum += x*i;
        }

        if(sum <= 0)
            break;

        if(sum % 2 != 0)
        {
            printf("Collection #%d:\nCan't be divided.\n\n", cas);
            continue;
        }

        sum /= 2, f[0] = 1;

        for (int i = 1; i <= len ; i++)
        {
            for(int j = sum; j >= a[i]; j--)
            {
                if(f[j-a[i]] == true)
                    f[j] = true;
            }
        }

        if(f[sum])
        {
            printf("Collection #%d:\nCan be divided.\n\n", cas);
        }else{
            printf("Collection #%d:\nCan't be divided.\n\n", cas);
        }
    }
    return 0;

}

