#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;

const int MAXN = 1000000 + 5;

class Interactor
{
public:
    int PushQuery(int x)
    {
        int ret;
        cout << "? " << x << endl ;
        cin >> ret;
        return ret;
    }

    void PushAnswer(int x)
    {
        cout << "! " << x << endl ;
        InterruptProg(0);
    }

    void InterruptProg(int excd)
    {
        exit(excd);
    }
}interactor;

int main()
{
    int N;
    cin >> N ;
    if(N & 1)
        interactor.PushAnswer(-1);

    N >>= 1;

    int diff = interactor.PushQuery(1) - interactor.PushQuery(N+1);

    if(!diff)
        interactor.PushAnswer(1);
    if(diff & 1)
        interactor.PushAnswer(-1);

    int L = 2, R = N;

    while(L <= R)
    {
        int mid = (L + R) >> 1 ;

        int _diff = interactor.PushQuery(mid) - interactor.PushQuery(mid + N);

        if(!_diff)
            interactor.PushAnswer(mid);
        if(_diff * diff > 0)
            L = mid + 1;
        else
            R = mid - 1;
    }

    interactor.PushAnswer(-1);

    return 0;
}

