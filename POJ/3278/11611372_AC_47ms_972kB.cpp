#include <iostream>
#include <queue>
#include <cstring>
#include <cassert>
using namespace std;

struct step
{
    int pos, st;
    step(int p, int s):pos(p), st(s){};
    step(){};
};

const int MAXN = 100000;

bool vis[MAXN+10];

int BFS(int sp, int ep)
{
    memset(vis, 0x00, sizeof(vis));

    queue<step>q;
    q.push(step(sp, 0));

    while(!q.empty())
    {
        step cur = q.front(); q.pop();
        if(cur.pos == ep)
        {
            return cur.st;
        }

        //assert(cur.pos >= 0);

        if(cur.pos-1 >= 0 && !vis[cur.pos-1])
        {
            vis[cur.pos-1] = true;
            q.push(step(cur.pos-1, cur.st+1));
        }
        if(cur.pos+1 <= MAXN && !vis[cur.pos+1])
        {
            vis[cur.pos+1] = true;
            q.push(step(cur.pos+1, cur.st+1));
        }
        if(cur.pos*2 <= MAXN && !vis[cur.pos*2])
        {
            vis[cur.pos*2] = true;
            q.push(step(cur.pos*2, cur.st+1));
        }

    }
    return -1;
}

int main()
{
    int n, k;
    cin >> n >> k;
    cout << BFS(n, k) << endl;
    return 0;
}
/*
#include<queue>
#include<iostream>
#define MAXN 100000
using namespace std;
struct node{
	int add, tim;
	node(int x, int y): add(x), tim(y) {}
};
queue<node>que;
bool vis[MAXN+5];
int main(){
	int n, k;
	cin>>n>>k;
	que.push(node(n, 0));
	while(!que.empty()){
		node now = que.front();
		que.pop();
		if(now.add == k){
			cout<<now.tim;
			return 0;
		}
		if(now.add > -1 && vis[now.add-1] == false)
		{
			que.push(node(now.add-1, now.tim+1));
			vis[now.add-1] = true;
		}
		if(now.add < k && vis[now.add+1] == false){
			que.push(node(now.add+1, now.tim+1));
			vis[now.add+1] = true;
		}
		if(now.add < k && vis[now.add*2] == false){
			que.push(node(now.add*2, now.tim+1));
			vis[now.add*2] = true;
		}
	}
}
*/
