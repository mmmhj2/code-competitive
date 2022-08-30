#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 5000000, MAXPRIME = 350000;

int phi[MAXN+5], primeTable[MAXPRIME+5];
bool vist[MAXN+5];

int getEuler(int imax);

int main()
{
    int s, e;
    cin >> s >> e;
    getEuler(e+5);

    int emin = 0x7fffffff, pmin = s;
    for(int i = s; i <= e; i++)
    {
        //cout << i << ":" << phi[i] << endl;
        if(emin > phi[i])
        {
            emin = phi[i];
            pmin = i;
        }
    }

    cout << pmin;
}

int getEuler(int imax)
{
    int cnt = 0;    vist[1] = true;
    for(int i = 2; i <= imax; i++)
    {
        if(!vist[i])
        {
            primeTable[++cnt] = i;
            //vist[i] = true;
            phi[i] = i-1;
        }

        for(int j = 1; j <= cnt; j++)
        {
            if(primeTable[j] * i > imax)
                break;
            vist[primeTable[j]*i] = true;

            if(i % primeTable[j] == 0)
            {
                phi[i * primeTable[j]] = phi[i] * primeTable[j];
                break;
            }
            phi[i * primeTable[j]] = phi[i] * (primeTable[j]-1);
        }
    }
    return cnt;
}
