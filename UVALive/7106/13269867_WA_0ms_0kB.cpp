#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#define until(x) while(!(x))
using namespace std;

const int MAXN = 1005;
const int INF  = 0x3f3f3fff;
const char MAXANS[] = "ZZZZZZZZZZZZZZZZ";

string dictionary[MAXN];
int n, dictDist[2][MAXN];
int AdjMat[MAXN][MAXN];

inline void ClearDict()
{
    memset(dictDist, 0xFF, sizeof dictDist);
    memset(AdjMat  , 0x00, sizeof AdjMat);
    int i = 0;
    until(dictionary[i].empty())
    {
        dictionary[i].clear();
        i++;
    }
}

void BFS(int start)
{
    queue <int> que;
    que.push(start);
    dictDist[start][start] = 0;

    until(que.empty())
    {
        int cur = que.front();
        que.pop();

        for(int i = 0; i < n; i++)
        {
            if(AdjMat[cur][i] == 1 && dictDist[start][i] < 0)
            {
                dictDist[start][i] = dictDist[start][cur] + 1;
                que.push(i);
            }
        }
    }
}


int main()
{
    while(cin >> n)
    {
        ClearDict();
        for(int i = 0; i < n; i++)
            cin >> dictionary[i] ;

        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
            {
                int DiffCnt = 0;
                for(unsigned k = 0; k < dictionary[i].size(); k++)
                    DiffCnt += (dictionary[i][k] != dictionary[j][k]);
                AdjMat[i][j] += DiffCnt;
            }

        BFS(0); BFS(1);

        int minAns = INF;   string strAns = MAXANS;

        if(dictDist[0][1] >= 0)
            minAns = dictDist[0][1], strAns = "0";

        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                if(AdjMat[i][j] == 2 && dictDist[0][i] >= 0 && dictDist[1][j] >= 0)
                    if(minAns >= dictDist[0][i] + dictDist[1][j] + 2)
                    {
                        minAns = dictDist[0][i] + dictDist[1][j] + 2;
                        //string tmpAns1 = dictionary[i];
                        string tmp = dictionary[i];
                        string tmpAns = ((minAns == dictDist[0][i] + dictDist[1][j] + 2) ? strAns : MAXANS);

                        for(int k = 0; k < dictionary[i].size(); k++)
                        {
                            if(dictionary[i][k] != dictionary[j][k])
                            {
                                tmp[k] = dictionary[j][k];
                                tmpAns = min(tmpAns, tmp);
                                tmp[k] = dictionary[i][k];
                            }
                        }
                        strAns = tmpAns;
                    }
        if(minAns == INF)
            strAns = "0", minAns = -1;
        cout << strAns << endl << minAns << endl ;
    }
    return 0;
}
