#include <iostream>
#include <string>
using namespace std;

typedef unsigned int uint;

#ifdef _CRT_ABS_DEFINED
int abs(int a)
{
    if(a < 0)
        return -a;
    return a;
}
#endif // _CRT_ABS_DEFINED

int main()
{
    int kase;
    cin >> kase ;
    while(kase--)
    {
        bool counterfeit[15] = {0};
        int suspicion[15] = {0};
        string lf, rt, res;
        for(int i = 1; i <= 3; i++)
        {
            cin >> lf >> rt >> res ;
            if(res == "even")
                for(uint i = 0; i < lf.length(); i++)
                    counterfeit[lf[i] - 'A'] = true,
                    counterfeit[rt[i] - 'A'] = true;
            if(res == "up")
                for(uint i = 0; i < lf.length(); i++)
                    suspicion[lf[i] - 'A'] ++,
                    suspicion[rt[i] - 'A'] --;
            if(res == "down")
                for(uint i = 0; i < lf.length(); i++)
                    suspicion[lf[i] - 'A'] --,
                    suspicion[rt[i] - 'A'] ++;
        }

        char counterfeitcoin = '\0';
        int maxsuspicion = 0;
        for(int i = 0; i < 12; i++)
        {
            if(counterfeit[i])
                continue;
            if(abs(maxsuspicion) < abs(suspicion[i]))
                maxsuspicion = suspicion[i],
                counterfeitcoin = 'A' + i;
        }
        cout << counterfeitcoin ;
        cout << " is the counterfeit coin and it is " ;
        cout << (maxsuspicion < 0 ? "light" : "heavy");
        cout << "." << endl ; // !!!!!
    }
    return 0;
}
