#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int f[11111];
struct node
{
	int p,d;
}a[11111];
int find(int x)
{
	if (f[x]==-1)
		return x;
	else
	{
		f[x]=find(f[x]);
		return f[x];
	}
}
bool cmp(node a,node b)
{
	return a.p>b.p;
}
int main()
{
	int u;
	int ans;
	while (~scanf ("%d",&u))
	{
		for (int i=0;i<u;i++)
			scanf ("%d %d",&a[i].p,&a[i].d);
		memset (f,-1,sizeof(f));
		sort(a,a+u,cmp);
		ans=0;
		for (int i=0;i<u;i++)
		{
			int t;
			t=find(a[i].d);	
			if (t>0)
			{
				ans+=a[i].p;
				f[t]=t-1;		
			}
		}
		printf ("%d\n",ans);
	}
	return 0;
}