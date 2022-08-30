#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int INF = 0x7FFFFFFF;

struct point
{
    int delta;
    int pos;

    static bool cmp(const point & lhs, const point & rhs)
    {
        if(lhs.pos == rhs.pos)
            return lhs.delta > rhs.delta;
        return lhs.pos < rhs.pos;
    }
};

vector <point> vpnt;
vector <pair<int, int>> ans;
int N, K;

int main()
{
    int l, r;
    cin >> N >> K ;
    for(int i = 1; i <= N; i++)
    {
        cin >> l >> r ;
        vpnt.push_back(point{ 1, l});
        vpnt.push_back(point{-1, r});
    }

    sort(vpnt.begin(), vpnt.end(), point::cmp);

    int cur = INF;
    for(vector<point>::iterator itr = vpnt.begin(); itr != vpnt.end(); itr++)
    {
        if(itr->delta > 0)
        {
            K--;
            if(K == 0)
                cur = itr->pos;
        }

        else
        {
            K++;
            if(K == 1)
                ans.push_back(make_pair(cur, itr->pos));
        }
    }
    cout << ans.size() << endl ;

    for(pair<int, int> & x : ans)
        cout << x.first << " " << x.second << endl ;

    return 0;
}

