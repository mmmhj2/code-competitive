#include <bits/stdc++.h>
using namespace std;

const int INF = 0x7F7F7F7F;
const double EPS = 1e-9;
const int MAXN = 1e5 + 5;

struct segment
{
	int L, R;
	bool operator < (const segment & rhs) const
	{
		return this->R < rhs.R;
	}
}segs[MAXN];
int N;

int main()
{

	while(~scanf("%d", &N))
	{
		for(int i = 0 ; i < N; i++)
			scanf("%d%d", &segs[i].L, &segs[i].R);

		sort(segs, segs + N);
		double L = 0, R = 1e7;

		while(L + EPS < R)
		{
			double mid = (L + R) / 2, chk = 0;
			bool ok = true;

			for(int i = 0; i < N; i++)
			{
				if(chk < segs[i].L)
					chk = segs[i].L;
				if(chk + mid > segs[i].R)
				{
					ok = false;
					break;
				}
				chk += mid;
			}

			if(ok)
				L = mid;
			else
				R = mid;
		}

		int num = 0, dem = 1;

		for(int p, q = 1; q <= N; q++)
		{
			p = round(L * q);
			if(fabs(1.0 * p / q - L) < fabs(1.0 * num / dem - L))
				num = p, dem = q;
		}

		printf("%d/%d\n", num, dem);

	}

	return 0;
}
