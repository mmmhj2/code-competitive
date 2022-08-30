#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

const int MAXN = 200000;

int num[MAXN+5], n;
bool swapable[MAXN+5];
int fastjudge = 1;
char str[MAXN+5];

int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d", &num[i]);
    scanf("\n%s", str);
    for(int i = 0; i < n; i++)
    {
        swapable[i+1] = str[i]-'0';
        if(!swapable[i+1] && num[i+2] != 0)
            if(num[i+2] < num[i+1])
                fastjudge = 0;
    }

    if(fastjudge == 0)
    {
        printf("NO\n");
    }
    else
    {
        printf("YES\n");
    }
/*
    for(int i = 1; i <= n; i++)
    {
        int curpos = i, tarpos = num[i];
        for(int i = curpos; i < tarpos; i++)
        {
            if(!swapable[i])
            {
                printf("NO\n");
                return 0;
            }
            swap(num[i], num[i+1]);
        }

    }
    printf("YES\n");
    return 0;*/
}
