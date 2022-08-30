#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
using namespace std;
const int MAXN = 50000;

typedef set<int> si;
typedef si::iterator sitr;
typedef long long i64;

vector <int> A;
vector <int> B;
int n;
i64 ans = 0;

int main()
{
    int curans = 0;
    int match = 0;
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        int t;
        cin >> t;
        A.push_back(t); B.push_back(t);
    }
    reverse(B.begin(), B.end());

    si setA, setB;

    for(int i = 0; i < n; i++)
    {
        sitr itr = setA.find(A[i]);
        if(itr != setA.end())
        {
            ans += curans;  continue;
        }
        
        setA.insert(A[i]);
        bool success = 0;
        curans = 0;
        for(int j = match; j < n; j++)
        {
            sitr itr = setA.find(B[j]);
            if(itr == setA.end())
                break;
                
            if(success)
            {
                curans++;   continue;
            }
            
            setB.insert(B[j]);
            if(setA.size() == setB.size())
            {
                curans++;
                success = true;
                match = j;
            }
        }
        ans += curans;
    }
    cout << ans << endl;
}
