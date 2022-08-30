#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <cmath>
#include <queue>

#define printfDbg(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)

using namespace std;
typedef long long i64;

//const int MAXN = 1000000000;

int N, K;

void changeInterval(int L, int R, string & s)
{
	s[R] = '-';
	for(int pos = R - 1; pos > L; pos--)
		s[pos] = '0';
	s[L] = '1';
}

int main()
{
	string str;
	while(cin >> str)
	{
		if(*str.begin() == '0')
			break;
		int lastOne = -1, curpos = str.length(), sum = 0;
		str.insert(0, "0");

		while(curpos >= 1)
		{
			if(str[curpos] == '1')
			{
				if(lastOne == -1)
					lastOne = curpos;
				sum++;
			}
			else
			{
				if(sum >= 2)
					changeInterval(curpos, lastOne, str),
					sum = 1, lastOne = curpos;
				else
					sum = 0, lastOne = -1;
			}
			curpos--;
		}

		if(sum > 2)
			changeInterval(curpos, lastOne, str);
		for(string::iterator itr = str.begin(); itr != str.end(); itr++)
			if(*itr == '1')
				*itr = '+';
		if(*str.begin() == '0')
			str.erase(0, 1);
		cout << str << endl ;
	}
}

