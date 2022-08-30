#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const int MAXN = 50000;

int height[MAXN+10], n;
vector <int> peak;

int check(int);
int binsearch();

int main()
{
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> height[i];
    for(int i = 1; i < n-1; i++)
        if((height[i] > height[i-1]) && (height[i] > height[i+1]))
            peak.push_back(i);

    if(peak.size() <= 0)
        cout << 0 << endl ;
    else
        cout << binsearch() << endl ;
}

int check(int k)
{
    int current = *peak.begin();
    int flagcnt = 1;
    for(int i = 1; i < peak.size(); i++)
    {
        if(peak[i] - current >= k)
        {
            flagcnt ++;
            current = peak[i];
        }
    }
    return (flagcnt >= k);
}

int binsearch()
{
    int l = 1, r = n;
    while(l + 1 < r)
    {
        int mid = (l+r) >> 1;
        //cerr << mid << " ";
        if(check(mid))
            l = mid;
        else
            r = mid;
        //cerr << l << " " << r << endl;
    }
    return l;
}
