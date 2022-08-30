#include <algorithm>
#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

struct _QueueNode
{
    int stp;
    int gp1, gp2, gp3;

    //_QueueNode(){};
    _QueueNode(int st = 0, int g1 = 0, int g2 = 0, int g3 = 0)
    {
        stp = st;
        gp1 = g1;
        gp2 = g2;
        gp3 = g3;
    }

};
const int MAXN = 16;
const int MAXCELL = MAXN*MAXN+5;

bool vistFor[MAXCELL][MAXCELL][MAXCELL];
bool vistRev[MAXCELL][MAXCELL][MAXCELL];
int gps1, gps2, gps3;
int gpt1, gpt2, gpt3;
int w, h, n;
vector <int> Adj[MAXCELL];

bool ForwardBFS(int stp, queue<_QueueNode> &);
bool ReverseBFS(int stp, queue<_QueueNode> &);

inline bool check(int x, int y, int nx, int ny)
{
    if(nx == ny)
        return false;
    if(nx == y && ny == x)
        return false;
    return true;
}

int BFS()
{
    int forStp = 0, revStp = 0;
    memset(vistFor, 0x00, sizeof vistFor);
    memset(vistRev, 0x00, sizeof vistRev);
    queue <_QueueNode> forQue, revQue;

    forQue.push(_QueueNode(0, gps1, gps2, gps3));
    vistFor[gps1][gps2][gps3] = true;

    revQue.push(_QueueNode(0, gpt1, gpt2, gpt3));
    vistRev[gpt1][gpt2][gpt3] = true;

    while((!forQue.empty()) || (!revQue.empty()))
    {
        if(ForwardBFS(forStp, forQue))
            return forStp + revStp;
        else
            forStp++;

        if(ReverseBFS(revStp, revQue))
            return forStp + revStp;
        else
            revStp++;
    }
    return -1;
}

void getInput()
{
    gps1 = gps2 = gps3 = 0;
    gpt1 = gpt2 = gpt3 = 0;
    int tileID[20][20], passcnt = 0;
    memset(tileID, 0x00, sizeof tileID);
    char maze[20][20] = {"\0"};

    //fgets(maze[0], 20, stdin);
    for(int i = 0; i < h; i++)
    {
        fflush(stdin);
        fgets(maze[i], w+1, stdin);
        //printf("%s\n", maze[i]);
    }


    for(int i = 0; i < h; i++)
        for(int j = 0; j < w; j++)
        {
            if(maze[i][j] == '#')
                tileID[i][j] = 0;
            else
            {
                tileID[i][j] = ++passcnt;
                switch(maze[i][j])
                {
                case ' ':
                    break;
                case 'A':
                    gpt1 = tileID[i][j];
                    break;
                case 'B':
                    gpt2 = tileID[i][j];
                    break;
                case 'C':
                    gpt3 = tileID[i][j];
                    break;
                case 'a':
                    gps1 = tileID[i][j];
                    break;
                case 'b':
                    gps2 = tileID[i][j];
                    break;
                case 'c':
                    gps3 = tileID[i][j];
                    break;
                }
            }
        }
    for(int i = 0; i <= passcnt; i++)
        Adj[i].clear();
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            const int curpos = tileID[i][j];
            if(!tileID[i][j])
                continue;
            if(tileID[i+1][j])
                Adj[curpos].push_back(tileID[i+1][j]);
            if(tileID[i][j+1])
                Adj[curpos].push_back(tileID[i][j+1]);
            if(i-1 >= 0 && tileID[i-1][j])
                Adj[curpos].push_back(tileID[i-1][j]);
            if(j-1 >= 0 && tileID[i][j-1])
                Adj[curpos].push_back(tileID[i][j-1]);
        }
    }
    /*
        vector<int>::iterator itr;

        for(int i = 1; i <= w*h; i++)
        {
            cerr << i << ": " ;
            for(itr = Adj[i].begin(); itr != Adj[i].end(); itr++)
                cerr << *itr << " " ;

            cerr << endl ;
        }
    */

}

int main()
{
    //ofstream cout("1.txt");
    //freopen("1.txt", "w", stdout);
    while(1)
    {
        scanf("%d%d%d", &w, &h, &n);
        if((!w) && (!h) && (!n))
            break;
        getInput();
        printf("%d\n", BFS());
    }
    return 0;
}


bool ForwardBFS(int _stp, queue<_QueueNode> & forQue)
{
    _QueueNode curnode;

    while(!forQue.empty())          //<<
    {
        curnode = forQue.front();   //<<
        forQue.pop();
        int stp = curnode.stp, pos1 = curnode.gp1, pos2 = curnode.gp2, pos3 = curnode.gp3;
        if(stp > _stp)           // Expand only once
        {
            //cerr << "Rejected" << endl ;
            //cerr << curnode.stp << " " << stp << endl ;
            break;
        }

        if(vistRev[pos1][pos2][pos3])   //<<
            return true;

        for(int i = 0; i <= Adj[pos1].size(); i++)
        {
            int tp1 = (i == 0 ? pos1 : Adj[pos1][i-1]);
            for(int j = 0; j <= Adj[pos2].size(); j++)
            {
                int tp2 = (j == 0 ? pos2 : Adj[pos2][j-1]);

                if(!check(pos1, pos2, tp1, tp2))
                    continue;

                for(int k = 0; k <= Adj[pos3].size(); k++)
                {
                    int tp3 = (k == 0 ? pos3 : Adj[pos3][k-1]);

                    if((!check(pos1, pos3, tp1, tp3)) || (!check(pos2, pos3, tp2, tp3)))
                        continue;
                    if(!vistFor[tp1][tp2][tp3])         // <
                    {
                        //cerr << "PUSH " << tp1 << " " << tp2 << " " << tp3 << endl ;
                        vistFor[tp1][tp2][tp3] = true;
                        forQue.push(_QueueNode(stp+1, tp1, tp2, tp3));
                    }

                }
            }
        }
    }

    return false;
}

bool ReverseBFS(int _stp, queue<_QueueNode> & revQue)
{
    _QueueNode curnode;

    while(!revQue.empty())          //<<
    {
        curnode = revQue.front();   //<<
        revQue.pop();
        int stp = curnode.stp, pos1 = curnode.gp1, pos2 = curnode.gp2, pos3 = curnode.gp3;
        if(stp > _stp)           // Expand only once
        {
            //cerr << "Rejected" << endl ;
            //cerr << curnode.stp << " " << stp << endl ;
            break;
        }

        if(vistFor[pos1][pos2][pos3])   //<<
            return true;

        for(int i = 0; i <= Adj[pos1].size(); i++)
        {
            int tp1 = (i == 0 ? pos1 : Adj[pos1][i-1]);
            for(int j = 0; j <= Adj[pos2].size(); j++)
            {
                int tp2 = (j == 0 ? pos2 : Adj[pos2][j-1]);
                if(!check(pos1, pos2, tp1, tp2))
                    continue;
                for(int k = 0; k <= Adj[pos3].size(); k++)
                {
                    int tp3 = (k == 0 ? pos3 : Adj[pos3][k-1]);
                    if((!check(pos1, pos3, tp1, tp3)) || (!check(pos2, pos3, tp2, tp3)))
                        continue;
                    if(!vistRev[tp1][tp2][tp3])         // <
                    {
                        //cerr << "PUSH " << tp1 << " " << tp2 << " " << tp3 << endl ;
                        vistRev[tp1][tp2][tp3] = true;
                        revQue.push(_QueueNode(stp+1, tp1, tp2, tp3));
                    }

                }
            }
        }
    }

    return false;
}

