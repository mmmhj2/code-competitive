#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>
#include <vector>
#include <cmath>
using namespace std;

const int MAXN = 20000 + 5;
const int DIR[5][2] = {{-1, 1}, {0, 2}, {1, 1}, {1, -1}, {0, -2}};

struct Point
{
	int x, y;
	Point (int _x = 0, int _y = 0)
	{
		x = _x, y = _y;
	}
};

vector <Point> pts;

void prepare()
{
	int x(0), y(0);
	pts.push_back(Point(x, y));
	y -= 2;
	pts.push_back(Point(x, y));

	for(int k = 1; k <= 60; k++)
	{
		for(int i = 0; i < 5; i++)
			for(int j = 0; j < k; j++)
				x += DIR[i][0], y += DIR[i][1], pts.push_back(Point(x, y));
		y -= 2;
		pts.push_back(Point(x, y));

		for(int i = 0; i < k; i++)
			x--, y--, pts.push_back(Point(x, y));
	}

	assert(pts.size() > 10000);
}

int main()
{
	int a, b;

	prepare();

	while (scanf("%d%d", &a, &b) && a && b)
	{
		a--, b--;
		int x = abs(pts[a].x - pts[b].x);
		int y = abs(pts[a].y - pts[b].y);
		int result = ((y <= x) ? x : (x + (y - x) / 2));

		printf("The distance between cells %d and %d is %d.\n", a, b, result);
		fflush(stdout);
	}

	return (0);

}

