#include <iostream>
#include <vector>
using namespace std;

typedef long long int i64;

int n, maxDepth, ans;

vector<int> decrypt(i64 rawdata)
{
    vector<int> ret;
    ret.clear();

    while(rawdata != 0LL)
    {
        int tmp = rawdata & 0x0f;
        rawdata >>= 4;
        ret.push_back(tmp);
    }
    return ret;
}

i64 encrypt(vector<int> rawdata)
{
    vector<int>::reverse_iterator itr;
    i64 ret = 0;

    for(itr = rawdata.rbegin(); itr != rawdata.rend(); itr++)
    {
        ret <<= 4;
        ret += *itr;
    }
    return ret;
}

// 向前移动(保证 SegS > Tar)
void moveParaForward(int SegS, int SegE, int Tar, const i64 & org, i64 & neo)
{
    vector <int> orgVec(decrypt(org)), neoVec(orgVec);

    int movcnt = SegE - SegS + 1;
    for (int cur = 0; cur < movcnt; cur++)
        neoVec[Tar + cur] = orgVec[SegS + cur];
    movcnt = SegS - Tar;
    for (int cur = 0; cur < movcnt; cur++)
        neoVec[SegE - cur] = orgVec[SegS - 1 - cur];

    neo = encrypt(neoVec);
}

int getDiffer(i64 toCheck)
{
    int ret = 0;
    for(int i = 1; i < n; i++)
    {
        if((toCheck & 0x0f) != (((toCheck & 0xf0)>>4) - 1))
            ret++;
        toCheck >>= 4;
    }
    if(toCheck != n)
        ret++;
    return ret;
}

int IteratingSearch(int depth, i64 cur)
{
    int differ = getDiffer(cur);
    if(differ > 3 * (maxDepth - depth))
        return 0;
    if(differ == 0)
        return 1;

    for(int i = 0; i < n; i++)
        for(int j = i; j < n; j++)
            for(int k = 0; k < i; k++)
            {
                i64 neo ;
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
        i64 orgInt = encrypt(orgVec);
        int initDiffer = getDiffer(orgInt);

        /*if(initDiffer != 0)
        {
            for(maxDepth = 1; ; maxDepth++)
                if(IteratingSearch(0, orgInt))
                    break;
        }*/
        for(maxDepth = 0; ; maxDepth++)
                if(IteratingSearch(0, orgInt))
                    break;

        cout << "Case " << kase << ": " ;
        cout << maxDepth << endl ;
    }
}
