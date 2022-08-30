#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main()
{
    int nCows, nCars, nShow;
    while(cin >> nCows >> nCars >> nShow)
    {
        int nTotal = nCows + nCars;
        int left = nTotal - nShow - 1;
        double firstCar = 1.0 * nCars / nTotal;
        double firstCow = 1.0 * nCows / nTotal;

        double postCar = firstCar * (1.0 * (nCars-1) / left);
        double postCow = firstCow * (1.0 * nCars / left);
        cout << fixed << setprecision(5) << postCar + postCow << endl ;
    }
}