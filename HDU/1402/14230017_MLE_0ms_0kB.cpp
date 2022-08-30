#include <iostream>
#include <string>
using namespace std;

const int MAXN = 150000;

#ifndef CUSTOM_CPL
#include <complex>
typedef complex<double> cpl;
#else
struct cpl
{
    double x, y;
    // Complex class implementation here
};
#endif
typedef cpl cplA[MAXN+5];

class FastFourierTrans
{
    const double PI = acos(-1);
    cpl getOmega(double theta)
    {
        return cpl(cos(theta), -sin(theta));
    }

    void TransformProc(cpl * in, cpl * out, int stp, int siz, int dir)
    {
        if(siz < 1)
            return;
        if(siz == 1)
        {
            out[0] = in[0];
            return;
        }

        TransformProc(in, out, stp * 2, siz / 2, dir);
        TransformProc(in + stp, out + siz / 2, stp * 2, siz / 2, dir);

        cpl even, odd;
        for(int i = 0; i < siz / 2; i++)
        {
            even = out[i], odd = out[i + siz/2];
            out[i] = even + getOmega(dir * PI * 2 * i / siz) * odd;
            out[i + siz/2] = even - getOmega(dir * PI * 2 * i / siz) * odd;
        }
    }
public:
    /**
    @b Run C-T algorithm for FFT
    @p dir 1 => FFT, -1 => Inverted FFT
    **/
    FastFourierTrans(cpl * in, cpl * out, int len, int dir)
    {
        TransformProc(in, out, 1, len, dir);
        if(dir < 0)
            for(int i = 0; i < len; i++)
                out[i] /= len ;
    }
};

class HiPreMultiply
{
    cplA in, in1, in2;
    cplA out, out1, out2;
    int ans[MAXN];
    int LoBit(int x)
    {
        return x & -x;
    }
public:
    HiPreMultiply(string n1, string n2)
    {
        //cout << n1 << " " << n2 << endl ;
        int len1 = n1.length(), len2 = n2.length();
        int totDig = len1 + len2 - 1, n;

        for(int i = 0; i < len1; i++)
            in1[i] = cpl(n1[i] - '0', 0);
        for(int i = 0; i < len2; i++)
            in2[i] = cpl(n2[i] - '0', 0);

        // Fill zero
        for(n = totDig; n != LoBit(n); n += LoBit(n))
            ;
        for(int i = len1; i < n; i++)
            in1[i] = cpl(0, 0);
        for(int i = len2; i < n; i++)
            in2[i] = cpl(0, 0);
        // Calculate multiplication
        new FastFourierTrans(in1, out1, n, 1);
        new FastFourierTrans(in2, out2, n, 1);
        for(int i = 0; i < n; i++)
            in[i] = out1[i] * out2[i];
/*
        cerr << "Phrase 1 completed!" << endl ;
        for(int i = 0; i < n; i++)
            in[i] = out1[i] * out2[i], cerr << in[i] << " " << out1[i] << " " << out2[i] << endl ;;
        cerr << endl ;
*/
        new FastFourierTrans(in, out, n, -1);
/*
        cerr << "Phrase 2 completed!" << endl ;
        for(int i = 0; i < n; i++)
            cerr << out[i] << " " << endl ;
*/

        // phrasing and output
        for(int i = 0; i < n; i++)
            ans[i] = (int)(out[i].real() + 0.5);

        for(int i = n-1; i > 0; i--)
            ans[i-1] += ans[i] / 10, ans[i] %= 10;

        for(int i = 0; i < totDig; i++)
        {

            // Processing leading zero

            if(ans[i] != 0)
            {
                for(; i < totDig; i++)
                    cout << ans[i] ;
                break;
            }
            else if (i == totDig-1)
                cout << 0 ;

            //cout << ans[i] ;
        }
        cout << endl ;
    }
};

int main()
{
    string n1, n2;
    while(cin >> n1 >> n2)
        new HiPreMultiply(n1, n2);
    return 0;
}
