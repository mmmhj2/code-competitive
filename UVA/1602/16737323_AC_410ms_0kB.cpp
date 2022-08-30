#include <bits/stdc++.h>
using namespace std;

//ofstream toLog("debug.log");

const int DX[] = { 0, 0, 1, -1 };
const int DY[] = { 1, -1, 0, 0 };
const int MAXN = 15;

struct Cell
{
	int x, y;
	Cell(int _x = 0, int _y = 0)
	{
		x = _x, y = _y;
	}

	bool operator <(const Cell & rhs) const
	{
		return x < rhs.x || (x == rhs.x && y < rhs.y);
	}
};

class Polyomino: public set<Cell>
{
public:

	void normalize()
	{
		Polyomino n;
		int deltaX = this->begin()->x;
		int deltaY = this->begin()->y;
		for (const Cell & t : (*this))
			deltaX = min(deltaX, t.x), deltaY = min(deltaY, t.y);
		for (const Cell & t : (*this))
			n.emplace(t.x - deltaX, t.y - deltaY);
		(*this) = n;
	}

	void rotate()	// 90°clockwise
	{
		Polyomino n;
		for (const Cell & t : (*this))
			n.emplace(t.y, -t.x);
		n.normalize();
		(*this) = n;
	}

	void flip()
	{
		Polyomino n;
		for (const Cell & t : (*this))
			n.emplace(t.x, -t.y);
		n.normalize();
		(*this) = n;
	}
};
set<Polyomino> poly[MAXN];
int answer[MAXN][MAXN][MAXN];

bool tryInsert(const Polyomino & _p, const Cell & c)
{
	Polyomino p = _p;
	p.insert(c);
	p.normalize();

	int n = p.size();
	for (int i = 0; i < 4; i++)
	{
		if (poly[n].count(p) != 0)
			return false;
		p.rotate();
	}
	p.flip();
	for (int i = 0; i < 4; i++)
	{
		if (poly[n].count(p) != 0)
			return false;
		p.rotate();
	}
/*
	toLog << "Polyomino inserted to " << n << endl ;
	for(const Cell & c : _p)
		toLog << "(" << c.x << "," << c.y << ") ";
	toLog << " -> " ;
	for(const Cell & c : p)
		toLog << "(" << c.x << "," << c.y << ") ";
	toLog << endl ;
*/
	poly[n].insert(p);
	return true;
}

void solve()
{
	Polyomino s;
	s.emplace(0, 0);
	poly[1].insert(s);

	for(int n = 2; n <= 10; n++)
		for(const Polyomino & p : poly[n-1])
			for(const Cell & c : p)
				for(int dir = 0; dir < 4; dir++)
				{
					Cell newc(c.x + DX[dir], c.y + DY[dir]);
					if(p.count(newc) == 0)
						//poly[p.size() + 1].insert(p);
						tryInsert(p, newc);
				}
	for(int n = 1; n <= 10; n++)
		for(int w = 1; w < MAXN; w++)
			for(int h = 1; h < MAXN; h++)
			{
				int cnt = 0;
				for(const Polyomino & p : poly[n])
				{
					//cerr << n << " " << w << " " << h << " " << p.size() << endl ;
					int maxX = 0, maxY = 0;
					for(const Cell & c : p)
						maxX = max(maxX, c.x),
						maxY = max(maxY, c.y);

					if(min(maxX, maxY) < min(h, w) && max(maxX, maxY) < max(h, w))
						cnt++;

				}
				//toLog << n << " " << w << " " << h << " " << cnt << endl ;
				answer[n][w][h] = cnt;
			}
}

int main()
{

	solve();

	int n, w, h;
	while(cin >> n >> w >> h)
		cout << answer[n][w][h] << endl ;

	return 0;
}
