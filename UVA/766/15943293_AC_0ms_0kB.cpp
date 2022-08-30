#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long i64;
typedef unsigned long long u64;

template<class T>
T GCD(T a, T b)
{
	if (b == 0)
		return a;
	return GCD(b, a % b);
}

template<class T>
T LCM(T a, T b)
{
	return a / GCD(a, b) * b;
}

template<class T = long long>
class Fraction
{
public:
	typedef T data_type;
	data_type a, b;
private:
	static data_type Abs(const data_type & x)
	{
		if (x > 0)
			return x;
		return (-x);
	}

	static data_type findLCD(const Fraction & x, const Fraction & y)
	{
		return LCM(x.b, y.b);
	}

	Fraction proc()
	{
		if(a == 0)
		{
			b = 1;
			return (*this);
		}

		data_type gcd = GCD(a, b);
		a /= gcd, b /= gcd;

		if (a * b < 0)
			a = -abs(a), b = abs(b);
		else
			a = abs(a), b = abs(b);

		return (*this);
	}

public:
	Fraction()
	{
		a = 0, b = 1;
	}
	Fraction(data_type _a)
	{
		a = _a, b = 1;
	}
	Fraction(data_type _a, data_type _b)
	{
		a = _a, b = _b;
	}

	Fraction operator +(const Fraction & rhs) const
	{
		return Fraction(a * rhs.b + rhs.a * b, b * rhs.b).proc();
	}
	Fraction operator -(const Fraction & rhs) const
	{
		return Fraction(a * rhs.b - rhs.a * b, b * rhs.b).proc();
	}
	Fraction operator *(const Fraction & rhs) const
	{
		return Fraction(a * rhs.a, b * rhs.b).proc();
	}
	Fraction operator /(const Fraction & rhs) const
	{
		return Fraction(a * rhs.b, b * rhs.a).proc();
	}

	explicit operator double()
	{
		return 1.00 * a / b;
	}

};
typedef Fraction<> Fract;

const int MAXN = 25;

Fract Bernoulli[MAXN], answer[MAXN];
Fract C[MAXN][MAXN];

void prepare()
{
	for(int i = 0; i < MAXN; i++)
	{
		C[i][0] = C[i][i] = 1;
		for(int j = 1; j < i ; j++)
			C[i][j] = C[i-1][j] + C[i-1][j-1];
	}

	Bernoulli[0] = 1;
	for(int i = 1; i < MAXN; i++)
	{
		Bernoulli[i] = 0;
		for(int j = 0; j < i; j++)
			Bernoulli[i] = Bernoulli[i] - C[i+1][j] * Bernoulli[j];
		Bernoulli[i] = Bernoulli[i] / C[i+1][i];
	}
}

int main(int argc, char * argv[])
{
	prepare();

	int kase;
	scanf("%d", &kase);
	while(kase--)
	{
		int N;
		i64 L = 1;
		scanf("%d", &N);

		for(int i = 0; i <= N; i++)
		{
			answer[i] = C[N + 1][i] * Bernoulli[i] * Fract(1LL, N + 1LL);
			L = LCM(L, answer[i].b);
		}

		printf("%lld ", L);
		answer[1] =  answer[1] + 1;

		for(int i = 0; i <= N; i++)
			printf("%lld ", L / answer[i].b * answer[i].a);

		printf("0\n");
		if(kase)
			printf("\n");
	}
}

