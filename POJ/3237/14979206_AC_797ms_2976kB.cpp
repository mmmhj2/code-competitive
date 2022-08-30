#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int inf=0x3f3f3f3f;
const int maxn=1e5+100;
const int maxm=maxn*2;
struct Edge
{
    int from;
    int to;
    int cost;
}E[maxn];
struct Node
{
    int l;
    int r;
    int maxi;
    int mini;
    int neg;
}t[maxn*4];
int e,head[maxn],pnt[maxm],nxt[maxm],cost[maxm];
int n,pre[maxn],size[maxn],son[maxn],dep[maxn],top[maxn],idx[maxn],pos[maxn],tree_clock;
void AddEdge(int u,int v,int c)
{
    pnt[e]=v;nxt[e]=head[u];cost[e]=c;head[u]=e++;
}
void Init()
{
    e=tree_clock=0;
    memset(head,-1,sizeof(head));
    memset(dep,0,sizeof(dep));
    pre[1]=0;
    size[0]=0;
}
void DFS(int u)
{
    size[u]=1;
    son[u]=0;
    for(int i=head[u];i!=-1;i=nxt[i])
        if(pnt[i]!=pre[u])
        {
            pre[pnt[i]]=u;
            dep[pnt[i]]=dep[u]+1;
            DFS(pnt[i]);
            size[u]+=size[pnt[i]];
            if(size[pnt[i]]>size[son[u]])
                son[u]=pnt[i];
        }
}
void dfs(int u,int top_node)
{
    top[u]=top_node;
    pos[u]=++tree_clock;
    idx[tree_clock]=u;
    if(son[u])
        dfs(son[u],top_node);
    for(int i=head[u];i!=-1;i=nxt[i])
        if(pnt[i]!=pre[u]&&pnt[i]!=son[u])
            dfs(pnt[i],pnt[i]);
}
void Build(int l,int r,int index)
{
    t[index].l=l;
    t[index].r=r;
    t[index].maxi=-inf;
    t[index].mini=inf;
    t[index].neg=0;
    if(l==r)
        return;
    int mid=(l+r)>>1;
    Build(l,mid,index<<1);
    Build(mid+1,r,index<<1|1);
}
void UpdateNode(int index)
{
    swap(t[index].maxi,t[index].mini);
    t[index].maxi*=-1;
    t[index].mini*=-1;
}
void PushDown(int index)
{
    if(t[index].l==t[index].r)
        return;
    if(t[index].neg)
    {
        t[index<<1].neg^=1;
        t[index<<1|1].neg^=1;
        UpdateNode(index<<1);
        UpdateNode(index<<1|1);
        t[index].neg=0;
    }
}
void PushUp(int index)
{
    t[index].maxi=max(t[index<<1].maxi,t[index<<1|1].maxi);
    t[index].mini=min(t[index<<1].mini,t[index<<1|1].mini);
}
void UpdateT(int l,int r,int index,int  val)
{
    PushDown(index);
    if(t[index].l==l&&t[index].r==r)
    {
        if(val==inf)
        {
            t[index].neg=1;
            UpdateNode(index);
        }
        else
            t[index].mini=t[index].maxi=val;
        return;
    }
    int mid=(t[index].l+t[index].r)>>1;
    if(r<=mid)
        UpdateT(l,r,index<<1,val);
    else if(l>mid)
        UpdateT(l,r,index<<1|1,val);
    else
    {
        UpdateT(l,mid,index<<1,val);
        UpdateT(mid+1,r,index<<1|1,val);
    }
    PushUp(index);
}
int QueryT(int l,int r,int index)
{
    PushDown(index);
    if(t[index].l==l&&t[index].r==r)
        return t[index].maxi;
    int mid=(t[index].l+t[index].r)>>1;
    if(r<=mid)
        return QueryT(l,r,index<<1);
    else if(l>mid)
        return QueryT(l,r,index<<1|1);
    else
        return max(QueryT(l,mid,index<<1),QueryT(mid+1,r,index<<1|1));
}
void Update(int x,int y,int v)
{
    while(top[x]!=top[y])
    {
        if(dep[top[x]]<dep[top[y]])
            swap(x,y);
        UpdateT(pos[top[x]],pos[x],1,v);
        x=pre[top[x]];
    }
    if(x==y)
        return;
    if(dep[x]>dep[y])
        swap(x,y);
    UpdateT(pos[son[x]],pos[y],1,v);
}
int Query(int x,int y)
{
    int ans=-inf;
    while(top[x]!=top[y])
    {
        if(dep[top[x]]<dep[top[y]])
            swap(x,y);
        ans=max(ans,QueryT(pos[top[x]],pos[x],1));
        x=pre[top[x]];
    }
    if(x==y)
        return ans;
    if(dep[x]>dep[y])
        swap(x,y);
    ans=max(ans,QueryT(pos[son[x]],pos[y],1));
    return ans==-inf?0:ans;
}
void solve()
{
    DFS(1);
    dfs(1,1);
    Build(1,tree_clock,1);
    for(int i=1;i<n;i++)
    {
        int x=E[i].from;
        int y=E[i].to;
        if(dep[x]>dep[y])
            swap(E[i].from,E[i].to);
        UpdateT(pos[E[i].to],pos[E[i].to],1,E[i].cost);
    }
    while(1)
    {
        char op[20];
        scanf("%s",op);
        if(op[0]=='Q')
        {
            int l,r;
            scanf("%d%d",&l,&r);
            printf("%d\n",Query(l,r));
        }
        else if(op[0]=='C')
        {
            int ind,val;
            scanf("%d%d",&ind,&val);
            UpdateT(pos[E[ind].to],pos[E[ind].to],1,val);
        }
        else if(op[0]=='N')
        {
            int l,r;
            scanf("%d%d",&l,&r);
            Update(l,r,inf);
        }
        else
            break;
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        Init();
        scanf("%d",&n);
        for(int i=1;i<n;i++)
        {
            scanf("%d%d%d",&E[i].from,&E[i].to,&E[i].cost);
            AddEdge(E[i].from,E[i].to,E[i].cost);
            AddEdge(E[i].to,E[i].from,E[i].cost);
        }
        solve();
    }
    return 0;
}
