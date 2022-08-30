#include <bits/stdc++.h>
using namespace std;

#define prev __prev__1337

class StringDecryption
{
	typedef long long i64;
	static const int MAXN = 500 + 10;
	static const int MOD = 1e9 + 9;
	string str;

	i64 dp[MAXN][15][2];

public:
	int decrypt(vector<string> code);
};

int StringDecryption::decrypt(vector<string> code)
{
	for(const string & x : code)
		str += x;

	dp[0][10][1] = 1;
	for(int last = 1; last <= (int)str.length(); last++)
	{
		i64 mult = 0, power_10 = 1;
		int lastChar = str[last - 1] - '0';
		for(int prev = last - 2; prev >= 0; prev--)
		{
			mult = (mult + power_10 * (str[prev] - '0')) % MOD;
			power_10 = power_10 * 10 % MOD ;

			if(str[prev] == '0')
				continue;
			if(prev > 0 && str[prev-1] - '0' == lastChar)
				continue;

			for(int prevDigit = 0; prevDigit <= 10; prevDigit++)
				for(int prevTaken = 0; prevTaken < 2; prevTaken++)
				{
					if(dp[prev][prevDigit][prevTaken] == 0)
						continue;
					if(lastChar == 0 && prevTaken == 1)
						continue;
					dp[last][prevDigit][0] = (dp[last][prevDigit][0] + dp[prev][prevDigit][prevTaken]) % MOD;

					if(prevDigit != lastChar)
					{
						if(lastChar > 0 && (prev < last - 2 || mult > 1))
							dp[last][lastChar][0] = ((dp[last][lastChar][0] + (dp[prev][prevDigit][prevTaken] * (mult - 1 - prevTaken + MOD)) % MOD) % MOD );
						if(prev < last - 2 || mult > 1 || prevTaken == 0)
							dp[last][lastChar][1] = ((dp[last][lastChar][1] + dp[prev][prevDigit][prevTaken]) % MOD);
					}
				}
		}
	}
	return (int) (dp[str.length()][str[str.length() - 1] - '0'][1] % MOD);
}
