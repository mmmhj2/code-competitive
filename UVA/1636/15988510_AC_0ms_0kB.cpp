#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct fraction
{
private:
    static int GCD(int a, int b)
    {
        if(b == 0)
            return a;
        return GCD(b, a % b);
    }
    int num, den;
public:
    void assign(int n, int d)
    {
        int g = GCD(n, d);
        num = n / g;
        den = d / g;
    }

    bool operator == (const fraction & rhs) const
    {
        return num == rhs.num && den == rhs.den;
    }

    bool operator < (const fraction & rhs) const
    {
        int LCM = den * rhs.den / GCD(den, rhs.den);
        int neoNumL = LCM / den * num;
        int neoNumR = LCM / rhs.den * rhs.num;
        return neoNumL < neoNumR;
    }
};

string str;
int main()
{
    while(cin >> str)
    {
        int zeroCnt = 0;
        int zeroCntBullet = 0;
        int bulletCnt = 0;
        int totalCnt = str.length();
        str += str;
        for(int i = 0; i < totalCnt; i++)
        {
            if(str[i] == '0')
            {
                zeroCnt++;
                if(str[i+1] == '1')
                    zeroCntBullet++;
            }
            else
                bulletCnt++;
        }
        fraction probRotate;
        probRotate.assign(bulletCnt, totalCnt);
        fraction probShoot;
        probShoot.assign(zeroCntBullet, zeroCnt);
        if(probRotate == probShoot)
            cout << "EQUAL" << endl ;
        else if(probRotate < probShoot)
            cout << "ROTATE" << endl ;
        else
            cout << "SHOOT" << endl ;
    }
}