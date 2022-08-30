//////////////////////////////////////////////////////
#include <algorithm>
#include <cstring>
#include <cfloat>
#include <vector>
#include <cmath>
using namespace std;

class Egalitarianism2
{
	static const int EPS = 1e-9;
	static const int MAXN = 20 + 5;

	int N;

	bool vis[MAXN];

	double dist[MAXN];
	int fa[MAXN];

	double w[MAXN][MAXN];
	double w_prime[MAXN][MAXN];		// w' = (w - avg) ^ 2

	double getEuclid(double x1, double y1, double x2, double y2)
	{
		return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	}

	void getW(double avg)
	{
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				w_prime[i][j] = (avg - w[i][j]) * (avg - w[i][j]);
	}

	double prim(double avg);

public:
	Egalitarianism2()
	{
		N = 0;
	}
	;
	virtual ~Egalitarianism2()
	{
	}
	;

	double minStdev(vector<int> x, vector<int> y);
};

double Egalitarianism2::prim(double avg)
{
	memset(fa, 0x00, sizeof fa);
	memset(vis, 0x00, sizeof vis);
	memset(dist, 0x00, sizeof dist);
	vector<double> pickedEdge;
	getW(avg);

	vis[0] = true;
	for (int i = 0; i < N; i++)
		dist[i] = w_prime[0][i], fa[i] = 0;

	avg = 0;
	for (int i = 1; i <= N - 1; i++)
	{
		pair<double, int> sel(DBL_MAX, -1);
		for (int k = 0; k < N; k++)
			if (!vis[k])
				sel = min(sel, make_pair(dist[k], k));

		int k = sel.second;
		vis[k] = true;
		pickedEdge.push_back(w[fa[k]][k]);
		avg += w[fa[k]][k] / (N - 1);

		for (int j = 0; j < N; j++)
			if (dist[j] > w_prime[k][j])
				dist[j] = w_prime[k][j], fa[j] = k;
	}

	double sqDev = 0;

	for (vector<double>::iterator itr = pickedEdge.begin();
			itr != pickedEdge.end(); ++itr)
		sqDev += ((avg - *itr) * (avg - *itr)) / (N - 1);

	return sqrt(sqDev);
}

double Egalitarianism2::minStdev(vector<int> x, vector<int> y)
{
	double result = 1e9;

	N = x.size();
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			w[i][j] = getEuclid(x[i], y[i], x[j], y[j]);

	for (int x = 0; x < N * N; x++)
		for (int y = x + 1; y < N * N; y++)
		{
			double avg = (w[x / N][x % N] + w[y / N][y % N]) / 2;
			result = min(result, prim(avg + EPS));
		}

	return result;
}
