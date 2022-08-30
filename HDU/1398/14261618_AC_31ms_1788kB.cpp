#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 300 + 10;

class GeneratingFunc
{
    typedef int *pint;
    int n;
    pint co1, co2;
    pint v, minco, maxco;
public:
    /**
    @p N    预期空间最大值
    @p value   价值数组
    @p _maxco   起始系数数组
    @p_ minco   终止系数数组
    **/
    GeneratingFunc(int N, pint value, pint _minco, pint _maxco)
    {
        n = N+5;
        co1 = new int[N+5];
        co2 = new int[N+5];
        v = value, minco = _minco, maxco = _maxco;
    }
    ~GeneratingFunc()
    {
        delete[] co1;
        delete[] co2;
    }

    int calc(int terms, int res)
    {
        memset(co1, 0x00, (sizeof (int)) * n);
        co1[0] = 1;

        for(int i = 1; i <= terms; i++)
        {
            for(int j = minco[i];j <= maxco[i] && j * v[i] <= res; j++)
                for(int k = 0; k + j * v[i] <= res; k++)
                    co2[k + j * v[i]] += co1[k];

            for(int j = 0; j <= n; j++)
                co1[j] = co2[j], co2[j] = 0;
        }

        return co1[res];
    }
};

int v[MAXN], n1[MAXN], n2[MAXN];
GeneratingFunc mainProc(MAXN, v, n1, n2);

int main()
{
    for(int i = 1; i <= 17; i++)
        v[i] = i * i;
    for(int i = 0; i <= 300; i++)
        n1[i] = 0, n2[i] = 0x7fffffff;
    int n;
    while(cin >> n)
    {
        if(n <= 0)
            break;
        cout << mainProc.calc(17, n) << endl ;
    }
    return 0;
}
