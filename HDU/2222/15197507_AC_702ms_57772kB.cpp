/*
hdu2222 AC自动机模板题
date:2013.2.26
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cassert>
#include<queue>

using namespace std;
#define  SETSIZE 26         //字符集大小
#define  MAXNODE 201000     //Trie的结点数
#define  MAXLEN  1010000    //文本串长度
#define  KEYLEN  55         //模式串长度

struct node {
    int cnt;                //模式串标志及计数器
    node *next[SETSIZE];     //下一个结点指针
    node *fail;              //失配指针
    node() {
        cnt = 0;
        fail = NULL;
        memset(next, 0, sizeof(next));
    }
};
node* Root;                   //Trie的根结点指针
int Ans;                      //匹配的模式串总数
char Str[MAXLEN];             //文本串

void Insert(char *s, node *rt)        //Trie中插入模式串s
{
    int i, j, n = strlen(s);
    node *p = rt, *q;
    for(i = 0; i < n; i++)
    {
        j = s[i] - 'a';
        assert(p != NULL);
        q = p->next[j];
        if(!q)                      //结点不存在
        {
            q = new node;           //新建结点
            p->next[j] = q;         //连接到p之下
        }
        p = q;                      //往下走
    }
    p->cnt++;                       //模式串计数加1
}
void Read()
{
    int i, n;
    char s[KEYLEN];
    scanf("%d\n", &n);
    Root = new node;                //生成虚的根结点
    for(i = 0; i < n; i++)
    {
        gets(s);                    //读入模式串
        Insert(s, Root);            //插入Trie
    }
    gets(Str);                      //读入文本串
}
char Key[KEYLEN];
void Print(node *rt, int dep)                //输出Trie中的模式串
{
    int i;
    if(!rt)
        return;
    if(rt->cnt)
    {
        for(i = 0; i < dep; i++)
            printf("%c", Key[i]);
        printf("\n");
    }
    for(i = 0; i < SETSIZE; i++)
        if(rt->next[i])
        {
            Key[dep] = 'a' + i;
            Print(rt->next[i], dep+1);
        }
}
void ACBuild(node *rt)              //建立fail指针
{
    queue<node *>q;
    node *p, *bef;
    int i;
    for(i = 0; i < SETSIZE; i++)
        if(rt->next[i])
        {
            rt->next[i]->fail = rt;
            q.push(rt->next[i]);       //第1层结点的指针入队
        }
    while(!q.empty())
    {
        p = q.front();  q.pop();
        for(i = 0; i < SETSIZE; i++)
            if(p->next[i])
            {
                for(bef = p->fail; bef; bef = bef->fail)  //父结点的fail所指结点
                {
                    if(bef->next[i])        //如果该结点有儿子'i'
                    {
                        p->next[i]->fail = bef->next[i];
                        break;              //找到fail所指结点，跳出
                    }
                }
                if(!bef)            //如果一开始为空，则指向根
                    p->next[i]->fail = rt;
                q.push(p->next[i]);
            }
    }
}
void ACFind(char *s, node *rt)  //在文本串s中进行多模式串匹配
{
    int i, j, n = strlen(s);
    node *p = rt, *q;
    for(i = 0; i < n; i++)
    {
        j = s[i] - 'a';
        while(!p->next[j] && p!=rt)
            p = p->fail;
        p = p->next[j];
        if(!p)
            p = rt;
        for(q = p; q != rt; q = q->fail)
        {
            Ans += q->cnt;
            q->cnt = 0;             //题目要求模式串不重复匹配
        }
    }
}


int main()
{
    int t;
    scanf("%d\n", &t);
    while(t-->0)
    {
        Ans = 0;
        Read();
        ACBuild(Root);
        ACFind(Str, Root);
        printf("%d\n", Ans);
    }
    return 0;
}
