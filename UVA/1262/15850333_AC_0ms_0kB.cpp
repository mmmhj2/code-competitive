#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;

const int MAXN = 8000;

char mapA[10][10], mapB[10][10];
char answer[10];

int K, cur;

int DFS(int pos)
{
	if(pos == 5)
		return (++cur == K);

	bool Candidate[2][26] = {0};
	for(int i = 0; i < 6; i++)
		Candidate[0][mapA[i][pos] - 'A'] = 1;
	for(int i = 0; i < 6; i++)
		Candidate[1][mapB[i][pos] - 'A'] = 1;

	for(char c = 'A'; c <= 'Z'; c++)
		if(Candidate[0][c - 'A'] && Candidate[1][c - 'A'])
		{
			//printf("At depth %d, trying %c\n", pos, c);
			answer[pos] = c;
			if(DFS(pos+1))
				return (1);
			answer[pos] = '\0';
		}
	return (0);
}

int main()
{
	int kase;
	cin >> kase ;

	while(kase--)
	{
		cur = 0;
		cin >> K ;
		for(int i = 0; i < 6; i++)
			cin >> mapA[i];
			//cerr << mapA[i] << endl ;
		for(int i = 0; i < 6; i++)
			cin >> mapB[i];
			//cerr << mapB[i] << endl;

		if(DFS(0))
			cout << answer << endl ;
		else
			cout << "NO" << endl ;
	}
}

