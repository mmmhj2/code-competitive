#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;

const int MAXN = 12;

int a[MAXN][MAXN];

int main()
{
	int kase;

	scanf("%d", &kase);

	while (kase--)
	{
		for (int i = 0; i < 9; i += 2)
			for (int j = 0; j <= i; j += 2)
				scanf("%d", &a[i][j]);

		for (int i = 8; i >= 0; i -= 2)
			for (int j = 1; j < i; j += 2)
				a[i][j] = (a[i - 2][j - 1] - a[i][j - 1] - a[i][j + 1]) / 2;

		for (int i = 1; i < 9; i += 2)
			for (int j = 0; j <= i; j++)
				a[i][j] = a[i + 1][j] + a[i + 1][j + 1];

		for (int i = 0; i < 9; i++)
			for (int j = 0; j <= i; j++)
				printf("%d%c", a[i][j], " \n"[j == i]);
	}

	return (0);

}
