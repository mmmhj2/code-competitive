#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector <char> stk;

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr);

	string str;
	cin >> str;

	for(char x : str)
	{
		switch(x)
		{
		case 'S':
			stk.push_back(x);
			break;
		case 'T':

			if(stk.empty() || stk.back() == 'T')
				stk.push_back(x);
			else
				stk.pop_back();
			break;
		}
	}

	cout << stk.size() << endl ;

}
