#include <iostream>
#include <utility>
#include <cstring>
#include <vector>
using namespace std;
const int MAXN = 30;
const char SUCCESS[] = "T-shirts rock!";
const char FAILURE[] = "I\'d rather not wear a shirt anyway...";
const int OFFSET = 25;

int HasShirt[10];
bool vist[MAXN*7];

vector <int> Adj[MAXN*7];
int match[MAXN*7];

int getType(char a)
{
    switch(a)
    {
    case 'S':
        return 1;
    case 'M':
        return 2;
    case 'L':
        return 3;
    case 'X':
        return 4;
    case 'T':
        return 5;
    default:
        return -1;
    }
}

int DFS(int cur)
{

    for(int i = 0; i < Adj[cur].size(); i++)
    {
        int & to = Adj[cur][i];
        if(vist[to])
            continue;
        vist[to] = true;
        if(match[to] == 0 || DFS(match[to]))
        {
            match[to] = cur;
            match[cur] = to;
            return true;
        }
    }
    return false;
}

int main()
{
    string str;
    string req[25];
    while(1)
    {
        cin >> str ;
        if(str == "ENDOFINPUT")
            break;

        memset(match, 0x00, sizeof match);
        memset(vist, 0x00, sizeof vist);
        memset(HasShirt, 0x00, sizeof HasShirt);
        for(int i = 0; i < MAXN*7; i++)
            Adj[i].clear();

        int n;
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> req[i];
        for(int i = 1; i <= 5; i++)
            cin >> HasShirt[i];
        cin >> str;

        for(int i = 1; i <= n; i++)
        {
            int st = getType(req[i][0]);
            int ed = getType(req[i][1]);
            for(int k = st; k <= ed; k++)
            {
                for(int pos = 1; pos <= HasShirt[k]; pos++)
                {
                    int realpos = pos + OFFSET*k;
                    Adj[realpos].push_back(i);
                    Adj[i].push_back(realpos);
                }
            }
        }
/*
        #ifdef DEBUG
        for(int i = 1; i <= n; i++)
        {
            cerr << "Adjacent " << i << endl;
            for(int j = 0; j < Adj[i].size(); j++)
                cerr << " " << Adj[i][j];
            cerr << endl;
        }
        #endif // DEBUG*/

        int ans = 0;
        for(int i = 1; i <= n; i++)
        {
            if(!match[i])
            {
                memset(vist, 0x00, sizeof vist);
                if(DFS(i))
                    ans++;
            }
        }

        if(ans == n)
            cout << SUCCESS << endl;
        else
            cout << FAILURE << endl;
    }
    return 0;
}

