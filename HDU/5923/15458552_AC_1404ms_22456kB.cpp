#include <cmath>
#include <cstring>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <string>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <ctime>
#include <cstdlib>
#include <iostream>
#define pi 3.1415926
#define mod 1000000007
#define MAXM 10010
#define MAXN 510
#define INF 0x3f3f3f3f3f3f3fLL
using namespace std;

struct edge{
	int v,next;
}e[MAXM];
int head[MAXM];
int tot=0;

void add(int u,int v){
	e[tot].v=v;
	e[tot].next=head[u];
	head[u]=tot++;
}

struct node{
	int u,v;
};

std::vector<node> G;

int f[MAXM][MAXN];
void init(int m,int n){
	for(int i=0;i<=m;i++){
		for(int j=0;j<=n;j++){
			f[i][j]=j;
		}
	}
}
int find(int m,int x){
	if(f[m][x]==x)
		return x;
	else
		return f[m][x]=find(m,f[m][x]);
}
void unite(int m,int x,int y){
	x=find(m,x);
	y=find(m,y);
	if(x==y)
		return;
	else
		f[m][y]=x;
}

void dfs(int x){
  	for(int k=head[x];k!=-1;k=e[k].next){
 		int v=e[k].v;
		memcpy(f[v],f[x],sizeof(f[v]));
		unite(v,G[v-1].u,G[v-1].v);
		//if(x!=0)
          //  unite(v,G[x-1].u,G[v-1].u);
		dfs(v);
	}
}

int res[MAXM];
int vis[MAXN];
int main()
{
	int t;
	scanf("%d",&t);
	for(int cas=1;cas<=t;cas++){
		printf("Case #%d:\n",cas);
		int n,m;
		scanf("%d%d",&n,&m);
		init(m,n);
		tot=0;
		G.clear();
		memset(head,-1,sizeof(head));
		add(0,1);
		for(int i=2;i<=m;i++){
			int x;
			scanf("%d",&x);
			add(x,i);
		}
		for(int i=0;i<m;i++){
			int u,v;
			scanf("%d%d",&u,&v);
			node temp;
			temp.u=u,temp.v=v;
			G.push_back(temp);
		}
		dfs(0);
		int q;
		scanf("%d",&q);
		while(q--){
			int cnt;
			memset(vis,0,sizeof(vis));
			scanf("%d",&cnt);
			for(int i=0;i<=n;i++){
				f[m+1][i]=i;
			}
			for(int i=0;i<cnt;i++){
				scanf("%d",&res[i]);
			}
			memcpy(f[m+1],f[res[0]],sizeof(f[m+1]));
			for(int i=1;i<cnt;i++){
                for(int j=1;j<=n;j++){
				int r=find(res[i],j);
				unite(m+1,r,j);
				}
				//unite(m+1,G[res[0]-1].u,G[res[i]-1].u);
			}
			int ans=0;
			for(int i=1;i<=n;i++){
 				int temp=find(m+1,i);
				//cout<<temp<<endl;
				if(!vis[temp]){
                    	vis[temp]=1;
				ans++;
				}
			}
			printf("%d\n",ans);
		}
	}
}
