#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn = 100005;
const double pi = acos(-1.0);
const int low(int x){ return x&-x; }//树状数组的lowbit，可以计算二进制最右边的1
int n, m;
char s1[maxn], s2[maxn];

class FFT
{
private:
    const static int maxn = 150000;//要注意长度是2^k方
    class Plural
    {
    public:
        double x, y;
        Plural(double x = 0.0, double y = 0.0) :x(x), y(y){}
        Plural operator +(const Plural &a)
        {
            return Plural(x + a.x, y + a.y);
        }
        Plural operator -(const Plural &a)
        {
            return Plural(x - a.x, y - a.y);
        }
        Plural operator *(const Plural &a)
        {
            return Plural(x*a.x - y*a.y, x*a.y + y*a.x);
        }
        Plural operator /(const double &u)
        {
            return Plural(x / u, y / u);
        }
    };//定义复数的相关运算
    Plural x[maxn], x1[maxn], x2[maxn];
    Plural y[maxn], y1[maxn], y2[maxn];
    int ans[maxn];
    int n, len;
public:
    int reverse(int x)
    {
        int ans = 0;
        for (int i = 1, j = n >> 1; j; i <<= 1, j >>= 1) if (x&i) ans |= j;
        return ans;
    }//数字倒序,FFT的初始步骤
    Plural w(double x, double y)
    {
        return Plural(cos(2 * pi * x / y), -sin(2 * pi * x / y));
    }
    void setx(char *s, char *S)
    {
        int len1 = 0, len2 = 0;
        for (int i = 0; s[i]; i++, len1++) x1[i].x = s[i] - '0', x1[i].y = 0;
        for (int i = 0; S[i]; i++, len2++) x2[i].x = S[i] - '0', x2[i].y = 0;
        for (len = n = len1 + len2 - 1; n != low(n); n += low(n));
        for (int i = len1; i < n; i++) x1[i] = Plural(0, 0);
        for (int i = len2; i < n; i++) x2[i] = Plural(0, 0);
    }
    void fft(Plural*x, Plural*y, int flag)
    {
        for (int i = 0; i < n; i++) y[i] = x[reverse(i)];
        for (int i = 1; i < n; i <<= 1)
        {
            Plural uu = w(flag, i + i);
            for (int j = 0; j < n; j += i + i)
            {
                Plural u(1, 0);
                for (int k = j; k < j + i; k++)
                {
                    Plural a = y[k];
                    //w(flag*(k - j), i + i) 可以去掉u和uu用这个代替，精度高些，代价是耗时多了
                    Plural b = u * y[k + i];
                    y[k] = a + b;
                    y[k + i] = a - b;
                    u = u*uu;
                }
            }
        }
        if (flag == -1) for (int i = 0; i < n; i++) y[i] = y[i] / n;
    }//1是FFT，-1是IFFT，答案数组是y数组
    void solve()
    {
        fft(x1, y1, 1); fft(x2, y2, 1);
        for (int i = 0; i < n; i++) y[i] = y1[i] * y2[i];
        fft(y, x, -1);
        for (int i = 0; i < n; i++) ans[i] = (int)(x[i].x + 0.5);//调整精度
        for (int i = n - 1; i; i--)
        {
            ans[i - 1] += ans[i] / 10;
            ans[i] %= 10;
        }
        for (int i = 0; i < len; i++)
        {
            if (ans[i] != 0)
            {
                for (; i < len; i++) printf("%d", ans[i]);
                break;
            }
            else if (i == len - 1) putchar('0');
        }
        putchar(10);
    }
}fft;

int main()
{
    while (scanf("%s%s", s1, s2) != EOF)
    {
        fft.setx(s1, s2);
        fft.solve();
    }
    return 0;
}
