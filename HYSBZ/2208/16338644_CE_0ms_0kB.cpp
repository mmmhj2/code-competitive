// CF #1000 E We Need More Bosses
#include <iostream>
#include <cstring>
#include <cassert>
#include <string>
#include <vector>
#include <stack>
using namespace std;

const int MAXN = 2000 + 10;

class SCCFinder
{
protected:
	typedef int *pint;
	typedef vector<int> AdjTable;
	typedef stack<int> vStk;

#define until(x) while(!(x))

	pint SCCid, LOW, DFN;
	bool * inStack;
	AdjTable * Adj;

	int TmStp, SCCcnt;
	vStk vexStack;

	void Tarjan(int cur)
	{
		TmStp++;
		DFN[cur] = TmStp;
		LOW[cur] = DFN[cur];
		vexStack.push(cur);
		inStack[cur] = true;

		AdjTable::iterator itr;
		for (itr = Adj[cur].begin(); itr < Adj[cur].end(); itr++)
		{
			int to = *itr;
			if (!DFN[to])
			{
				Tarjan(to);
				LOW[cur] = min(LOW[cur], LOW[to]);
			}
			if (inStack[to])
				LOW[cur] = min(LOW[cur], DFN[to]);
		}

		if (DFN[cur] == LOW[cur])
		{
			int tmp = vexStack.top();
			SCCcnt++;
			//fprintf(stderr, "In %d, constructing SCC %d\n", cur, SCCcnt);
			do
			{
				tmp = vexStack.top();
				SCCid[tmp] = SCCcnt; // ID of each component is in the topology order
				vexStack.pop();
				inStack[tmp] = false;
			}until(tmp == cur);
		}
	}

public:
	SCCFinder()
	{
		TmStp = 0;
		SCCcnt = 0;
		SCCid = LOW = DFN = NULL;
		inStack = NULL;
		Adj = NULL;
	}
	void SCCFinderInit(pint _SCCid, pint _LOW, pint _DFN, bool * _inStack, AdjTable * _Adj)
	{
		SCCid = _SCCid;
		LOW = _LOW;
		DFN = _DFN;
		inStack = _inStack;
		Adj = _Adj;
	}
	void FindSCC(int s)
	{
		if(SCCid == NULL)
			return;
		if(LOW == NULL || DFN == NULL)
			return;
		if(inStack == NULL)
			return;
		if(Adj == NULL)
			return;

		Tarjan(s);
	}

	void FindSCCinDiscrete(int N)
	{
		if(SCCid == NULL)
			return;
		if(LOW == NULL || DFN == NULL)
			return;
		if(inStack == NULL)
			return;
		if(Adj == NULL)
			return;

		for(int i = 1; i <= N; i++)
			if(!DFN[i])
				Tarjan(i);
	}

	int getSCCcnt()
	{
		return SCCcnt;
	}
#undef until
};

SCCFinder sf;

int N;
vector<int> Adj[MAXN];
vector<int> newAdj[MAXN];
bool linked[MAXN][MAXN];

int tmStp;
int DFN[MAXN], LOW[MAXN];
int SCCid[MAXN];
int SCCsiz[MAXN];
int SCCcnt;
bool inStack[MAXN];
stack<int> stk;
string str;

int answer[MAXN];

int vist[MAXN];
void DFS(int cur, int cnt)
{
	answer[cur] += SCCsiz[cur];
	vist[cur] = cnt;
	for(const auto & x : Adj[cur])
		if(vist[x] != cnt)
			DFS(x, cnt);
}

int main()
{
	cin >> N;
	for (int i = 1; i <= N; i++)
	{
		cin >> str;
		for (int j = 0; j < N; j++)
			if (str[j] == '1')
				Adj[i].push_back(j + 1);
	}

	sf.SCCFinderInit(SCCid, LOW, DFN, inStack, Adj);
	sf.FindSCCinDiscrete(N);
	SCCcnt = sf.getSCCcnt();

	//fprintf(stderr, "SCC counter : %d\n", sf.getSCCcnt());
	for(int i = 1; i <= N; i++)
	{
		//fprintf(stderr, "%d ", SCCid[i]);
		SCCsiz[SCCid[i]]++;
		for(const auto & x : Adj[i])
			if(SCCid[i] != SCCid[x] && !linked[x][i])
				newAdj[SCCid[i]].push_back(SCCid[x]), linked[x][i] = true;
	}

	for(int i = 1; i <= N; i++)
		DFS(SCCid[i], i);

	long long ans = 0;
	for(int i = 1; i <= SCCcnt; i++)
		ans += answer[i];
	cout << ans << endl ;
	return 0;
}
