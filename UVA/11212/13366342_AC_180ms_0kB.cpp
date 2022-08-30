#include <iostream>
#include <vector>
using namespace std;

typedef long long int i64;

int n, maxDepth, ans;

void moveParaForward(int SegS, int SegE, int Tar, const vector<int> & orgVec, vector<int> & neoVec)
{
    neoVec = vector<int> (orgVec);
    int movcnt = SegE - SegS + 1;
    for (int cur = 0; cur < movcnt; cur++)
        neoVec[Tar + cur] = orgVec[SegS + cur];
    movcnt = SegS - Tar;
    for (int cur = 0; cur < movcnt; cur++)
        neoVec[SegE - cur] = orgVec[SegS - 1 - cur];
}

int getDiffer(const vector<int> & vec)
{
    int ret = 0;
    //vec.push_back(n+1);
    for(int i = 0; i < n-1; i++)
        if(vec[i] != vec[i+1]-1)
            ret++;
    if(vec[n-1] != n)
        ret++;
    return ret;
}

int IteratingSearch(int depth, vector<int> cur)
{
    int differ = getDiffer(cur);
    if(differ > 3 * (maxDepth - depth))
        return 0;
    if(differ == 0)
        return 1;

    vector <int> neo;
    for(int i = 0; i < n; i++)
        for(int j = i; j < n; j++)
            for(int k = 0; k < i; k++)
            {
                moveParaForward(i, j, k, cur, neo);
                if(IteratingSearch(depth+1, neo))
                    return 1;
            }
    return 0;
}

int main()
{
    int kase = 0;
    while(true)
    {
        kase++;
        maxDepth = 0;
        cin >> n ;
        if(n == 0)
            break;
        vector <int> orgVec;
        for(int i = 0; i < n ; i++)
        {
            int tmp ;
            cin >> tmp ;
            orgVec.push_back(tmp);
        }

        for(maxDepth = 0; ; maxDepth++)
                if(IteratingSearch(0, orgVec))
                    break;

        cout << "Case " << kase << ": " ;
        cout << maxDepth << endl ;
    }
}
