#include <iostream>
#include <algorithm>
using namespace std;

bool JudgeWinner(int a, int b)
{
    int cnt = 0;
    while(true)
    {
        if(!(a % b))
            break;
        if(a >= b * 2)
            break;
        a = a - b;
        if(a < b)
            swap(a, b);
        cnt++;
    }
    return cnt & 1;
}

int main()
{
    int a, b;
    while(cin >> a >> b)
    {
        if((!a) && (!b))
            break;
        if(JudgeWinner(max(a, b), min(a, b)))
            cout << "Ollie wins" << endl ;
        else
            cout << "Stan wins" << endl ;
    }
    return 0;
}
