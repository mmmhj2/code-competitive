#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

template<class T>
void selectMin(T & x, const T & y)
{
	if (x > y)
		x = y;
}
template<class T>
void selectMax(T & x, const T & y)
{
	if (x < y)
		x = y;
}

const int MAXN = 2e5 + 10;
const int MAXLOG = 20 + 5;
const int PINF = 0x3F3F3F3F;

const char NSOL[] = "Impossible";
const char FSOL[] = "Possible";

int N, V;
int lg2 = -1;
int exp_2[MAXLOG];
int R[MAXLOG][MAXN];
int cnt[MAXLOG];
int dp1[MAXN << 3], dp2[MAXN << 3];
int A[MAXN];

void prepare()
{
	exp_2[0] = 1;
	for (int i = 1; i < MAXLOG; i++)
		exp_2[i] = exp_2[i - 1] * 2;
}

int main()
{
	prepare();
	cin >> N >> V;
	for (int i = 1; i <= N; i++)
		cin >> A[i];

	int x = V * 2;
	while (x)
	{
		x /= 2, lg2++;

		// Split segments
		for (int i = 1; i < N; i++)
		{
			if (A[i + 1] - A[i] <= x)
				continue;
			R[lg2][++cnt[lg2]] = i;
		}
		R[lg2][++cnt[lg2]] = N;
	}

	if (cnt[0] > lg2 + 1)
	{
		for (int i = 1; i <= N; i++)
			puts(NSOL);
		return 0;
	}

	for (int s = 0; s < exp_2[lg2]; s++)
		dp2[s] = N + 1;
	for (int s = 0; s < exp_2[lg2]; s++)
		for (int i = 1; i <= lg2; i++)
		{
			if (s & exp_2[i - 1])
				continue;
			selectMax(dp1[s | exp_2[i - 1]],
					*upper_bound(R[i] + 1, R[i] + cnt[i] + 1, dp1[s]));
			selectMin(dp2[s | exp_2[i - 1]],
					R[i][lower_bound(R[i] + 1, R[i] + cnt[i] + 1, dp2[s] - 1)
							- R[i] - 1] + 1);
		}

	for (int i = 1; i <= cnt[0]; i++)
	{
		bool solution = false;
		for (int s = 0; s < exp_2[lg2]; s++)
			if (dp1[s] >= R[0][i - 1] && dp2[exp_2[lg2] - s - 1] <= R[0][i] + 1)
			{
				solution = true;
				break;
			}

		for (int j = R[0][i - 1] + 1; j <= R[0][i]; j++)
			puts(solution ? FSOL : NSOL);

	}

}
