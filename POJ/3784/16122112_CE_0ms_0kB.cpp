//============================================================================
// Name        : DynamicMedian.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <queue>
using namespace std;

template<class T>
class HeapPair
{
	T median;
	priority_queue<T, vector<T>, greater<T> > lHeap;
	priority_queue<T, vector<T>, less<T> > hHeap;
public:
	HeapPair()
	{
		median = T();
		//lHeap.clear(), hHeap.clear();
	}

	void clear()
	{
		//lHeap.clear(), hHeap.clear();
		while(lHeap.size())
			lHeap.pop();
		while(hHeap.size())
			hHeap.pop();
	}

	void insert(const T & x)
	{
		if(lHeap.empty())
		{
			lHeap.push(x);
			return;
		}

		if(x > lHeap.top())
			lHeap.push(x);
		else
			hHeap.push(x);

		while(lHeap.size() < hHeap.size())
			lHeap.push(hHeap.top()), hHeap.pop();
		while(lHeap.size() > hHeap.size() + 1)
			hHeap.push(lHeap.top()), lHeap.pop();

	}

	T inspect(void)
	{
		return lHeap.top();
	}

};

HeapPair <int> hp;
vector <int> answer;

int main()
{
	int T, caseId, N, x;
	scanf("%d", &T);
	for(int caseCnt = 1; caseCnt <= T; caseCnt++)
	{
		hp.clear();
		answer.clear();

		scanf("%d%d", &caseId, &N);

		for(int i = 1; i <= N; i++)
		{
			scanf("%d", &x);
			hp.insert(x);

			if(i & 1)
				answer.push_back(hp.inspect());
		}

		printf("%d %u\n", caseId, answer.size());
		for(vector<int>::iterator itr = answer.begin(); itr != answer.end(); ++itr)
			printf("%d%c", *itr, " \n"[(itr - answer.begin() + 1) % 10 == 0]);
		puts("");
	}

	return 0;
}
