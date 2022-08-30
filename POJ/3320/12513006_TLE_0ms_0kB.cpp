#include <iostream>
#include <map>
#include <set>
using namespace std;

const int MAXN = 1000000;

map <int, int> ideacount;
set <int> ideaappear;
int p, ideasum;
int t;
int idea[MAXN+10];

int main()
{
    cin >> p;
    for(int i = 1; i <= p; i++)
    {
        cin >> idea[i];
        ideaappear.insert(idea[i]);
    }
    int n = ideaappear.size();
    int s = 1, e = 1, num = 0;
    int ans = p+10;

    while(true)
    {
        while(e <= p && num < n)
            if(ideacount[idea[e++]]++ == 0)
                num++;
        if(num < n)
            break;
        ans = min(ans, e-s);

        if(--ideacount[idea[s++]] == 0)
            num--;
    }

    cout << ans << endl ;

}
