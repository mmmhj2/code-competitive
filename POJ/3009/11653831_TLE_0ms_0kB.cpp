#include <iostream>
#include <queue>
#include <cstring>

#define UP 0x01
#define DOWN    0x02
#define LEFT    0x04
#define RIGHT   0x08

using namespace std;

struct node
{
    char bd[21][21];
    int x, y;
    int depth;

    node()
    {
        x = 0, y = 0, depth = 0;
    };
}org;
int W, H;
int stx, sty, glx, gly;

int CheckThr(const node & n)
{
    const short &x = n.x, &y = n.y;
    int ret = 0;
	if(x-1 >= 0)
		if(n.bd[x-1][y] != '1')
			ret+=UP;
	if(x+1 <= H)
		if(n.bd[x+1][y] != '1')
			ret+=DOWN;
	if(y-1 >= 0)
		if(n.bd[x][y-1] != '1')
			ret+=LEFT;
	if(y+1 <= W)
		if(n.bd[x][y+1] != '1')
			ret+=RIGHT;
	return ret;
}

int BFS(node);


int main()
{
    while(true)
    {
        memset(&org, 0x00, sizeof(org));
        cin >> W >> H;
        if(!W || !H)
            break;
        for(int i = 1; i <= H; i++)
        {
            for(int j = 1; j <= W; j++)
            {
                cin >> org.bd[i][j];
                if(org.bd[i][j] == '2')
                    org.x = i, org.y = j;
                if(org.bd[i][j] == '3')
                    glx = i, gly = j;
            }
        }
        cout << BFS(org) << endl;

    }
    return 0;
}

int BFS(node org)
{
    queue <node> q;
    q.push(org);

    while(!q.empty())
    {
        node neo = q.front();
        q.pop();
        neo.depth++;
        if(neo.depth > 10)
            continue;

        if(neo.x == glx && neo.y == gly)
            return neo.depth;

        int dir = CheckThr(neo);

        if(dir & UP)
        {
            for(int i = neo.x; i > 0; i--)
            {
                if(neo.bd[i][neo.y] == '1')
                {
                    neo.bd[i][neo.y] = '0';
                    int t = neo.x;
                    neo.x = i+1;
                    q.push(neo);
                    neo.bd[i][neo.y] = '1';
                    neo.x = t;
                    break;
                }
                if(neo.bd[i][neo.y] == '3')
                    return neo.depth;
            }
        }
        if(dir & DOWN)
        {
            for(int i = neo.x; i <= H; i++)
            {
                if(neo.bd[i][neo.y] == '1')
                {
                    neo.bd[i][neo.y] = '0';
                    int t = neo.x;
                    neo.x = i-1;
                    q.push(neo);
                    neo.bd[i][neo.y] = '1';
                    neo.x = t;
                    break;
                }
                if(neo.bd[i][neo.y] == '3')
                    return neo.depth;
            }
        }
        if(dir & LEFT)
        {
            for(int i = neo.y; i > 0; i--)
            {
                if(neo.bd[neo.x][i] == '1')
                {
                    neo.bd[neo.x][i] = '0';
                    int t = neo.y;
                    neo.y = i+1;
                    q.push(neo);
                    neo.bd[neo.x][i] = '1';
                    neo.y = t;
                    break;
                }
                if(neo.bd[neo.x][i] == '3')
                    return neo.depth;
            }
        }
        if(dir & RIGHT)
        {
            for(int i = neo.y; i <= W; i++)
            {
                if(neo.bd[neo.x][i] == '1')
                {
                    neo.bd[neo.x][i] = '0';
                    int t = neo.y;
                    neo.y = i-1;
                    q.push(neo);
                    neo.bd[neo.x][i] = '1';
                    neo.y = t;
                    break;
                }
                if(neo.bd[neo.x][i] == '3')
                    return neo.depth;
            }
        }
    }
    return -1;
}
