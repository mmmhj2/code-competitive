#include <algorithm>
#include <iostream>
#include <string>
using namespace std;
typedef long long i64;

i64 result;
int N;
int cnt[30];
string str;

int main(int argc, char **argv)
{
	cin >> str ;
	for(const char & x : str)
		cnt[x - 'a']++, N++;

	result = 1LL * N * (N - 1) / 2 + 1;
	for(const int & x : cnt)
		if(x != 0)
			result -= 1LL * x * (x - 1) / 2;
	cout << result << endl ;
	return 0;
}

