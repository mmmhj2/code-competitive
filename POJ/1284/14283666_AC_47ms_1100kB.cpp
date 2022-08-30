#include <iostream>
#include <utility>
#include <vector>
#include <cmath>
using namespace std;

const int MAXN = 65550 + 10;

vector <int> PrimeList;
bool isPrime[MAXN];
int Phi[MAXN];

void getPhi(int n)
{
    //cerr << n << endl ;
    for(int i = 2; i <= n; i++)
    {
        if(!isPrime[i])
            isPrime[i] = true, PrimeList.push_back(i), Phi[i] = i-1;

        for(unsigned int j = 1; j <= PrimeList.size(); j++)
        {
            const int & prime = PrimeList[j-1];
            if(i * prime > n)
                break;
            isPrime[i * prime] = true;

            if(i % prime == 0)
            {
                Phi[i * prime] = Phi[i] * prime ;
                break;
            }
            else
            {
                Phi[i * prime] = Phi[i] * (prime - 1) ;
            }
        }
    }
}

int main()
{
    int n;
    getPhi(65550);
    while(cin >> n)
    {
        cout << Phi[Phi[n]] << endl ;
    }
}
