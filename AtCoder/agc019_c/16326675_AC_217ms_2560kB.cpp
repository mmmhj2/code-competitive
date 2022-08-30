#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
using namespace std;
typedef long double float128;
typedef long long i64;
const int MAXN = 2e5 + 10;
const float128 PI = acos(float128(-1));

int X1, X2, Y1, Y2;
int N;
int flagX, flagY;
float128 answer;
int stk[MAXN], top;	

pair<int, int> p[MAXN];

int main(int argc, char **argv)
{
	//cerr << (sizeof (float128)) << endl;
	cin >> X1 >> Y1 >> X2 >> Y2 >> N ;
	flagX = flagY = 1;
	if(X1 > X2)
		flagX = -1, X1 = -X1, X2 = -X2;
	if(Y1 > Y2)
		flagY = -1, Y1 = -Y1, Y2 = -Y2;

	for(int i = 1; i <= N; i++)
	{
		cin >> p[i].first >> p[i].second ;
		p[i].first *= flagX, p[i].second *= flagY;

		if(!(X1 <= p[i].first && p[i].first <= X2 && Y1 <= p[i].second && p[i].second <= Y2))
			N --, i --;
	}
	cerr << N << endl ;
	sort(p + 1, p + 1 + N);
	for(int i = 1; i <= N; i++)
		if(top == 0 || p[i].second > stk[top])
			stk[++top] = p[i].second;
		else
			*(upper_bound(stk + 1, stk + top + 1, p[i].second)) = p[i].second;
	cerr << top << endl ;
	answer = 100.0L * (X2 - X1 + Y2 - Y1) + (PI - 4) * 5 * top;
	if(top == min(X2 - X1 + 1, Y2 - Y1 + 1))
		answer += PI * 5;
	cout << fixed << setprecision(20) << answer << endl ;
}

