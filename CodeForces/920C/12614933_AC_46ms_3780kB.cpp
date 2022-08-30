#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

const int MAXN = 200000;

int num[MAXN+5], n;
int index[MAXN+5];
char str[MAXN+5];

int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &num[i]);
        index[i] = i;
    }
    scanf("\n%s", str);
    for(int i = 1; i <= n; i++)
        if(str[i-1]-'0')
            index[i+1] = index[i];
    for(int i = 1; i <= n; i++)
        if(index[num[i]] != index[i])
        {
            printf("NO\n");
            return 0;
        }
    printf("YES\n");
    return 0;
}
