#include <iostream>
#include <iterator>
#include <cstdio>
#include <string>
#include <vector>
#include <queue>
#include <set>
#define NO_SOL_OUTPUT "This puzzle is not solvable."
using namespace std;

set <string> vist;

int GOAL[20][2];        // The positions of corresponding numbers in goal state
const int MOVEX[4] = {0, 0, 1, -1};
const int MOVEY[4] = {1, -1, 0, 0};

inline int myabs(int a)
{
    return (a < 0 ? -a : a);
}

inline int ManhaDist(int x1, int y1, int x2, int y2)
{
    return myabs(x1 - x2) + myabs(y1 - y2);
}

struct state
{
    int h, step, x, y;
    int board[4][4];
    string mov;

    bool operator < (const state & rhs) const
    {
        return h + step > rhs.h + step;
    }


};

int getH(int b[][4])
{
    int sum = 0 ;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
        {
            if(b[i][j] == 0 || (i == GOAL[b[i][j]][0] && j == GOAL[b[i][j]][1]))
                continue;
            sum += ManhaDist(i, j, GOAL[b[i][j]][0], GOAL[b[i][j]][1]);
        }
    return sum * 4;
}

bool DeterSol(int b[][4])
{
    int tmp = 0, x;//, y;
    int expand[20], invcnt = 0;

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
        {
            expand[tmp++] = b[i][j];
            if(b[i][j] == 0)
                x = i;//, y = j;
        }
    for(int i = 0; i < 16; i++)
        for(int j = i+1; j < 16; j++)
            if(expand[i] > expand[j] && expand[j] != 0)
                invcnt++;
    if(!((invcnt + x) & 1))
        return false;
    return true;
}

bool tryinsert(const state & st)
{
    string tmp;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            tmp.push_back((char)(st.board[i][j] + '0'));
    if(vist.count(tmp))
        return false;
    return true;
}

bool Astar(const state & StartState)
{
    vist.clear();
    priority_queue <state> pq;
    pq.push(StartState);
    state cur, neostate;
    int x, y;
    while(!pq.empty())
    {
        cur = pq.top();
        pq.pop();
        /*
        #ifndef ONLINE_JUDGE
        //copy(&cur.board[0][0], &cur.board[3][3], ostream_iterator<int>(cout, " "));
        //cout << endl ;
        cout << cur.mov << " " << cur.h << " " << cur.step << endl ;
        #endif // ONLINE_JUDGE
        */
        /*
        if(cur.h == 0)
        {
            cout << cur.mov << endl ;
            return true;
        }
        */

        for(int i = 0; i < 4; i++)
        {
            x = cur.x + MOVEX[i], y = cur.y + MOVEY[i];
            if(x < 0 || y < 0 || x >= 4 || y >= 4)
                continue;

            neostate = cur;
            swap(neostate.board[x][y], neostate.board[cur.x][cur.y]);
            neostate.step++;
            if(neostate.step > 50)
                continue;

            switch(i)
            {
            case 0:
                neostate.mov.push_back('R');
                //neostate.mov.push_back('L');
                break;
            case 1:
                neostate.mov.push_back('L');
                //neostate.mov.push_back('R');
                break;
            case 2:
                neostate.mov.push_back('D');
                //neostate.mov.push_back('U');
                break;
            case 3:
                neostate.mov.push_back('U');
                //neostate.mov.push_back('D');
                break;
            }

            if(neostate.mov.size() >= 2)
            {
                int b1 = neostate.mov.size() - 1;
                int b2 = neostate.mov.size() - 2;
                if((neostate.mov[b1] == 'U' && neostate.mov[b2] == 'D')
                        || (neostate.mov[b1] == 'D' && neostate.mov[b2] == 'U')
                        || (neostate.mov[b1] == 'R' && neostate.mov[b2] == 'L')
                        || (neostate.mov[b1] == 'L' && neostate.mov[b2] == 'R')
                  )
                    continue;
            }

            neostate.h = getH(neostate.board);
            neostate.x = x, neostate.y = y;
            if(neostate.h == 0)
            {
                printf("%s\n", neostate.mov.data());
                return true;
            }
            if(tryinsert(neostate))
                pq.push(neostate);
        }
    }
    return false;
}

int main()
{

    int kase, n = 1;

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            GOAL[n][0] = i, GOAL[n++][1] = j;

    cin >> kase ;
    while(kase--)
    {
        state start;
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
            {
                //cin >> start.board[i][j];
                scanf("%d", &start.board[i][j]);
                if(start.board[i][j] == 0)
                    start.x = i, start.y = j;
            }

        if(!DeterSol(start.board))
        {
            //cout << NO_SOL_OUTPUT << endl ;
            puts(NO_SOL_OUTPUT);
            continue;
        }
        //start.h = state::getH(start.board);
        start.step = 0, start.h = 0;
        bool sol = Astar(start);
        if(!sol)
            //cout << NO_SOL_OUTPUT << endl ;
            puts(NO_SOL_OUTPUT);
    }
    return 0;
}
