#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
class MoreNim
{
	static constexpr const int MAXN = 50 + 5;
	vector<i64> hp;
	bitset<MAXN> bs[MAXN];
	bool gauss(const vector<i64> & coef);
public:
	i64 bestSet(vector<string> heaps);
};

inline bool MoreNim::gauss(const vector<i64>& coef)
{
	//cerr << "Gauss Elimination" << endl ;
	int equ = coef.size();
	for (unsigned i = 0; i < coef.size(); i++)
		for (int j = 0; j < MAXN; j++)
			bs[j][i] = (coef[i] >> j) & 1;
	for (int i = 0; i < equ; i++)
	{

		int mxr = -1;
		for (int j = i ; j < MAXN; j++)
			if (bs[j][i])
			{
				mxr = j;
				break;
			}
		if (mxr < 0)
			return false;
		swap(bs[mxr], bs[i]);

		for (int j = i + 1; j < MAXN; j++)
		{
			if (!bs[j][i])
				continue;
			bs[j] ^= bs[i];
		}

	}
	return true;
}

inline i64 MoreNim::bestSet(vector<string> heaps)
{
	for(auto x : heaps)
		hp.push_back(stoll(x));
	sort(hp.begin(), hp.end(), greater<i64>());

	vector <i64> op;
	for(auto x : hp)
	{
		op.push_back(x);
		if(!gauss(op))
			op.pop_back();
	}
	i64 sum = 0;
	for(auto x : hp)
		sum += x;
	for(auto x : op)
		sum -= x;
	return sum;
}
