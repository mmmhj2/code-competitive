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
    @p _maxco   起始系数数组（最小选择数）
    @p _minco   终止系数数组（最大选择数）
    **/
    GeneratingFunc(int N, pint value, pint _minco, pint _maxco)
    {
        n = N+5;
        co1 = new int[N+5];
        co2 = new int[N+5];
        memset(co1, 0x00, (sizeof (int)) * n);
        memset(co2, 0x00, (sizeof (int)) * n);
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
                for(int k = 0;k <= res && k + j * v[i] <= res; k++)
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
    for(int i = 0; i <= 100; i++)
        v[i] = 1 ;
    int n, m;
    while(cin >> n >> m )
    {
        for(int i = 1; i <= n; i++)
            cin >> n1[i] >> n2[i] ;
        cout << mainProc.calc(n, m) << endl ;
    }
    return 0;
}
