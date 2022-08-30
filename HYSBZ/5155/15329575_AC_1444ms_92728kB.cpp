#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define pa pair<int,int>
const int Maxq=100010;
const int inf=2147483647;
int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    return x*f;
}
map<int,int>mp;
int lc[Maxq*33],rc[Maxq*33],pos[Maxq*33],ll[Maxq*33],rr[Maxq*33],len[Maxq*33],c[Maxq*33];
int n,q,tot=0,root=0;
int get(int l,int r)
{
    return (l+r)/2+((r-l)&1);
}
void up(int x,int l,int r)
{
    int mid=l+r>>1;
    int lcl=ll[lc[x]],lcr=rr[lc[x]],lclen=len[lc[x]],lcp=pos[lc[x]];
    int rcl=ll[rc[x]],rcr=rr[rc[x]],rclen=len[rc[x]],rcp=pos[rc[x]];
    if(!lc[x])lcl=lcr=lclen=mid-l+1,lcp=get(l,mid);
    if(!rc[x])rcl=rcr=rclen=r-mid,rcp=get(mid+1,r);
    c[x]=c[lc[x]]+c[rc[x]];
    len[x]=max(lcr+rcl,max(lclen,rclen));
    if(len[x]==rclen)pos[x]=rcp;
    else if(len[x]==lcr+rcl)pos[x]=get(mid-lcr+1,mid+rcl);
    else pos[x]=lcp;
    if(lcl==mid-l+1)ll[x]=lcl+rcl;
    else ll[x]=lcl;
    if(rcr==r-mid)rr[x]=rcr+lcr;
    else rr[x]=rcr;
}
void modify(int &x,int l,int r,int p,int v)
{
    if(!x)x=++tot;
    if(l==r)
    {
        if(v)pos[x]=-1;
        else pos[x]=l;
        ll[x]=rr[x]=len[x]=1-v,c[x]=v;
        return;
    }
    int mid=l+r>>1;
    if(p<=mid)modify(lc[x],l,mid,p,v);
    else modify(rc[x],mid+1,r,p,v);
    up(x,l,r);
}
int query(int x,int l,int r,int fl,int fr)
{
    if(!x)return 0;
    if(l==fl&&r==fr)return c[x];
    int mid=l+r>>1;
    if(fr<=mid)return query(lc[x],l,mid,fl,fr);
    else if(fl>mid)return query(rc[x],mid+1,r,fl,fr);
    else return query(lc[x],l,mid,fl,mid)+query(rc[x],mid+1,r,mid+1,fr);
}
int main()
{
    //freopen("data.in", "r", stdin);
    //freopen("data.out", "w", stdout);

    n=read(),q=read();
    bool fir=true;
    while(q--)
    {
        int x=read();
        if(!x)
        {
            int l=read(),r=read();
            printf("%d\n",query(root,1,n,l,r));
        }
        else
        {
            if(!mp[x])
            {
                int p;
                if(fir)p=get(1,n),fir=false;
                else p=pos[root];
                modify(root,1,n,p,1);
                mp[x]=p;
            }
            else
            {
                modify(root,1,n,mp[x],0);
                mp[x]=0;
            }
        }
    }
}
