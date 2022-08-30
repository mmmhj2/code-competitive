#include <iomanip>
#include <iostream>
#include <cmath>
//#include <complex>
using namespace std;

const double EPS = 1e-9;

struct cvector
{
    int x, y;

    cvector ()
    {
        x = 0, y = 0;
    }

    int operator * (const cvector & rhs)
    {
        return x*rhs.x + y*rhs.y;
    }

    int operator ^ (const cvector & rhs)
    {
        return x*rhs.y - y*rhs.x;
    }

    static double getCosine(cvector a, cvector b)
    {
        int innerproduct = a*b;
        double lengthA = sqrt(a.x*a.x + a.y*a.y);
        double lengthB = sqrt(b.x*b.x + b.y*b.y);
        return innerproduct / (lengthA * lengthB);
    }

    static double getCosineSq(cvector a, cvector b)
    {
        int innerproduct = a*b;
        int lenghSqA = a.x*a.x + a.y*a.y;
        int lenghSqB = b.x*b.x + b.y*b.y;
        return (innerproduct * innerproduct * 1.0) / (lenghSqA * lenghSqB * 1.0);
    }
};

int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        cvector arr[4];
        int tx1, ty1, tx2, ty2;
        for(int i = 0; i < 4; i++)
        {
            cin >> tx1 >> ty1 >> tx2 >> ty2;
            arr[i].x = tx2 - tx1 , arr[i].y = ty2 - ty1;
        }

        bool isRectangle = true;

        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                if(i == j)
                    continue;
                double cosine = cvector::getCosineSq(arr[i], arr[j]);
                int extproduct = arr[i] ^ arr[j];

                if(abs(cosine-0) > EPS && abs(cosine-1) > EPS)
                    isRectangle = false;
                if(abs(cosine-0) <= EPS && extproduct == 0)
                    isRectangle = false;

            }
        }

        if(!isRectangle)
            cout << "NO"  << endl ;
        else
            cout << "YES" << endl ;
    }
    return 0;
}
