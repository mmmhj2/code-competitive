#include <bits/stdc++.h>
using namespace std;

int procUnit[10];
int N;
int ans;

vector<int> schedule;

bool check(const int *cur, int offset)
{
	for (int i = 0; i < 5; i++)
		if (procUnit[i] & (cur[i] >> offset))
			return false;
	return true;
}

void DFS(int taskId, int time, const int *state)
{
	if (taskId >= 9)
		return ans = min(ans, time + N), (void) 0;
	int * tmp = new int[5];

	for (unsigned i = 0; i < schedule.size(); i++)
	{
		if (time + schedule[i] + (9 - 1 - taskId) * (*schedule.begin()) + N
				> ans)
			return;
		memcpy(tmp, state, (sizeof(int)) * 5);
		if (!check(tmp, schedule[i]))
			continue;
		for (int k = 0; k < 5; k++)
			tmp[k] = (tmp[k] >> schedule[i]) | procUnit[k];
		DFS(taskId + 1, time + schedule[i], tmp);
	}

	delete[] tmp;
}
string s;
int main()
{
	while (cin >> N)
	{
		if (!N)
			break;
		ans = 0x7F7F7F7F;
		schedule.clear();
		memset(procUnit, 0x00, sizeof procUnit);

		for (int i = 0; i < 5; i++)
		{
			cin >> s;
			for (string::iterator itr = s.begin(); itr != s.end(); ++itr)
				if (*itr == 'X')
					procUnit[i] |= (1 << (itr - s.begin()));
		}
		for(int i = 0; i <= N; i++)
			if(check(procUnit, i))
				schedule.push_back(i);
		DFS(0, 0, procUnit);
		cout << ans << endl ;
	}
	return 0;
}
