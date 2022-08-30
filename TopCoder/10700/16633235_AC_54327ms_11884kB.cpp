#include <bits/stdc++.h>
using namespace std;

class EllysString
{
	const int INF = 1e9;
	vector <int> sCnt, tCnt;
	vector <int> sPos[26], tPos[26];
	vector <int> best;
public:
	int theMin(vector<string> _s, vector<string> _t);
};

int EllysString::theMin(vector<string> _s, vector<string> _t)
{
	string s, t;
	for(string __s : _s)
		s += __s;
	for(string __t : _t)
		t += __t;

	if(s.length() != t.length())
		throw new std::runtime_error("");
	sCnt.resize(26), tCnt.resize(26);
	for(char ch : s)
		sCnt[ch - 'a']++;
	for(char ch : t)
		tCnt[ch - 'a']++;

	for(int i = 0; i < 26; i++)
		sPos[i].resize(sCnt[i]), tPos[i].resize(tCnt[i]);
	best.resize(s.length() + 1);
	fill(best.begin(), best.end(), INF);
	best[0] = 0;

	for(int start = 0; start < s.length(); start++)
	{
		best[start + 1] = min(best[start + 1], best[start] + 1);
		fill(sCnt.begin(), sCnt.end(), 0),
		fill(tCnt.begin(), tCnt.end(), 0);

		int numEqual = 0, totalDelta = 0;
		for(int len = 1; start + len <= s.length(); ++len)
		{
			int ch = s.at(start + len - 1) - 'a';
			if(sCnt[ch] == tCnt[ch])
				numEqual--;
			sPos[ch][sCnt[ch]++] = len;
			if(sCnt[ch] <= tCnt[ch])
				totalDelta += abs(sPos[ch][sCnt[ch] - 1] - tPos[ch][sCnt[ch] - 1]);
			if(sCnt[ch] == tCnt[ch])
				numEqual++;

			ch = t.at(start + len - 1) - 'a';
			if(sCnt[ch] == tCnt[ch])
				numEqual--;
			tPos[ch][tCnt[ch]++] = len;
			if(tCnt[ch] <= sCnt[ch])
				totalDelta += abs(sPos[ch][tCnt[ch] - 1] - tPos[ch][tCnt[ch] - 1]);
			if(sCnt[ch] == tCnt[ch])
				numEqual++;

			if(numEqual == 0)
				best[start + len] = min(best[start + len], best[start] + totalDelta / 2);
		}
	}
	return best[s.length()];
}
