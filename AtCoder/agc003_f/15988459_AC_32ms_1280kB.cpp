#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

typedef long long i64;

const i64 MOD = 1e9 + 7;

vector <int> vec;

template<class T>
T modularExp(T base, i64 exp)
{
	T answer(1);

	while (exp)
	{
		if (exp & 1)
			answer = answer * base % MOD;
		base = base * base % MOD;
		exp = exp >> 1;
	}
	return answer;
}

struct Matrix
{
	i64 data[4][4];

	Matrix(i64 x)	// Load a filled matrix
	{
		memset(data, 0x00, sizeof data);
		for (int i = 0; i < 4; i++)
			data[i][i] = x;
	}

	i64 * operator [](unsigned index)
	{
		return this->data[index];
	}

	const i64 * operator [](unsigned index) const
	{
		return this->data[index];
	}


	Matrix operator *(const Matrix & rhs) const
	{
		Matrix result(0);

		for (int k = 0; k < 3; k++)
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					result[i][j] = (result[i][j]
							+ data[i][k] * rhs.data[k][j] % MOD) % MOD;
		return result;
	}

	Matrix operator %(i64 modular)
	{
		return (*this);
	}
};

char mp[1005][1005];
i64 N, M, K;
i64 blkCnt, adjCnt;
i64 upDown, leftRight;

int solve()
{
	if (K <= 1)
		return 1;
	if (upDown && leftRight)
		return 1;
	if (!upDown && !leftRight)
		return modularExp(blkCnt, K - 1);
	if (!upDown)
		swap(upDown, leftRight);

	Matrix x(0);
	x[0][0] = x[1][1] = blkCnt;
	x[1][2] = 1;
	x[2][2] = upDown;

	x = modularExp(x, K - 2);

	i64 V(0), E(0);
	int tmp[3] =
	{ blkCnt, adjCnt, adjCnt * upDown };

	for (int i = 0; i < 3; i++)
		V = (V + x[0][i] * tmp[i] % MOD) % MOD;
	for (int i = 0; i < 3; i++)
		E = (E + x[1][i] * tmp[i] % MOD) % MOD;

	return (V - E + MOD) % MOD;
}

void countAdj()
{
	// Count adjacent blocks
	for (int i = 0; i < N; i++)
		leftRight += (mp[i][0] == '#' && mp[i][M - 1] == '#');
	for (int i = 0; i < M; i++)
		upDown += (mp[0][i] == '#' && mp[N - 1][i] == '#');
	// Count total blocks
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			blkCnt += (mp[i][j] == '#');

	if (upDown)
		for (int i = 0; i < N - 1; i++)
			for (int j = 0; j < M; j++)
				adjCnt += (mp[i][j] == '#' && mp[i + 1][j] == '#');
	else
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M - 1; j++)
				adjCnt += (mp[i][j] == '#' && mp[i][j + 1] == '#');
}

int main()
{
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++)
		cin >> mp[i];
	cerr << "Input Finished !" << endl ;
	countAdj();
	cout << solve() << endl;
	return 0;
}
