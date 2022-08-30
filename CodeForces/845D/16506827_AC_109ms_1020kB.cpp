#include <bits/stdc++.h>
using namespace std;

int N;
int ans, spd, spdLim = 0x7F7F7F7F;

int noTakeoverCnt;
stack <int> spdSign;

int main()
{
	ios::sync_with_stdio(false);

	cin >> N ;
	while(N--)
	{
		int op;
		cin >> op ;
		switch(op)
		{
		case 1:
			cin >> spd;

			while(spdSign.size() && spd > spdSign.top())
				spdSign.pop(), ans++;
			break;
		case 2:
			ans += noTakeoverCnt;
			noTakeoverCnt = 0;
			break;
		case 3:
			cin >> spdLim;
			if(spd > spdLim)
				ans++;
			else
				spdSign.push(spdLim);
			break;
		case 4:
			noTakeoverCnt = 0;
			break;
		case 5:
			//spdLim = 0x7F7F7F7F;
			while(spdSign.size())
				spdSign.pop();
			break;
		case 6:
			noTakeoverCnt ++;
		}
	}

	cout << ans << endl ;

	return 0;
}
